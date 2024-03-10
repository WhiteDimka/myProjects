#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>

void sleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

void sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000);
}
#endif

#if defined(max) //прописано для корректной работы max(), т.к. тот также определён в <windows.h>
#undef max
#endif

#include <cstring>
#include <string>
#include <iostream>
#include <stack>
#include <limits>
#include <time.h>

#include "Signal_Interference.h"

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable: 4996)

//const int BUFFER_SIZE = 2000;//размер буфера

SignalInterference::SignalInterference(bool f_latency, bool f_loss, bool f_mixing, bool f_noise)
{
	flag_latency_ = f_latency;
	flag_loss_ = f_loss;
	flag_mixing_ = f_mixing;
	flag_noise_ = f_noise;
}

SignalInterference::SignalInterference(const SignalInterference& arg) //конструктор копий
{
	flag_latency_ = arg.flag_latency_;
	flag_loss_ = arg.flag_loss_;
	flag_mixing_ = arg.flag_mixing_;
	flag_noise_ = arg.flag_noise_;

	min_latency_ = arg.min_latency_;
	max_latency_ = arg.max_latency_;
	loss_rate_ = arg.loss_rate_;
	mixing_rate_ = arg.mixing_rate_;
	noise_rate_ = arg.noise_rate_;

	strncpy(lost_packet_, arg.lost_packet_, BUFFER_SIZE);

}

SignalInterference::~SignalInterference() //деструктор
{
	
}

void SignalInterference::turn_latency() //вкл/выкл задержки
{
	flag_latency_ = flag_latency_ ^ true;
}
void SignalInterference::set_latency_flag(bool Islatency) //вкл/выкл задержки
{
	flag_latency_ = Islatency;
}

void SignalInterference::turn_loss() //вкл/выкл потери пакетов
{
	flag_loss_ = flag_loss_ ^ true;
}

void SignalInterference::set_loss_flag(bool IsLoss) //вкл/выкл потери пакетов
{
	flag_loss_ = IsLoss;
}

void SignalInterference::turn_mixing() //вкл/выкл перемешивания пакетов
{
	flag_mixing_ = flag_mixing_ ^ true;
}
void SignalInterference::set_mixing_flag(bool IsMixing) //вкл/выкл перемешивания пакетов
{
	flag_mixing_ = IsMixing;
}
void SignalInterference::turn_noise() //вкл/выкл шумов
{
	flag_noise_ = flag_noise_ ^ true;
}
void SignalInterference::set_noise_flag(bool IsNose)
{
	flag_noise_ = IsNose;
}

void SignalInterference::set_min_latency(int val) //установить минимальную задержку
{
	if (val >= 0)
		min_latency_ = val;
	else 
		min_latency_ = 0;
	if (max_latency_ <= min_latency_)
		max_latency_ = min_latency_ + 1;
}

void SignalInterference::input_min_latency() //ввести минимальную задержку
{
	int temp = 0;
	std::cin >> temp;

	if ((std::cin.fail()) || temp < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //первый аргумент в cin.ignore( , ) используется для переносимости определения максимального размера буфера
		min_latency_ = 0;
	}
	else {
		min_latency_ = temp;
	}
	if (max_latency_ <= min_latency_)
		max_latency_ = min_latency_ + 1;
}

int SignalInterference::get_min_latency() //получить значение минимальной задержки
{
	return min_latency_;
}

void SignalInterference::set_max_latency(int val) //установить максимальную задержку
{
	if (val > min_latency_)
		max_latency_ = val;
	else
		max_latency_ = min_latency_ + 1;
}

void SignalInterference::input_max_latency() //ввести максимальную задержку
{
	int temp = min_latency_;
	std::cin >> temp;

	if ((std::cin.fail()) || temp <= min_latency_) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		max_latency_ = min_latency_ + 1;
	}
	else {
		max_latency_ = temp;
	}
}

int SignalInterference::get_max_latency() //получить значение максимальной задержки
{
	return max_latency_;
}

void SignalInterference::set_loss_rate(int val) //установить вероятность потери пакетов
{
	if (val >= 0)
		loss_rate_ = val;
	else
		loss_rate_ = 0;
}

void SignalInterference::input_loss_rate() //ввести вероятность потери пакетов
{
	int temp = 0;
	std::cin >> temp;

	if ((std::cin.fail()) || temp < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		loss_rate_ = 0;
	}
	else {
		loss_rate_ = temp;
	}
}

int SignalInterference::get_loss_rate() //получить значение вероятности потери пакетов
{
	return loss_rate_;
}

void SignalInterference::set_mixing_rate(int val) //установить вероятность перемешивания пакетов
{
	if (val >= 0)
		mixing_rate_ = val;
	else
		mixing_rate_ = 0;
}

void SignalInterference::input_mixing_rate() //ввести вероятность перемешивания пакетов
{
	int temp = 0;
	std::cin >> temp;

	if ((std::cin.fail()) || temp < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		mixing_rate_ = 0;
	}
	else {
		mixing_rate_ = temp;
	}
}

int SignalInterference::get_mixing_rate() //получить значение премешивания пакетов
{
	return mixing_rate_;
}

void SignalInterference::set_noise_rate(int val) //установить вероятность появления шумов
{
	if (val >= 0)
		noise_rate_ = val;
	else
		noise_rate_ = 0;
}

void SignalInterference::input_noise_rate() //ввести вероятность появления шумов
{
	int temp = 0;
	std::cin >> temp;

	if ((std::cin.fail()) || temp < 0) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		noise_rate_ = 0;
	}
	else {
		noise_rate_ = temp;
	}
}

