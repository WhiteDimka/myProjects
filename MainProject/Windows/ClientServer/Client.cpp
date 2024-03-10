// Prepared by Ekaterina Ilchenko in 2022

// Для сборки exe: cl client.cpp ws2_32.lib
#include "Client.h"
#include "Codec/Codec.h"

Client::Client()
{
    Mute = true;
    IsSendingThreadEnds = true;
    IsAcceptingThreadEnds = true;
    IsClientActive = false;
    IsAudioPlayingNow = false;
    RecieveTry = 0;
    MaxRecieveTry = 50;
    SendTry = 0;
    MaxSendTry = 50;
    CanClientSpeakNow = CanSpeak::WaitingForAnswer;

    IsClientConfigured = InitWSA();

    PlayingMutex = CreateSemaphore(NULL,  // аттрибуты безопасности по умолчанию
                                   1,  // начальное значение счетчика
                                   1,  // максимаьлное значение счетчика
                                   NULL);  // безымянный семафор
    if (PlayingMutex == NULL)
        std::cout << "Ошибка создания мьютекса " << std::endl;
}

Client::~Client()
{
    DisconnectFromServer();
}

bool Client::ConnectToServer(const char* IP, unsigned short Port)
{
    if (IsClientActive)
    {
        std::cout << "Client is not active\n";
        return false;
    }
    if (!IsClientConfigured)
    {
        std::cout << "Client is not configurated\n";
        IsClientConfigured = InitWSA();
        if (!IsClientConfigured)
        {
            std::cout << "Client STILL is not configurated\n";
            return false;
        }
    }

    struct sockaddr_in fordata;
    // binding the socket
    fordata.sin_family = AF_INET;
    fordata.sin_port = htons(Port);
    fordata.sin_addr.s_addr = inet_addr(IP);
    if (connect(m_socket, reinterpret_cast<SOCKADDR*>(&fordata), sizeof(fordata)) ==
        SOCKET_ERROR)
    {
        std::cout << "Connection error\n";
        closesocket(m_socket);
        return false;
    }

    IsClientActive = true;

    Player.StartPlaying();
    Microphone.StartRecording();
    IsSendingThreadEnds = false;
    IsAcceptingThreadEnds = false;
    new std::thread(&Client::Accepting, this);
    new std::thread(&Client::Sending, this);

    return true;
}

bool Client::ConnectToServer(const char* IP, unsigned short Port,
                             const char* RecordingFileName)
{
    if (IsClientActive)
    {
        return false;
    }
    if (!IsClientConfigured)
    {
        IsClientConfigured = InitWSA();
        if (!IsClientConfigured)
        {
            return false;
        }
    }

    struct sockaddr_in fordata;
    // binding the socket
    fordata.sin_family = AF_INET;
    fordata.sin_port = htons(Port);
    fordata.sin_addr.s_addr = inet_addr(IP);
    if (connect(m_socket, reinterpret_cast<SOCKADDR*>(&fordata), sizeof(fordata)) < 0)
    {
        std::cout << "Connection error\n";
        closesocket(m_socket);
        return false;
    }

    IsClientActive = true;

    Player.StartPlayingAndRecordingToFile(RecordingFileName);
    Microphone.StartRecording();
    IsSendingThreadEnds = false;
    IsAcceptingThreadEnds = false;
    new std::thread(&Client::Accepting, this);
    new std::thread(&Client::Sending, this);

    return true;
}

void Client::DisconnectFromServer()
{
    if (!IsClientActive || !IsClientConfigured)
    {
        std::cout << "Client is not active or config. Disconnecting\n ";
        return;
    }
    std::cout << "Disconnecting\n";
    IsClientActive = false;
    Mute = true;
    while (!IsSendingThreadEnds)
    {
        Sleep(1);  // Необходимо для корректной работы
    }
    Player.StopPlaying();
    Microphone.StopRecording();
    // Ждем завершения всех потоков, кроме потока приема данных от сервера
    // (он завершится с закрытием сокета)
    while (!IsSendingThreadEnds || IsClientActive || Player.IsPlayingInProgress() ||
           Microphone.IsRecordInProgress() || IsAudioPlayingNow)
    {
        Sleep(1);// Необходимо для корректной работы
    }
    SendDisconnectCode();
    closesocket(m_socket);
}

