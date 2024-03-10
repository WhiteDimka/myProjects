#include "Codec.h"

int8_t* Codec::Encode(int* Array, int ArraySize)
{
	return EncodeWithCodec(Array, ArraySize);
}

int* Codec::Decode(int8_t* Array, int ArraySize)
{
	return DecodeWithCodec(Array, ArraySize);
}

int8_t* Codec::EncodeWithCodec(int* Array, int ArraySize)
{
	// If array is not initialized, return
	if (ArraySize < 0)
	{
		return nullptr;
	}
	int8_t* EncodedArray = new int8_t[ArraySize];
	int CurrentElementWithoutZeroBits;
	for (int i = 0; i < ArraySize; i++)
	{
		// We can't pass 32-bit value to encode function, 
		// because it's higher than max value, that it could encode.
		// We can shift by 16 bits to the right to get 16-bit value, 
		// because, in our situation, we have only zeros in first 16 bits,
		// and we could just remove them and return after decoding
		CurrentElementWithoutZeroBits = Array[i] >> 16;
		EncodedArray[i] = G711_ALaw_Encode(CurrentElementWithoutZeroBits);
	}
	return EncodedArray;
}

int* Codec::DecodeWithCodec(int8_t* Array, int ArraySize)
{
	if (ArraySize < 0)
	{
		return nullptr;
	}
	int* DecodedArray = new int[ArraySize];
	int CurrentElementWithZeroBits;
	for (int i = 0; i < ArraySize; i++)
	{
		// Because of shifting by 16 bits before encoding, we need to return our bits,
		// what we are doing here by shifting it to the left by 16
		CurrentElementWithZeroBits = G711_ALaw_Decode(Array[i]) << 16;
		DecodedArray[i] = CurrentElementWithZeroBits;
	}
	return DecodedArray;
}

int8_t Codec::G711_ALaw_Encode(int Number)
{
	/*
	First, the number is verified is its negative. 
	If the number is negative he will be made positive and the sign variable (by default 0)
	will contain the value 0x80 (so when it's OR-ed to the coded result it will determine it's sign).

	Since the A-Law algorithm considers numbers in the range 0x000 - 0xFFF (without considering the sign bit),
	if a number is bigger than 0xFFF, it will automatically made equal to 0xFFF in order to avoid further problems.

	The first step in determining the coded value is finding the position of the first bit who has a 1 value (excluding the sign bit).
	The search is started from position 11 and is continued until a bit with the value 1 is find or until a position smaller than 5 is met.

	If the position is smaller than 5 (there was no 1 bit found on the positions 11-5),
	the least significant byte of the coded number is made equal the the bits 5,4,3,2 of the original number.
	Otherwise the least significant bit of the coded number is equal to the first four bits who come after the first 1 bit encountered.

	In the end, the most significant byte of the coded number is computed according to the position of the first 1 bit
	(if not such this was found, then the position is considered).

	Also, before returning the result, the even bits of the result will be complemented (by XOR-ing with 0x55).
	*/

	// max value, 12 bits exclude sign bit: 1111 1111 1111
	const uint16_t ALAW_MAX = 0xFFF;
	// mask for determine first 1-bit after sign bit
	uint16_t mask = 0x800;
	// part of encoded number (sign)
	uint8_t sign = 0;
	// index of a bit, we are at, right now
	uint8_t position = 11;
	// part of encoded number (least significant byte)
	uint8_t lsb = 0;
	// if number is negative
	if (Number < 0)        
	{
		// making this number positive
		Number = -Number;
		// because it was negative number, we write 0b100000000 or 0x80 to sign var, 
		// it represents 1 in sign bit of encoded value
		sign = 0x80;
	}
	// if number larger, than max number of the range: 0x000 - 0xFFF (exclude sign bit)
	if (Number > ALAW_MAX)
	{
		// making number equal to max to avoid further problems
		Number = ALAW_MAX;
	}
	// We need to find position of the first 1-bit (excluding sign bit).
	// Our needed range for position is only 7 first bits (excluding sign bit): 11,10,9,8,7,6,5
	//
	// On each cycle iteration, we getting n-th position bit,
	// and if it isn't 1-bit and position is not less, than 5, 
	// we shifting mask by 1 bit to the right and decrementing position.
	//for (; ((Number & mask) != mask && position >= 5); mask >>= 1, position--);

	for (; ((Number & mask)
		!= mask 
		&& position >= 5);
		mask >>= 1,
		position--);

	// If, after for() cycle, position is less, than 5 (we didn't find 1-bit in 11:5 bits),
	// least significant byte (lsb) is equal to 5,4,3,2 bits of the original value.
	// We writing to lsb Number without last bit
	// Else, lsb is equal to the first four bits after 1-bit.
	// Shifting original number by (position - 4(our 4 bits of original number, we writing to lsb))
	// and writing result to lsb.
	lsb = (Number >> ((position == 4) ? (1) : (position - 4)));
	// I didn't get, for what this row is
	lsb &= 0x0f;
	// In the end, we assembing encoded number using logical addition and inverting even bits of it.
	// 
	// sign = 0000 0000 or 1000 0000,
	// ((position - 4) << 4) - position of msb (most significant byte) with shift by 4 to the left
	// because we need space for lsb,
	// and lsb, we calculated earlier.
	// After assembling 8-bit number, inverting even bits via mask = 0x55 = 0b0101 0101
	return (sign | ((position - 4) << 4) | lsb) ^ 0x55;
}