int SignalInterference::get_noise_rate() //получить значение вероятнсти появления шумов
{
	return noise_rate_;
}

void SignalInterference::set_noise_intensivity(int val) //установить интенсивность шумов на пакет
{
	if (val > 0 && val <= 280)
	{
		noise_intensivity_ = val;
	}
	else if (val > 280)
	{
		noise_intensivity_ = 280;
	}
	else
	{
		noise_intensivity_ = 1;
	}
}

void SignalInterference::input_noise_intensivity() //ввести интенсивность шумов на пакет
{
	int temp = 0;
	std::cin >> temp;

	if ((std::cin.fail()) || temp < 1)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		noise_intensivity_ = 1;
	}
	else if (temp > 280)
	{
		noise_intensivity_ = 280;
	}
	else
	{
		noise_intensivity_ = temp;
	}
}

int SignalInterference::get_noise_intensivity() //получить значение шумов на пакет
{
	return noise_intensivity_;
}

void SignalInterference::delay() //приватный метод для задержки перед записью пакета
{
	sleep((rand() % (max_latency_ - min_latency_) + min_latency_));
}

void SignalInterference::part_loss(char* buf) //приватный метод для копирования потерянного пакета во внутренний буфер
{
	memset(lost_packet_, 0, BUFFER_SIZE + 1);
	for (int i = 0; i < BUFFER_SIZE + 1; i++) {
		lost_packet_[i] = buf[i];
	}
}

void SignalInterference::mixing(char** buf, int current_packet_number) //приватный метод для перемешивания пакетов
{
	srand(time(NULL));
	int pos1 = 0, pos2 = 0;
	char* temp;

	if (current_packet_number < 2) //проверяем, что пришло больше 1 одного пакета для перемешивания
		return;

	while (pos1 == pos2) //выбираем две позиции из доступных для обмена пакетов местами
	{
		pos1 = rand() % current_packet_number;
		pos2 = rand() % current_packet_number;
	}

	//обмен пакетов местами
	temp = buf[pos1];
	buf[pos1] = buf[pos2];
	buf[pos2] = temp;
}

void SignalInterference::noise(char* buf)
{
	srand(time(NULL));
	char mask[8];
	mask[0] = (char)1;
	for (int i = 1; i < 8; i++) //настраиваем маски для симуляции помех
		mask[i] = mask[i - 1] << 1;

	for (int i = 0; i < noise_intensivity_; i++) //проходим цикл для установления нужного количества шумов
	{
		//int changed_packet = rand() % current_packet_number; //выбор случайного пакета для изменения
		int changed_byte = rand() % BUFFER_SIZE; //выбор случайного места искажения в пакете
		int changed_bit = rand() % 8; //выбор случайной помехи
		buf[changed_byte] = buf[changed_byte] ^ mask[changed_bit]; //применение помехи к данным
	}
}

void SignalInterference::run(int buf_size, char* buf) //запуск (всей шумихи) суммарных помех
{
	srand(time(NULL));
	int part = 0; //количество пройденных пакетов
	int packet_i = 0; //количество неутерянных пакетов
	int packet_number = buf_size / BUFFER_SIZE + 1; //предвычисляем количество пакетов

	char **temp_buf;
	temp_buf = new char *[packet_number]; //выделяем массив строк для удобства работы с пакетами
	for (int i = 0; i < packet_number; i++)
	{

		if (flag_loss_ && rand() % 100 < loss_rate_) //проверка флага и вероятности потери пакетов
		{
			this->part_loss(buf + i * BUFFER_SIZE);
			part++;
			continue;
		}

		temp_buf[packet_i] = new char[BUFFER_SIZE + 1]; //выделение памяти под непотерянный пакет
		memset(temp_buf[packet_i], 0, BUFFER_SIZE + 1);
		memcpy(temp_buf[packet_i], buf + i * BUFFER_SIZE, BUFFER_SIZE); //запись непотерянного пакета
		packet_i++;

		if (flag_noise_ && rand() % 100 < noise_rate_) //проверка флага и вероятности появления шумов
		{
			this->noise(temp_buf[packet_i - 1]);
		}

		if (flag_mixing_ && rand() % 100 < mixing_rate_) //проверка флага и вероятности перемешивания
		{
			this->mixing(temp_buf, packet_i);
		}

		if (flag_latency_) //проверка флага задержки
		{
			this->delay();
		}

		part++;
	}

	memset(buf, 0, buf_size); //очистка исходного буфера

	int CurrentIndex = 0;
	int CurrentPaket = 0;
	while (CurrentIndex < buf_size && CurrentPaket < packet_i)
	{
		buf[CurrentIndex] = temp_buf[CurrentPaket][CurrentIndex % BUFFER_SIZE];
		CurrentIndex++;
		if (CurrentIndex % BUFFER_SIZE == 0) {
		
			CurrentPaket++;
		}
		/*
		for (int i = 0; i < packet_i; i++) //запись преобразованных данных в исходный буфер
		{
			//fwrite(temp_buf[i], 1, recvSize, file); //запись буфера в файл
			memcpy(buf + i * BUFFER_SIZE, temp_buf[i], BUFFER_SIZE);
		}
		*/
	}
	
	for (int i = 0; i < packet_i; i++) //очистка использованной памяти
	{
		delete[] temp_buf[i];
	}
	delete[] temp_buf;
	
}