void Client::OneSideDisconnect()
{
    if (!IsClientActive || !IsClientConfigured)
    {
        std::cout << "Client is not active or config. Disconnecting\n ";
        return;
    }
    std::cout << "Disconnecting\n";
    IsClientActive = false;
    Mute = true;
    while (!IsSendingThreadEnds)
    {
    }
    Player.StopPlaying();
    Microphone.StopRecording();
    // Ждем завершения всех потоков, кроме потока приема данных от сервера
    // (он завершится с закрытием сокета)
    while (!IsSendingThreadEnds || IsClientActive || Player.IsPlayingInProgress() ||
           Microphone.IsRecordInProgress() || IsAudioPlayingNow)
    {
    }
    closesocket(m_socket);
}

bool Client::SetMute(bool IsMute)
{
    if (IsMute)
    {
        Mute = IsMute;
        // Ждем отправки последнего пакета
        while (Microphone.IsRecordInProgress())
        {
            // Нужна задержка для корректной работы
            Sleep(1);
        }
        SendMuteCode();
        return true;
    }
    else
    {
        Mute = !SendSpeakCode();
        if (Mute == IsMute)
        {
            return true;
        }
    }
    return false;
}
bool Client::InitWSA()
{
    // initialize
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        std::cout << "Error in WSAStartup()\n";
        return false;
    }

    // creating a socket
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET)
    {
        std::cout << "Error when creating a socket\n" << WSAGetLastError();
        WSACleanup();
        return false;
    }
    return true;
}
//Данная функция принимает данные от клиента и после их обработки записывает в файл
bool Client::RecvFile()
{
    //константные переменные для определения размера массива
    const int BUFFER_SIZE = 12000;
    const int FILE_NAME_SIZE = 200;
    const int FILE_SIZE = 20;

    // флаг для разделения имени файла и его размера
    // тк он приходит в особом формате
    bool flag = true;

    // сообщение выглядит <ИмяФайла|РазмерФайла*\0>

    // необходимо два счетчика тк ТСР часто склеивает потоки данных в один
    // поэтому необходимо проверить
    // отправилось ли только сообщение
    // или сообщение+часть буффера в который считаны данные с файла

    int sizeFileCount = 0;  // счетчик для выделения из сообщения размера файла для записи
    int SizeDataCount = 0;  // размер целого сообщения
    int recvSize = 1;       // размер принятого сообщения

    int FileSize;  // размер файла

    // массивы для данных
    char buf[BUFFER_SIZE]{};  // буффер для считывания получения данных и запись их в файл
    char FileName[FILE_NAME_SIZE -
                  FILE_SIZE]{};  // массив для имени файла и открытии в функции fopen
    char
        FileNameAndLen[FILE_NAME_SIZE];  // сообщение от сервера <ИмяФайла|РазмерФайла*\0>
    char FileLen[FILE_SIZE]{};  // Размер файла

    FILE* file;

    // принимаем сообщение
    recvSize = recv(m_socket, FileNameAndLen, FILE_NAME_SIZE, 0);

    if (recvSize == SOCKET_ERROR)
        return false;

    FileNameAndLen[0] = '1';

    //разделения сообщения на ИмяФайла и РазмерФайла
    for (int i = 0; i < recvSize; i++)
    {
        //звездочка означает конец сообщения
        if (FileNameAndLen[i] == '*')
        {
            FileLen[sizeFileCount] = '\0';
            break;
        }

        //закончилось Имя Файла
        if (FileNameAndLen[i] == '|' && flag)
        {
            flag = false;
            FileName[i] = '\0';
        }
        //считываем ИмяФайла
        else if (flag)
            FileName[i] = FileNameAndLen[i];
        //отделяем длинну данных считанных из файла
        else
            FileLen[sizeFileCount++] = FileNameAndLen[i];

        SizeDataCount++;  //считаем размер сообщения
    }
    SizeDataCount += 2;

    // 	wb - creates a binary file for writing
    file = fopen(FileName, "wb");
    //переодчим размер массива из char в int
    FileSize = atoi(FileLen);

    //проверка на то
    //добавилось ли к сообщение данные считанные из файл
    int SizeRecvData = 0;  //длина приятых данных
    if (SizeDataCount != recvSize)
    {
        char* mes = new char[FILE_NAME_SIZE - SizeDataCount]{};
        //отделяем данные файла
        for (int i = SizeDataCount; i < FILE_NAME_SIZE; i++)
            mes[i - SizeDataCount] = FileNameAndLen[i];

        //записываем их
        fwrite(mes, 1, FILE_NAME_SIZE - static_cast<size_t>(SizeDataCount), file);

        SizeRecvData = FILE_NAME_SIZE - SizeDataCount;
        delete[] mes;
    }

    // we accept files in packages from another client
    while (1)
    {
        //если длина след пакета меньше BUFFER_SIZE
        //то необходдимо изменить размера буффера ожидающего свое заполнение
        //после полного заполнения выход из цикла
        if (FileSize - SizeRecvData < BUFFER_SIZE)
        {
            recvSize = recv(m_socket, buf, FileSize - SizeRecvData, 0x8);
            fwrite(buf, 1, recvSize, file);
            break;
        }
        //принимаем файла от сервера
        else
        {
            recvSize = recv(m_socket, buf, BUFFER_SIZE, 0x8);
            fwrite(buf, 1, recvSize, file);  // we write data in bytes to the created file
            SizeRecvData += recvSize;
        }

        // checking if an error occurred when sending the file (the client disconnected,
        // etc.)
        // then the cycle ends
        if (recvSize == SOCKET_ERROR)
            return false;
    }

    fclose(file);
    printf("recv");

    //открываем наш файл
    std::string SystemCommand = "start ";
    SystemCommand += FileName;
    system(SystemCommand.c_str());

    return true;
}

