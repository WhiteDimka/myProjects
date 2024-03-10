// Prepared by Ekaterina Ilchenko in 2022
//
// Для сборки exe: cl server.cpp ws2_32.lib
#include "Server.h"
#include "Codec/Codec.h"

Server::Server()
{
    Interference = new SignalInterference();
    Interference.turn_latency();
    IsServerActive = false;
    IsServerConfigured = InitWSA();
    numOfClients = 0;
    CurrentlySpeakingClient = ALL_CLIENTS_MUTED;
}

bool Server::InitWSA()
{
    // initialize
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        std::cout << "Error in WSAStartup()!\n";
        return false;
    }
    return true;
}

// to remove from a vector
void Server::DisconnectClient(ForClient* client)
{
    for (int i = 0; i < con.size(); i++)
    {
        if (con[i].numOfClient == client->numOfClient &&
            con[i].getsock == client->getsock)
            con.erase(con.cbegin() + i);
    }
}

int Server::SendCodeToAllOtherClients(const int IgnoreClientID, int Code)
{
    int RecieveCode = 4;

    for (ForClient CurrentClient : con)
    {
        if (CurrentClient.numOfClient == IgnoreClientID)
        {
            continue;  // pass sender
        }

        switch (Code)
        {
            case MUTE_CODE:
                if (!SendMuteCodeToClient(CurrentClient.getsock))
                {
                    std::cout << "Can not send MuteCode to client: "
                              << CurrentClient.numOfClient << std::endl;
                    RecieveCode = SOCKET_ERROR;
                }
                break;
            case SPEAK_CODE:
                if (!SendSpeakCodeToClient(CurrentClient.getsock))
                {
                    std::cout << "Can not send SpeakCode to client: "
                              << CurrentClient.numOfClient << std::endl;
                    RecieveCode = SOCKET_ERROR;
                }
                break;
            case FILE_CODE:
                if (!SendFileCodeToClient(CurrentClient.getsock))
                {
                    std::cout << "Can not send FileCode to client: "
                              << CurrentClient.numOfClient << std::endl;
                    RecieveCode = SOCKET_ERROR;
                }
                break;
        }

        if (RecieveCode < 0 || RecieveCode == SOCKET_ERROR)
        {
            std::cout << "Connection interrupted\n";
            return SOCKET_ERROR;
        }
        // std::cout << "Sent to customer number " << CurrentClient.numOfClient << " : ";
        // std::cout << Array << std::endl;
    }
    return RecieveCode;
}

bool Server::SendMuteCodeToClient(SOCKET& ClientSocket)
{
    int MuteCode = MUTE_CODE;
    std::cout << "Send MUTE_CODE to " << ClientSocket << std::endl;
    return send(ClientSocket, (char*)&MuteCode, sizeof(int), 0) != SOCKET_ERROR;
}
bool Server::SendSpeakCodeToClient(SOCKET& ClientSocket)
{
    int SpeakCode = SPEAK_CODE;
    std::cout << "Send SPEAK_CODE to " << ClientSocket << std::endl;
    return send(ClientSocket, (char*)&SpeakCode, sizeof(int), 0) != SOCKET_ERROR;
}
bool Server::SendFileCodeToClient(SOCKET& ClientSocket)
{
    int FileCode = FILE_CODE;
    std::cout << "Send FILE_CODE to " << ClientSocket << std::endl;
    return send(ClientSocket, (char*)&FileCode, sizeof(int), 0) != SOCKET_ERROR;
}

bool Server::StartServer(const char* IP, unsigned short Port)
{
    if (!IsServerConfigured)
    {
        return false;
    }

    // creating a socket
    soc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (soc == INVALID_SOCKET)
    {
        std::cout << "Error when trying to create a socket!\n" << WSAGetLastError();
        WSACleanup();
        return false;
    }

    sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_addr.s_addr = inet_addr(IP);
    ser.sin_port = htons(Port);
    if (bind(soc, reinterpret_cast<SOCKADDR*>(&ser), sizeof(ser)) == SOCKET_ERROR)
    {
        std::cout << "Error when binding a socket to a port!\n";
        closesocket(soc);
        IsServerActive = false;
        return false;
    }
    // listening
    if (listen(soc, 1) == SOCKET_ERROR)
    {
        std::cout << "Error listening to socket!\n";
        IsServerActive = false;
        return false;
    }
    IsServerActive = true;
    new std::thread(&Server::WaitingForTheClientToConnect, this);
    return true;
}

