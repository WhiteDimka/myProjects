#include <iostream>

class Codec
{
public:
	///	## Публичный метод для кодирования 
	/// 
	/// Данный метод предназначен для вызова приватного метода EncodeWithCodec
	/// для кодирование данных с помощью кодека.
	/// @param [in] Array Указатель на массив типа int*, 
	/// в котором находятся необработанные данные
	/// @param [in] ArraySize int, содержащий размер массива
	/// @returns указатель, на закодированный массив типа int8_t*
	int8_t* Encode(int* Array, int ArraySize);
	///	## Публичный метод для декодирования 
	/// 
	/// Данный метод предназначен для вызова приватного метода DecodeWithCodec
	/// для декодирование данных с помощью кодека.
	/// @param [in] Array Указатель на массив типа int8_t*, 
	/// в котором находятся необработанные данные
	/// @param [in] ArraySize int, содержащий размер массива
	/// @returns указатель, на декодированный массив типа int*
	int* Decode(int8_t* Array, int ArraySize);
private:
	//	Метод кодирования массива из int в int8_t с помощью кодека
	int8_t* EncodeWithCodec(int* Array, int ArraySize);
	//	Метод декодирования массива из int8_t в int с помощью кодека
	int* DecodeWithCodec(int8_t* Array, int ArraySize);
	//	Кодирование с помощью кодека G711.aLaw
	int8_t G711_ALaw_Encode(int Number);
	//	Декодирование с помощью кодека G611.aLaw
	int16_t G711_ALaw_Decode(int8_t Number);
	//	Кодирование с помощью кодека G711.MuLaw
	int8_t G711_MuLaw_Encode(int number);
	//	Декодирование с помощью кодека G711.MuLaw
	int16_t G711_MuLaw_Decode(int8_t number);
};