//для отправки данных используется имя файла введенное пользователем
//после этого с помощью fopen открывается файл
//считывается имя и размер файла
//и отправляются на сервер
//далее считываются данные из файла и потоками отправляются на сервер
//завершается выполнение после завершения отправки файла
bool Client::SendFile(const char* FileName)
{
    //константные переменнные для задания размеров массива
    const int FILE_SIZE = 20;
    const int BUFFER_SIZE = 12000;

    int Offset;    //смещение в файле относительно начала
    int FileSize;  //размер файла

    char buffer[BUFFER_SIZE]{};  // буффер для чтения данных с файла и отправки
    char* NameAndSize;  //массив для имени и размера файла <ИмяФайла|РазмерФайла*\0>

    FILE* file;
    file = fopen(FileName, "rb");  // rb - открываем двоичный файл для чтения

    // проверка, что файл найден
    if (file == nullptr)
    {
        std::cout << "File not exists!" << std::endl;
        return false;
    }

    //отправляем серверу FILE_CODE
    //чтобы он обработал наши данные верно и запустил необходимые функции
    if (!SendFileCode())
        return false;

    // вычилсяем размер отправляемого файла, для этого переносим указатель файла в конец
    // и считываем его текущее положение
    fseek(file, 0, SEEK_END);
    FileSize = ftell(file);

    //для отправки размера файла необходимо привести его к типу char
    char sizeFile[FILE_SIZE];
    itoa(FileSize, sizeFile, 10);

    int LenFileName = strlen(FileName);  //длина имя файла
    int LenSiziFile = strlen(sizeFile);  //длина размера файла

    int size = LenFileName + LenSiziFile + 3;  // общая длина сообщения

    NameAndSize = new char[size];  //выделяем память под отправку сообщения
                                   //<ИмяФайла|РазмерФайла*\0>

    //заносим размер и имя файла в один буфер для отправки
    for (int i = 0; i < size - 2; i++)
    {
        if (i < LenFileName)
            NameAndSize[i] = FileName[i];
        else if (i == LenFileName)
            NameAndSize[i] = '|';
        else
            NameAndSize[i] = sizeFile[i - LenFileName - 1];
    }
    NameAndSize[size - 2] = '*';
    NameAndSize[size - 1] = '\0';

    if (send(m_socket, NameAndSize, size, 0) == SOCKET_ERROR)  // отправляем сообщение
    {
        std::cout << "Message not send!" << std::endl;
        return false;
    }

    size_t readingSize = 1;
    int SendSize = 0;
    std::cout << "Sending...\n";

    Offset = 0;
    // пока размер файла меньше смещения в нем
    // и пока считанный размер больше 0
    // то считываем данные в буфер и отправляем их
    // std::cout << FileSize << "- FileSize\n";
    while (Offset < FileSize && readingSize > 0)
    {
        // сдвигаем указатель в файле на количество считанных байт
        fseek(file, Offset, SEEK_SET);
        // считываем данные с файла в буффер
        readingSize = fread(buffer, 1, BUFFER_SIZE, file);

        SendSize = send(m_socket, buffer, readingSize, 0);  // отправляем поток данных

        if (SendSize == SOCKET_ERROR)
        {
            std::cout << "File NOT sended\n";
            return false;
        }

        Offset += readingSize;  //смещение в файле
        /*
        std::cout << Offset << "Offset\n";
        if (Offset >= FileSize - 12000)
        {
            std::cout << readingSize << "readingSize\n";
            std::cout << SendSize << "SendSize\n";
            std::cout << "Offset >= FileSize - 24000\n";
        }
        if (Offset == FileSize)
        {
            std::cout << "Offset == FileSize\n";
        }
        */
    }

    fclose(file);
    std::cout << "File sended\n";
    delete[] NameAndSize;

    return true;
}