void Server::EndServer()
{
    IsServerActive = false;
    /*
    for (int i = 0; i < ClientThreads.size(); i++)
    {
        ClientThreads[i]->join();
    }
    */
}

void Server::turn_latency()
{
    Interference.turn_latency();
}

void Server::turn_loss()
{
    Interference.turn_loss();
}

void Server::turn_mixing()
{
    Interference.turn_mixing();
}

void Server::turn_noise()
{
    Interference.turn_noise();
}

void Server::set_min_latency(int val)
{
    Interference.set_min_latency(val);
}

void Server::set_max_latency(int val)
{
    Interference.set_max_latency(val);
}

void Server::set_loss_rate(int val)
{
    Interference.set_loss_rate(val);
}

void Server::set_mixing_rate(int val)
{
    Interference.set_mixing_rate(val);
}

void Server::set_noise_rate(int val)
{
    Interference.set_noise_rate(val);
}

void Server::set_noise_intensivity(int val)
{
    Interference.set_noise_intensivity(val);
}

void Server::set_latency_flag(bool Islatency)
{
    Interference.set_latency_flag(Islatency);
}

void Server::set_loss_flag(bool IsLoss)
{
    Interference.set_loss_flag(IsLoss);
}

void Server::set_mixing_flag(bool IsMixing)
{
    Interference.set_mixing_flag(IsMixing);
}

void Server::set_noise_flag(bool IsNose)
{
    Interference.set_noise_flag(IsNose);
}

void Server::DisableInterference()
{
    set_latency_flag(false);
    set_loss_flag(false);
    set_mixing_flag(false);
    set_noise_flag(false);
}

void Server::WaitingForTheClientToConnect()
{
    std::cout << "Server waiting for the client to connect...\n";
    while (IsServerActive)
    {
        // we accept the connection
        SOCKET Sock;
        while (IsServerActive)
        {
            Sock = SOCKET_ERROR;
            while (Sock == SOCKET_ERROR)
            {
                struct sockaddr_in client;
                int len = sizeof(client);
                Sock = accept(soc, (struct sockaddr*)&client, &len);
                ForClient* data =
                    new ForClient{Sock, client, numOfClients};  // creating a client
                con.push_back(ForClient(Sock, client, numOfClients));
                numOfClients++;
                if (numOfClients == 1000)
                    numOfClients = 0;
                new std::thread(&Server::Mail, this, data);
                // ClientThreads.push_back(new std::thread(&Server::Mail, this, data));
            }
            break;
        }
    }
}

// Function for receiving and sending messages to clients
void Server::Mail(ForClient* g)
{
    ForClient* data = reinterpret_cast<ForClient*>(g);
    SOCKET getsock = data->getsock;
    struct sockaddr_in soccl = data->soccl;
    int clientNum = data->numOfClient;
    std::cout << "Client number : " << clientNum
              << " connected with IP: " << inet_ntoa(soccl.sin_addr) << std::endl;

    if (CurrentlySpeakingClient != ALL_CLIENTS_MUTED)
    {
        SendMuteCodeToClient(getsock);
    }

    // Получение данных от клиента
    ClientHandler(getsock, clientNum);

    std::cout << "Client number: " << clientNum
              << "\ndisconnected with IP: " << inet_ntoa(soccl.sin_addr) << std::endl;
    DisconnectClient(data);
    closesocket(getsock);
    delete (data);
}

