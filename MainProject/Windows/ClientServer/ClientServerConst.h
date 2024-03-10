#pragma once

#ifdef __linux

// Инклюды специфичные для линукса

#elif defined _WIN32

#include <Windows.h>

#endif

#define DEFAULT_SERVER_IP "192.168.1.65"
#define DEFAULT_SERVER_PORT 3433

#define DISCONNECT_CODE_1 -4931
#define MUTE_CODE -4932
#define SPEAK_CODE -4933
#define FILE_CODE -4934
#define ALL_CLIENTS_MUTED -1

#define RECIEVE_DATA_ERROR_CODE -1
#define SEND_DATA_ERROR_CODE -1

// Флаг приема tcp содеинения
// при данном флаге прием будет длиться до тех пор,
// пока не будет принят весь пакет данных
#define MSG_WAITALL 0x8

/// Структура для хранения информации о клиенте
struct ForClient
{
    SOCKET getsock;  ///< Сокет клиента
    struct sockaddr_in soccl;  ///< Структура для хранения адреса клиента
    int numOfClient;  ///< Номер клиента
    /// Конструктор структуры
    ///
    /// Данный конструктор инициализирует данные о клиенте
    ForClient(const SOCKET& Sock, const sockaddr_in& client, const int& numOfClients)
        : getsock(Sock), soccl(client), numOfClient(numOfClients){};
};

enum CanSpeak
{
    CanSpeakNow,
    WaitingForAnswer,
    CanNotSpeakNow
};