int* Client::RecieveIntServerMessage(SOCKET& ServerSocket, int& SizeOfIntArray)
{
    SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
    int RecieveCode = SOCKET_ERROR;
    int InputMessageSize;

    // Получаем размер принимаемого сообщения
    RecieveCode = recv(ServerSocket, reinterpret_cast<char*>(&InputMessageSize),
                       sizeof(int), MSG_WAITALL);

    std::cout << "Recieve Server Message. RecieveCodeSize: " << RecieveCode
              << "; InputMessageSize: " << InputMessageSize << std::endl;

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << " Recive message Size Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    if (InputMessageSize < 0)
    {
        std::cout << " This is a code\n";
        SizeOfIntArray = InputMessageSize;
        return nullptr;
    }

    // Нужна задержка, что бы сервер успел отправить новые данные
    Sleep(1);

    SizeOfIntArray = InputMessageSize / sizeof(int);
    int* InputMessage = new int[SizeOfIntArray];
    // Получаем сам массив
    RecieveCode = recv(ServerSocket, reinterpret_cast<char*>(&InputMessage[0]),
                       InputMessageSize, MSG_WAITALL);

    /*
    std::cout << "; RecieveCodeMessage: " << RecieveCode
        << "; InputMessage: " << InputMessage << std::endl;
        */

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    return InputMessage;
}