void Server::ClientHandler(SOCKET& ClientSocket, const int ClientID)
{
    // Если не смогли получить сообщение от клиента MaxConnectedTry раз считаем что клиент
    // отключился
    const int MaxConnectedTry = 50;
    int ConnectionTry = 0;  // Текущая попытка подключения
    while (ConnectionTry < MaxConnectedTry && IsServerActive)
    {
        int ArraySize;
        int8_t* Array = RecieveInt8ClientMessage(ClientSocket, ArraySize);
        if (ArraySize < 0)
        {
            switch (ArraySize)
            {
                case DISCONNECT_CODE_1:
                    std::cout << "Client send disconnect code\n";
                    // Условие выхода из внешнего цикла
                    ConnectionTry = MaxConnectedTry + 1;
                    break;
                case RECIEVE_DATA_ERROR_CODE:
                    ConnectionTry++;
                    break;
                case MUTE_CODE:
                    std::cout << "Recive mute code from: " << ClientID << std::endl;
                    if (CurrentlySpeakingClient == ClientID)
                    {
                        std::cout << "Mute all!" << std::endl;
                        CurrentlySpeakingClient = ALL_CLIENTS_MUTED;
                    }
                    break;
                case SPEAK_CODE:
                    if (CurrentlySpeakingClient == ALL_CLIENTS_MUTED ||
                        CurrentlySpeakingClient == ClientID)
                    {
                        CurrentlySpeakingClient = ClientID;
                        std::cout << ClientSocket << std::endl;
                        if (!SendSpeakCodeToClient(ClientSocket))
                        {
                            std::cout << "Can not send SPEAK_CODE to client: " << ClientID
                                      << std::endl;
                            CurrentlySpeakingClient = ALL_CLIENTS_MUTED;
                        }
                    }
                    else
                    {
                        if (!SendMuteCodeToClient(ClientSocket))
                        {
                            std::cout << "Can not send MUTE_CODE to client: " << ClientID
                                      << std::endl;
                        }
                    }
                    break;
                case FILE_CODE:
                    if (!FileDistribution(ClientSocket, ClientID))
                        std::cout << "File sent to All clients" << std::endl;
                    else
                        std::cout << "File Not sent" << std::endl;
                    break;
                default:
                    ConnectionTry++;
                    break;
            }
        }
        else
        {
            // Реализация помех внешней среды
            Interference.run(ArraySize, (char*)Array);

            ConnectionTry = 0;
            if (SendInt8MessageToAllOtherClients(Array, ArraySize, ClientID) ==
                SOCKET_ERROR)
            {
                std::cout << "Client number: " << ClientID << " Can not Send Array\n";
            };
        }
        if (Array != nullptr)
        {
            delete[] Array;
            Array = nullptr;
        }
    }
    if (CurrentlySpeakingClient == ClientID)
    {
        CurrentlySpeakingClient = ALL_CLIENTS_MUTED;
    }
}

int* Server::RecieveIntClientMessage(SOCKET& ClientSocket, int& SizeOfIntArray)
{
    SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
    int RecieveCode = SOCKET_ERROR;
    int InputMessageSize;

    // Получаем размер принимаемого сообщения
    RecieveCode = recv(ClientSocket, reinterpret_cast<char*>(&InputMessageSize),
                       sizeof(int), MSG_WAITALL);

    std::cout << "Client: " << ClientSocket << "; InputMessageSize: " << InputMessageSize
              << std::endl;

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Size Error!\n";

        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }

    if (InputMessageSize == DISCONNECT_CODE_1 || InputMessageSize == SPEAK_CODE ||
        InputMessageSize == MUTE_CODE || InputMessageSize == FILE_CODE)
    {
        std::cout << " this is a code!\n";
        SizeOfIntArray = InputMessageSize;
        return nullptr;
    }

    if (InputMessageSize < 0)
    {
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    SizeOfIntArray = InputMessageSize / sizeof(int);

    int* InputMessage = new int[SizeOfIntArray];
    // Получаем сам массив
    RecieveCode = recv(ClientSocket, reinterpret_cast<char*>(&InputMessage[0]),
                       InputMessageSize, MSG_WAITALL);
    /*
    std::cout << "Client: " << ClientSocket << "; InputMessage: " << InputMessage
        << std::endl;
        */

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    return InputMessage;
}

