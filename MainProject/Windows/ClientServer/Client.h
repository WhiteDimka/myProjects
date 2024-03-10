#pragma once

#include "ClientServerConst.h"
#include <iostream>
#include <thread>

#include "AudioRecording/AudioRecorder.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)


/// ## Класс клиента
///
/// Данный класс реализует функционал клиента. Несколько клиентов подключаются к одному серверу. 
/// Один клиент начинает отправлять данные на сервер, остальные клиенты буду принимать данные с сервера.
/// Для подключения к серверу используется метод ConnectToServer(). 
/// После подключения к серверу клиент сразу начинает пытаться получить и воспроизвести аудио сигнал с сервера.
/// То есть клиент сразу становиться слушателем. 
/// 
/// Для отправки аудио сообщений на сервер используется метод SetMute().
/// Данный метод позволяет включать/выключать запись с микрофона и отправку на сервер записанного аудио сигнала.
/// @note Данная система не поддерживает одновременный разговор двух и более клиентов. 
/// По этому метод SetMute() не позволит включить микрофон, если другой клиент говорит в данный момент.
/// 
/// Перед отправкой аудио сигнала на сервер, данный сигнал кодируется при помощи класса Codec. 
/// @note Кодирование происходит в методе Sending()
/// 
/// Соответственно с сервера клиент получает закодированный сигнал. Следовательно, 
/// перед воспроизведением клиент декодирует полученный сигнал, посредствам того же класса Codec.
/// @note Декодирование происходит в методе Accepting().
/// 
/// Для передачи файлов используются методы RecvFile() и SendFile().
class Client
{
public:
	/// ## Конструктор по умолчанию
	/// 
	/// В данном конструкторе инициализируются флаги клиента,
	/// задается количество попыток отправить/принять сообщение сервера
	/// инициализируется мьютекс
	Client();
	/// ## Деструктор
	///
	/// При уничтожении класса, клиент должен отключиться от сервера, 
	/// что бы не нарушать его стабильную работу 
	~Client();
	/// ## Метод подключения к серверу(без записи разговора)
	/// 
	/// @param [in] IP Строка const char* содержащая ip на котором работает сервер, к которому нужно подключиться
	/// @param [in] Port unsigned short содержащий номер порта на котором работает сервер, 
	/// к которому нужно подключиться
	/// @returns true при успешном подключении к серверу, 
	/// false если не удалось подключиться к серверу
	bool ConnectToServer(const char* IP, unsigned short Port);
	/// ## Метод подключения к серверу с записью прослушиваемого звука в файл
	/// 
	/// При вызове данного метода звук воспроизводимый на данном клиенте будет записан в файл,
	/// имя которого указывается во входном параметре.
	/// @warning Имя файла должно заканчиваться на .wav
	/// @param [in] IP Строка const char* содержащая ip на котором работает сервер, к которому нужно подключиться
	/// @param [in] Port unsigned short содержащий номер порта на котором работает сервер, 
	/// к которому нужно подключиться
	/// @param [in] RecordingFileName Имя файла в который будет сохранена запись разговора.
	/// @returns true при успешном подключении к серверу, 
	/// false если не удалось подключиться к серверу
	bool ConnectToServer(const char* IP, unsigned short Port, const char* RecordingFileName);
	/// ## Метод отключения клиента от сервера
	///
	/// Данный метод вызывается при завершении работы клиента
	void DisconnectFromServer();

	/// ## Метод устанавливающий mute параметр
	///
	/// Поскольку связь идет в режиме рации, изначально все клиенты замучены.
	/// Для того, что бы клиент начал передавать запись микрофона на сервер, а от сервера другим клиентам,
	/// mute необходимо установить в false. Однако, если в данный момент говорит другой клиент, 
	/// то данную операцию провести не получится.
	/// @param [in] IsMute true - запретить клиенту говорить/false - разрешить клиенту говорить
	/// @returns true, если set прошел успешно. Set может пройти не успешно, 
	/// если в данный момент говорит другой клиент, а данный метод был вызван с параметром false
	bool SetMute(bool IsMute);

	/// ## Метод отправки файла на сервер
	///
	/// @param [in] FileName Имя файла, который находится в папке с проектом, 
	/// который будет отправлен другим клиентам
	/// @returns true, если отправка прошла успешно. false, если отправка не прошла.
	bool SendFile(const char* FileName);

private:
	SOCKET m_socket;
	AudioRecorder Microphone;
	AudioRecorder Player;
	// Данный мьютекс используется для того, 
	// что бы пришедшие с сервера аудио дорожки воспроизводились поочередно
	HANDLE PlayingMutex;

	int RecieveTry;
	int MaxRecieveTry;
	int SendTry;
	int MaxSendTry;

	bool IsClientConfigured;
	bool IsClientActive;
	bool Mute;
	// Перечисление используемое для запросов права голоса у сервера
	CanSpeak CanClientSpeakNow;

	bool IsSendingThreadEnds;
	bool IsAcceptingThreadEnds;
	bool IsAudioPlayingNow;

	bool InitWSA();

	int* RecieveIntServerMessage(SOCKET& ServerSocket, int& SizeOfIntArray);
	int8_t* RecieveInt8ServerMessage(SOCKET& ServerSocket, int& SizeOfIntArray);
	bool SendIntArray(int* Array, int Size);
	bool SendInt8Array(int8_t* Array, int Size);
	void SendDisconnectCode();
	// Отключение от сервера, не оповещая сервер
	void OneSideDisconnect();
	bool SendSpeakCode();
	bool SendMuteCode();
	bool SendFileCode();

	void PlayRecieveAudio(int* RecieveAudioArray, int ArraySize);
	void Sending();
	// function for accepting messages
	void Accepting();
	// Метод приема файла
	bool RecvFile();
};