int16_t Codec::G711_ALaw_Decode(int8_t Number)
{
	/*
	The first thing the decoding algorithm does is to complement the even bits of the coded number
	(since they were complemented in the coding part, complementing them again would "bring them to normal").

	The next step is to verify if the number is negative by checking if the 8th bit is set
	(if it's set, the number is negative).
	If the number is negative, the variable named sign (who is used like a flag/boolean)
	is set to -1 and the number is made positive by clearing the 8th bit.

	As you probably observed, I used a more complicated algorithm for checking the negativity of the number 
	I had to do this because my compiler had (and perhaps your would've had) problems with 8 bit variables
	and a statement like number=-number raises some problems.

	The next thing we need in order to decode the number is to determine the position we calculated in encoding algorithm.
	The position is calculated as the sum between the value represented by the most significant byte of the coded number and 4.

	The final step consists in actually decoding the number.
	The number will have its first 1 bit at the position determined before,
	the next four bits will be equal to the least significant byte of the coded number and the next bit following them will be automatically set to 1.
	If the position determined is smaller than 5, the position bit will not be set automatically (but the last 1 bit will).

	Before returning the number, if the number is negative he will have it sign added.
	*/

	// sign of decoded number
	uint8_t sign = 0x00;
	// index of a bit, we are at, right now
	uint8_t position = 0;
	// decoded number
	int16_t decoded = 0;
	// invert back even bits
	Number ^= 0x55;
	// if number is negative (in that case we will get 1-bit)
	if (Number & 0x80)
	{
		// logical mult number with 0b01111111
		Number &= ~(1 << 7);
		// set sign value to -1
		sign = -1;
	}
	// Determine the position, that was calculated in encoding algorithm.
	// Getting first 4 bits (msb) and increasing this value by 4;
	position = ((Number & 0xF0) >> 4) + 4;
	//Now, decoding...
	// 
	// If number have first 1-bit at the position, greater than 4
	if (position != 4)
	{
		// assembling decoded number
		decoded = 
			// setting first 1-bit into certain position
			((1 << position) 
			// next part of the decoded number is just value of lsb of coded number
			// getting the first 4 bits of encoded number and putting this 
			// in the certain position
			| ((Number & 0x0F) << (position - 4)) 
			// 1-bit right after lsb
			| (1 << (position - 5)));
	}
	// if number have first 1-bit at the position >= 5
	else
	{
		// Im tired, you see, what happening here, it's simple
		decoded = (Number << 1) | 1;
	}
	// if number is negative, adding negative sign
	return (sign == 0) ? (decoded) : (-decoded);
}

int8_t Codec::G711_MuLaw_Encode(int number)
{
	const uint16_t MULAW_MAX = 0x1FFF;  //максимальное значение (1 1111 1111 1111)
	const uint16_t MULAW_BIAS =
		33;  //Чтобы убедиться, что не будет числа без 1 бита в первых 12 - 5 позициях, к
			 //числу добавляется значение смещения (в данном случае 33).
	uint16_t mask = 0x1000;  //маска - 1 0000 0000 0000 (13 бит)
	uint8_t sign = 0;  //знаковая часть закодированного числа
	uint8_t position = 12;  //позиция, на каком из бите мы находимся
	uint8_t lsb = 0;  //позиция единицы в экспоненте
	if (number < 0)   //если отрицательное
	{
		number = -number;  //то меняем знак
		sign = 0x80;       //знаковый бит = 1
	}
	number += MULAW_BIAS;    //прибавляем к числу смещение
	if (number > MULAW_MAX)  //если число больше максмального
	{
		number = MULAW_MAX;  //то делаем его равным максимальному
	}
	//цикл ищет первый бит интенсивности равный 1 (биты интенсивности - экспонента)
	//в цикле если побитовое умножение маски на число не равно маске и позиция как минимум
	// 5я, то позицию уменьшаем на 1 и побитово вправо сдвигаем маску
	for (; ((number & mask) != mask && position >= 5); mask >>= 1, position--)
		;
	lsb = (number >> (position - 4)) & 0x0f;  //получаем последние 4 бита
	return (~(sign | ((position - 5) << 4) | lsb));  //получение итогового числа
}

int16_t Codec::G711_MuLaw_Decode(int8_t number)
{
	const uint16_t MULAW_BIAS = 33;  //смещение
	uint8_t sign = 0, position = 0;  //знак и позиция бита
	int16_t decoded = 0;             //результирующее число
	number = ~number;                //инверсия
	if (number & 0x80)               //провека знака числа
	{
		number &= ~(1 << 7);  //логическое умножение числа на 01111111
		sign = -1;            //знак отрицательный
	}
	position = ((number & 0xF0) >> 4) + 5;  //прыгаем по битам
	decoded =
		((1 << position) | ((number & 0x0F) << (position - 4)) | (1 << (position - 5))) -
		MULAW_BIAS;  //итоговое число
	return (sign == 0) ? (decoded)
		: (-(decoded));  //в зависимости от знака возвращаем число
}