int8_t* Server::RecieveInt8ClientMessage(SOCKET& ClientSocket, int& SizeOfIntArray)
{
    SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
    int RecieveCode = SOCKET_ERROR;
    int InputMessageSize;

    // Получаем размер принимаемого сообщения
    RecieveCode = recv(ClientSocket, reinterpret_cast<char*>(&InputMessageSize),
                       sizeof(int), MSG_WAITALL);

    std::cout << "Client: " << ClientSocket << "; InputMessageSize: " << InputMessageSize
              << std::endl;

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Size Error!\n";

        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }

    if (InputMessageSize == DISCONNECT_CODE_1 || InputMessageSize == SPEAK_CODE ||
        InputMessageSize == MUTE_CODE || InputMessageSize == FILE_CODE)
    {
        std::cout << " this is a code!\n";
        SizeOfIntArray = InputMessageSize;
        return nullptr;
    }

    if (InputMessageSize < 0)
    {
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    SizeOfIntArray = InputMessageSize / sizeof(int8_t);

    int8_t* InputMessage = new int8_t[SizeOfIntArray];
    // Получаем сам массив
    RecieveCode = recv(ClientSocket, reinterpret_cast<char*>(&InputMessage[0]),
                       InputMessageSize, MSG_WAITALL);

    /*
    std::cout << "Client: " << ClientSocket << "; InputMessage: " << InputMessage
        << std::endl;
        */

    if (RecieveCode == SOCKET_ERROR)
    {
        std::cout << "Recive message Error!\n";
        SizeOfIntArray = RECIEVE_DATA_ERROR_CODE;
        return nullptr;
    }
    return InputMessage;
}

int Server::SendIntMessageToClient(SOCKET& ClientSocket, const int* Array,
                                   const int ArraySize)
{
    int RecieveCode = SOCKET_ERROR;
    int MessageSize = ArraySize * sizeof(int);

    std::cout << "Send array to client " << ClientSocket
              << "; MessageSize: " << MessageSize;
    RecieveCode = send(ClientSocket, (char*)&MessageSize, sizeof(int), 0);
    std::cout << "; RecieveCode1 " << RecieveCode;

    if (RecieveCode == SOCKET_ERROR)
    {
        return SOCKET_ERROR;
    }
    // std::cout << "; Array: " << Array << std::endl;
    RecieveCode = send(ClientSocket, (char*)&Array[0], MessageSize, 0);
    return RecieveCode;
}

int Server::SendInt8MessageToClient(SOCKET& ClientSocket, const int8_t* Array,
                                    const int ArraySize)
{
    int RecieveCode = SOCKET_ERROR;
    int MessageSize = ArraySize * sizeof(int8_t);

    std::cout << "Send array to client " << ClientSocket
              << "; MessageSize: " << MessageSize;
    RecieveCode = send(ClientSocket, (char*)&MessageSize, sizeof(int), 0);
    std::cout << "; RecieveCode1 " << RecieveCode;

    if (RecieveCode == SOCKET_ERROR)
    {
        return SOCKET_ERROR;
    }
    // std::cout << "; Array: " << Array << std::endl;
    RecieveCode = send(ClientSocket, (char*)&Array[0], MessageSize, 0);
    return RecieveCode;
}