int8_t* Client::RecieveInt8ServerMessage(SOCKET& ServerSocket, int& SizeOfIntArray)
{
    SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
    int RecieveCode = SOCKET_ERROR;
    int InputMessageSize;

    // Получаем размер принимаемого сообщения
    RecieveCode = recv(ServerSocket, reinterpret_cast<char*>(&InputMessageSize),
                       sizeof(int), MSG_WAITALL);

    std::cout << "Recieve Server Message. RecieveCodeSize: " << RecieveCode
              << "; InputMessageSize: " << InputMessageSize << std::endl;

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << " Recive message Size Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    if (InputMessageSize < 0)
    {
        std::cout << " This is a code\n";
        SizeOfIntArray = InputMessageSize;
        return nullptr;
    }

    // Нужна задержка, что бы сервер успел отправить новые данные
    Sleep(1);

    SizeOfIntArray = InputMessageSize / sizeof(int8_t);
    int8_t* InputMessage = new int8_t[SizeOfIntArray];
    // Получаем сам массив
    RecieveCode = recv(ServerSocket, reinterpret_cast<char*>(&InputMessage[0]),
                       InputMessageSize, MSG_WAITALL);
    /*
    std::cout << "; RecieveCodeMessage: " << RecieveCode
        << "; InputMessage: " << InputMessage << std::endl;
        */

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    return InputMessage;
}

bool Client::SendIntArray(int* Array, int Size)
{
    int MessageSize = Size * sizeof(int);
    std::cout << "Send array to server. Array size: " << MessageSize << std::endl;
    int ReciveCode = SOCKET_ERROR;
    ReciveCode = send(m_socket, (char*)&MessageSize, sizeof(int), 0);
    // Sleep(10);
    if (ReciveCode == SOCKET_ERROR)
    {
        return false;
    }
    // std::cout << " Array: " << Array << std::endl;
    ReciveCode = send(m_socket, (char*)&Array[0], MessageSize, 0);
    // Sleep(10);
    return ReciveCode != SOCKET_ERROR;
}

bool Client::SendInt8Array(int8_t* Array, int Size)
{
    int MessageSize = Size * sizeof(int8_t);
    std::cout << "Send array to server. Array size: " << MessageSize << std::endl;
    int ReciveCode = SOCKET_ERROR;
    ReciveCode = send(m_socket, (char*)&MessageSize, sizeof(int), 0);
    // Sleep(10);
    if (ReciveCode == SOCKET_ERROR)
    {
        return false;
    }
    // std::cout << " Array: " << Array << std::endl;
    ReciveCode = send(m_socket, (char*)&Array[0], MessageSize, 0);
    // Sleep(10);
    return ReciveCode != SOCKET_ERROR;
}

void Client::SendDisconnectCode()
{
    // Ждем милисекунду, что бы у сервера было время поймать код отключения
    Sleep(1);
    std::cout << "Send disconnect code" << std::endl;
    int DisconnectCode = DISCONNECT_CODE_1;
    send(m_socket, (char*)&DisconnectCode, sizeof(int), 0);
}

bool Client::SendSpeakCode()
{
    CanClientSpeakNow = CanSpeak::WaitingForAnswer;
    std::cout << "Send speak code" << std::endl;
    int SpeakCode = SPEAK_CODE;
    if (send(m_socket, (char*)&SpeakCode, sizeof(int), 0) == SOCKET_ERROR)
    {
        std::cout << "Can not send SPEAK_CODE" << std::endl;
        return false;
    }
    while (CanClientSpeakNow == CanSpeak::WaitingForAnswer)
    {
        // Нужна задержка для корректной работы
        Sleep(1);
    }
    if (CanClientSpeakNow == CanSpeak::CanSpeakNow)
    {
        CanClientSpeakNow = CanSpeak::WaitingForAnswer;
        return true;
    }
    else
    {
        CanClientSpeakNow = CanSpeak::WaitingForAnswer;
        return false;
    }
}

bool Client::SendMuteCode()
{
    // Ждем милисекунду, что бы у сервера было время поймать код отключения
    Sleep(1);
    std::cout << "Send MUTE code" << std::endl;
    int MuteCode = MUTE_CODE;
    if (send(m_socket, (char*)&MuteCode, sizeof(int), 0) == SOCKET_ERROR)
    {
        std::cout << "Can not send MUTE_CODE" << std::endl;
        return false;
    }
}

