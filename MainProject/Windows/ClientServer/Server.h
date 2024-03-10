#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include "ClientServerConst.h"
#include "..\ClientServer\Signal_Interference\Signal_Interference.h"
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

/// ## Класс сервера
///
/// Объект данного класса обеспечивает связь между подключенными к нему клиентами.
/// Данные пришедшие с одного подключенного клиента рассылаются всем остальным клиентам.
/// Для запуска сервера используется метод StartServer(). А для окончания его работы метод EndServer().
/// К серверу подключен модуль внесения помех в передаваемый сигнал SignalInterference. 
/// Для взаимодействия с данным модулем сервер имеет следующие методы turn_latency(),
/// turn_loss(), turn_mixing(), turn_noise(), set_min_latency(), set_max_latency(),
/// set_loss_rate(), set_mixing_rate(), set_noise_rate(), set_latency_flag(), 
/// set_loss_flag(), set_mixing_flag() и set_noise_flag().
/// 
/// Для каждого подключенного клиента сервер запускает отедльный поток обработки сигналов данного клиента.
/// Клиент присылает сигнал двумя командами. Первой командой передается размер массива аудио сигнала, 
/// а второй командой сам массив. Если размер массива отрицательный, то это либо ошибка передачи, 
/// либо один из кодов команд для сервера. В зависимости от конкретного кода, пришедшего от клиента,
/// работа сервера меняется - сервер совершает действие соответствующие полученному коду, 
/// а затем продолжает ожидать размер массива от клиента.
class Server
{
public:
	/// ## Конструктор по умолчанию
	Server();
	/// ## Метод запуска сервера 
	///
	/// @param [in] IP Строка const char* содержащая ip на котором должен запустится сервер
	/// @param [in] Port unsigned short содержащий номер порта на котором будет запускаться сервер
	/// @returns true при успешном запуске сервера, 
	/// false если сервер не получилось запустить с данными параметрами
	bool StartServer(const char* IP, unsigned short Port);
	/// ## Метод окончания работы сервера
	void EndServer();

	/// ## Вкл/выкл задержки
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void turn_latency(); 
	/// ## Вкл/выкл потери пакетов
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void turn_loss(); 
	/// ## Вкл/выкл перемешивания пакетов
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void turn_mixing(); 
	/// ## Вкл/выкл шумов
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void turn_noise();
	/// ## Установить минимальную задержку передачи сигнала
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_min_latency(int val); 
	/// ## Установить максимальную задержку передачи сигнала
	///
	/// Задержка сигнала измеряется в миллисекундах.
	/// @attention Задержка сигнала расчитывается для каждого переданного пакета, 
	/// так что если за одну передачу будет переданно несколько пакетов, 
	/// передача будет длится задержка умноженная на количество передаваемых пакетов.
	/// Размер одного пакета 2048 байт
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_max_latency(int val); 
	/// ## Установить вероятность потери пакетов
	///
	/// Вероятность потери пакетов устанавливается в диапазоне от 0% до 100%
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_loss_rate(int val); 
	/// ## Установить вероятность перемешивания пакетов
	///
	/// Вероятность перемешивания пакетов устанавливается в диапазоне от 0% до 100%
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_mixing_rate(int val); 
	/// ## Установить вероятность появления шумов
	///
	/// Вероятность появления шумов устанавливается в диапазоне от 0% до 100%
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_noise_rate(int val); 
	/// ## Установить интенсивность шумов на пакет
	///
	/// Интенсивность шумов на пакет устанавливается в диапазоне от 0 до 280
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_noise_intensivity(int val); 
	/// ## Установка включения модуля задержки передачи сигнала
	///
	/// @param [in] Islatency Включить ли модуль задержки передачи сигнала
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_latency_flag(bool Islatency);
	/// ## Установка включения модуля потери пакетов
	///
	/// @param [in] IsLoss Включить ли модуль потери пакетов
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_loss_flag(bool IsLoss);
	/// ## Установка включения модуля перемешивания пакетов
	///
	/// @param [in] IsMixing Включить ли модуль перемешивания пакетов
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_mixing_flag(bool IsMixing);
	/// ## Установка включения модуля добавления шумов
	///
	/// @param [in] IsNose Включить ли модуль добавления шумов 
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void set_noise_flag(bool IsNose);
	/// ## Выключить все модули внесения помех в передаваемый сигнал
	///
	/// @note Метод для взаимодействия с модулем внесения помех в передаваемый сигнал
	void DisableInterference();

private:
	// Список подключеных клиентов
	std::vector<ForClient> con;
	// Сокет на котором запускается сервер
	SOCKET soc;
	//std::vector<std::thread*> ClientThreads;
	int numOfClients;

	SignalInterference Interference;

	bool IsServerConfigured;
	bool IsServerActive;
	int CurrentlySpeakingClient;

	bool InitWSA();
	void WaitingForTheClientToConnect();

	// Method for receiving and sending messages to clients
	void Mail(ForClient* g);

	void ClientHandler(SOCKET& ClientSocket, const int ClientID);

	int* RecieveIntClientMessage(SOCKET& ClientSocket, int& SizeOfIntArray);
	int8_t* RecieveInt8ClientMessage(SOCKET& ClientSocket, int& SizeOfIntArray);
	int SendIntMessageToClient(SOCKET& ClientSocket, const int* Array, const int ArraySize);
	int SendInt8MessageToClient(SOCKET& ClientSocket, const int8_t* Array, const int ArraySize);
	int SendFileMessageToAllOtherClients(const char Array[], const int ArraySize,
		const int IgnoreClientID);
	int SendIntMessageToAllOtherClients(const int* Array, const int ArraySize,
		const int IgnoreClientID);
	int SendInt8MessageToAllOtherClients(const int8_t* Array, const int ArraySize,
		const int IgnoreClientID);
	void DisconnectClient(ForClient* client);

	int SendCodeToAllOtherClients(const int IgnoreClientID, int Code);
	bool SendMuteCodeToClient(SOCKET& ClientSocket);
	bool SendSpeakCodeToClient(SOCKET& ClientSocket);
	bool SendFileCodeToClient(SOCKET& ClientSocket);

	bool FileDistribution(SOCKET& ClientSocket, const int IgnoreClientID);
};