// сервер принимает от клиента данные с файла
// и отправляет их все кроме клиента отправившего файл
bool Server::FileDistribution(SOCKET& ClientSocket, const int IgnoreClientID)
{
    SendCodeToAllOtherClients(IgnoreClientID, FILE_CODE);

    int recvSize;
    const int BUFFER_SIZE = 12000;
    char buf[BUFFER_SIZE];
    char FileName[200]{};

    char FileNameSize[200]{},
        FileSizeBuf[20]{};  // receive the file name from another client
    recvSize = recv(ClientSocket, FileNameSize, 200, 0);

    bool flag = true;
    int sizeBuf = 0;
    int sizeMes = 0;


    for (int i = 0; i < recvSize; i++)
    {
        if (FileNameSize[i] == '*')
        {
            FileSizeBuf[sizeBuf] = '\0';
            break;
        }

        if (FileNameSize[i] == '|' && flag)
        {
            flag = false;
            FileName[i] = '\0';
        }
        else if (flag)
            FileName[i] = FileNameSize[i];
        else
            FileSizeBuf[sizeBuf++] = FileNameSize[i];
        sizeMes++;
    }

    sizeMes += 2;

    SendFileMessageToAllOtherClients(FileNameSize, recvSize, IgnoreClientID);

    if (recvSize == SOCKET_ERROR)
    {
        std::cout << "\n```````````````````````````````````````````[FileName]|\n";
        return true;
    }

    int FileSize = atoi(FileSizeBuf);

    int offset = 0;

    if (sizeMes != recvSize)
    {
        char* mes = new char[200 - sizeMes]{};
        //отделяем данные файла
        for (int i = sizeMes; i < 200; i++) mes[i - sizeMes] = FileNameSize[i];

        //записываем их
        SendFileMessageToAllOtherClients(mes, 200 - recvSize, IgnoreClientID);

        offset = 200 - sizeMes;
        delete[] mes;
    }


    // std::cout << FileSize << "- FileSize]|\n";
    while (1)
    {
        if (FileSize - offset < BUFFER_SIZE)
        {
            // std::cout << FileSize - offset << "- offset\n";
            recvSize = recv(ClientSocket, buf, FileSize - offset, 0x8);
            // std::cout << recvSize << "- recvSize\n";
            SendFileMessageToAllOtherClients(buf, recvSize, IgnoreClientID);
            offset += recvSize;
            // std::cout << offset << "- offset\n";
            break;
        }
        else
        {
            recvSize = recv(ClientSocket, buf, BUFFER_SIZE, 0x8);

            SendFileMessageToAllOtherClients(buf, recvSize, IgnoreClientID);
            offset += recvSize;
        }
        //std::cout << offset << "- offset\n";
    }

    // checking if an error occurred when sending the file (the client disconnected, etc.)
    // then the cycle ends
    if (recvSize == SOCKET_ERROR)
    {
        return true;
    }

    return false;
}

int Server::SendFileMessageToAllOtherClients(const char Array[], const int ArraySize,
                                             const int IgnoreClientID)
{
    int RecieveCode = 4;

    for (ForClient CurrentClient : con)
    {
        if (CurrentClient.numOfClient == IgnoreClientID)
        {
            continue;  // pass sender
        }

        RecieveCode = send(CurrentClient.getsock, Array, ArraySize, 0);

        if (RecieveCode < 0 || RecieveCode == SOCKET_ERROR)
        {
            std::cout << "Connection interrupted\n";
            return SOCKET_ERROR;
        }
    }
    return RecieveCode;
}

int Server::SendIntMessageToAllOtherClients(const int* Array, const int ArraySize,
                                            const int IgnoreClientID)
{
    int RecieveCode = 4;

    for (ForClient CurrentClient : con)
    {
        if (CurrentClient.numOfClient == IgnoreClientID)
        {
            continue;  // pass sender
        }

        RecieveCode = SendIntMessageToClient(CurrentClient.getsock, Array, ArraySize);

        if (RecieveCode < 0 || RecieveCode == SOCKET_ERROR)
        {
            std::cout << "Connection interrupted\n";
            return SOCKET_ERROR;
        }
    }
    return RecieveCode;
}

int Server::SendInt8MessageToAllOtherClients(const int8_t* Array, const int ArraySize,
                                             const int IgnoreClientID)
{
    int RecieveCode = 4;

    for (ForClient CurrentClient : con)
    {
        if (CurrentClient.numOfClient == IgnoreClientID)
        {
            continue;  // pass sender
        }

        RecieveCode = SendInt8MessageToClient(CurrentClient.getsock, Array, ArraySize);

        if (RecieveCode < 0 || RecieveCode == SOCKET_ERROR)
        {
            std::cout << "Connection interrupted\n";
            return SOCKET_ERROR;
        }
    }
    return RecieveCode;
}
