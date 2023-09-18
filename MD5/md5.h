#pragma once
#include<string>

constexpr size_t BLOCK_SIZE = 64;
constexpr uint8_t UNIT_BIT = 0x80;

std::string md5(std::istream& stream, bool ignore_last_byte = false);

template<size_t N>
std::string hexPresentaiton(uint8_t(&data)[N])
{
	char hashstr[N * 2 + 2];
	for (int j = 0; j < N; j++)
	{
		if (data[j] < 16)
			hashstr[j * 2] = '0';
		_itoa_s(data[j], hashstr + j * 2 + (data[j] < 16 ? 1 : 0), 3, 16);
	}
	hashstr[N * 2] = 0;
	return hashstr;
};