void Client::PlayRecieveAudio(int* RecieveAudioArray, int ArraySize)
{
    if (Player.IsPlayingInProgress())
    {
        WaitForSingleObject(PlayingMutex, INFINITE);

        IsAudioPlayingNow = true;

        if (RecieveAudioArray != nullptr)
        {
            Player.PlayOnePart(RecieveAudioArray, ArraySize);
            delete[] RecieveAudioArray;
        }
        IsAudioPlayingNow = false;

        if (!ReleaseSemaphore(PlayingMutex,  // дескриптор семафора
                              1,  // увеличиваем значение счетчика на единицу
                              NULL))  // игнорируем предыдущее значение счетчика
        {
            printf("Release mutex error.\n");
        }
    }
}

void Client::Sending()
{
    while (IsClientActive)
    {
        Microphone.StartRecording();
        while (Microphone.IsRecordInProgress() && !Mute)
        {
            int ArraySize = 0;
            int* AudioArrayInt = Microphone.RecordOnePart(ArraySize);
            if (ArraySize > 0 && Microphone.GetOnePartSize() == ArraySize)
            {
                Codec MyCodec;
                int8_t* AudioArrayInt8 = MyCodec.Encode(AudioArrayInt, ArraySize);
                while (!SendInt8Array(AudioArrayInt8, ArraySize))
                {
                    if (++SendTry > MaxSendTry)
                    {
                        std::cout << "\n\nSERVER IS OUT\n\n";
                        OneSideDisconnect();
                        break;
                    }
                }
            }
        }
        Microphone.StopRecording();
    }
    IsSendingThreadEnds = true;
}

// function for accepting messages
void Client::Accepting()
{
    while (IsClientActive)
    {
        // Получение массива от сервера
        int ArraySize;
        int8_t* AudioArrayInt8 = RecieveInt8ServerMessage(m_socket, ArraySize);
        if (ArraySize < 0)
        {
            RecieveTry++;
            switch (ArraySize)
            {
                case SPEAK_CODE:
                    std::cout << "This is a speak code\n";
                    CanClientSpeakNow = CanSpeak::CanSpeakNow;
                    RecieveTry = 0;
                    break;
                case MUTE_CODE:
                    std::cout << "This is a mute code\n";
                    CanClientSpeakNow = CanSpeak::CanNotSpeakNow;
                    RecieveTry = 0;
                    break;
                case FILE_CODE:
                    std::cout << "This is a file code\n";
                    RecieveTry = 0;
                    if (RecvFile())
                        std::cout << "File recv\n";
                    else
                        std::cout << "File NOT recv\n";
                    break;
            }
            if (RecieveTry > MaxRecieveTry)
            {
                DisconnectFromServer();
                break;
            }
        }
        else
        {
            if (ArraySize != Player.GetOnePartSize())
            {
                std::cout << "Recieve Error\n";
                RecieveTry++;
                if (RecieveTry > MaxRecieveTry)
                {
                    delete[] AudioArrayInt8;
                    DisconnectFromServer();
                    break;
                }
                continue;
            }
            RecieveTry = 0;
            Codec MyCodec;
            int* AudioArrayInt = MyCodec.Decode(AudioArrayInt8, ArraySize);
            new std::thread(&Client::PlayRecieveAudio, this, AudioArrayInt, ArraySize);
        }
    }
    IsAcceptingThreadEnds = true;
}
//отправляем FILE_CODE серверу, чтобы он запустил необходимые
//функции для обработки данных
bool Client::SendFileCode()
{
    // Ждем милисекунду, что бы у сервера было время поймать код отключения
    Sleep(1);
    std::cout << "Send File code" << std::endl;
    int FileCode = FILE_CODE;
    if (send(m_socket, (char*)&FileCode, sizeof(int), 0) == SOCKET_ERROR)
    {
        std::cout << "Can not send FILE_CODE" << std::endl;
        return false;
    }

    return true;
}
