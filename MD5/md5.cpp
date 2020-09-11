#include<iostream>
#include<string>
#include<strstream>
#include<fstream>
#include<cstring>
using namespace std;

typedef unsigned long long ULL;
typedef unsigned int UI;

UI func(int opt, UI X, UI Y, UI Z)
{
	switch (opt)
	{
	case 0: return ((X&Y) | (~X&Z));
	case 1: return ((X&Z) | (~Z&Y));
	case 2: return (X ^ Y ^ Z);
	case 3: return (Y ^ (~Z | X));
	}
}

UI* get(char ch, UI& A, UI& B, UI& C, UI& D)
{
	switch (ch)
	{
	case 'A': return &A;
	case 'B': return &B;
	case 'C': return &C;
	case 'D': return &D;
	}
}

void roundmd5(char* block, UI* T, UI& A, UI& B, UI& C, UI& D, strstream& mem)
{
	unsigned int X[16];
	UI *a, *b, *c, *d, temp, Q;
	int k, i, s;
	char ch;
	for (int j = 0; j < 16; j++)
		X[j] = reinterpret_cast<unsigned int*>(block)[j];

	mem.seekg(0);
	for (int numStage = 0; numStage < 4; numStage++)
	{
		for (int j = 0; j < 16; j++)
		{
			mem >> ch >> ch;
			a = get(ch, A, B, C, D);
			mem >> ch; b = get(ch, A, B, C, D);
			mem >> ch; c = get(ch, A, B, C, D);
			mem >> ch; d = get(ch, A, B, C, D);
			mem >> k >> s >> i >> ch;
			temp = *a + func(numStage, *b, *c, *d) + X[k] + T[i];
			temp = (temp << s) + (temp >> (32 - s)); //цикличееский сдвиг
			*a = *b + temp;
		}
	}
}

string md5(const char* filename)
{
	ifstream file; //инициализация файла
	file.open(filename, ios::binary); //открытие файла
	if (!file) return string("NULL");//string("File is not found or already open!");
	file.seekg(0, ios::end);
	ULL countbyte = file.tellg(); //узнаем длину в байтах
	file.seekg(0);

	unsigned int T[65];
	for (int i = 0; i < 65; i++) {
		T[i] = abs(sin(i)) * 0x100000000;
	}

	//создадим буфер с командами
	const int LENBUFF = 1000;
	char membuff[LENBUFF];
	strstream mem(membuff, LENBUFF);
	mem.unsetf(ios::skipws);
	//Этап1
	mem << "[ABCD  0 7  1][DABC  1 12  2][CDAB  2 17  3][BCDA  3 22  4]";
	mem << "[ABCD  4 7  5][DABC  5 12  6][CDAB  6 17  7][BCDA  7 22  8]";
	mem << "[ABCD  8 7  9][DABC  9 12 10][CDAB 10 17 11][BCDA 11 22 12]";
	mem << "[ABCD 12 7 13][DABC 13 12 14][CDAB 14 17 15][BCDA 15 22 16]";
	//Этап2
	mem << "[ABCD  1 5 17][DABC  6  9 18][CDAB 11 14 19][BCDA  0 20 20]";
	mem << "[ABCD  5 5 21][DABC 10  9 22][CDAB 15 14 23][BCDA  4 20 24]";
	mem << "[ABCD  9 5 25][DABC 14  9 26][CDAB  3 14 27][BCDA  8 20 28]";
	mem << "[ABCD 13 5 29][DABC  2  9 30][CDAB  7 14 31][BCDA 12 20 32]";
	//Этап3
	mem << "[ABCD  5 4 33][DABC  8 11 34][CDAB 11 16 35][BCDA 14 23 36]";
	mem << "[ABCD  1 4 37][DABC  4 11 38][CDAB  7 16 39][BCDA 10 23 40]";
	mem << "[ABCD 13 4 41][DABC  0 11 42][CDAB  3 16 43][BCDA  6 23 44]";
	mem << "[ABCD  9 4 45][DABC 12 11 46][CDAB 15 16 47][BCDA  2 23 48]";
	//Этап4
	mem << "[ABCD  0 6 49][DABC  7 10 50][CDAB 14 15 51][BCDA  5 21 52]";
	mem << "[ABCD 12 6 53][DABC  3 10 54][CDAB 10 15 55][BCDA  1 21 56]";
	mem << "[ABCD  8 6 57][DABC 15 10 58][CDAB  6 15 59][BCDA 13 21 60]";
	mem << "[ABCD  4 6 61][DABC 11 10 62][CDAB  2 15 63][BCDA  9 21 64]";
	mem.setf(ios::skipws);

	unsigned int A, B, C, D;
	unsigned int AA, BB, CC, DD;
	AA = A = 0x67452301;
	BB = B = 0xEFCDAB89;
	CC = C = 0x98BADCFE;
	DD = D = 0x10325476;
	char block[64]; //очередной блок 512 бит

	long long rembyte = countbyte;
	ULL countbit = countbyte * 8;
	UI litLen = countbit; //младшие 4 байта длины файла
	UI bigLen = countbit << 32; //старшие 4 байта длины файла
	bool setf_true_bit = false; //дополнительный единичный бит 

	while (rembyte >= 0)
	{
		if (rembyte >= 64) //если целый блок данных
			file.read(reinterpret_cast<char*>(block), 64); //считать 64 байта в block
		else //неполный блок
		{
			file.read(reinterpret_cast<char*>(block), rembyte); //считать оставшиеся байты
			if (rembyte > 55) { //блок не полный, но места под длину файла и 1бит не хватает
				block[rembyte++] = 0x80; //добавить единичный бит(байт)
				setf_true_bit = true;
				for (int j = rembyte; j < 64; j++) //заполнить остальное нулями
					block[j] = 0;
				rembyte = 64;
			}
			else //неполные блок, но места хватает
			{
				if (!setf_true_bit)
					block[rembyte++] = 0x80;
				for (int j = rembyte; j < 56; j++)
					block[j] = 0;
				*(reinterpret_cast<UI*>(block + 56)) = litLen; //записать в блок 
				*(reinterpret_cast<UI*>(block + 60)) = bigLen; //длину файла
			}
		}
		roundmd5(block, T, A, B, C, D, mem); //проведем раунд
		AA = A = AA + A;
		BB = B = BB + B;
		CC = C = CC + C;
		DD = D = DD + D;
		rembyte -= 64;
	}

	unsigned char hash[16]; //запишем ABCD в массив символов
	*(reinterpret_cast<UI*>(hash)) = A;
	*(reinterpret_cast<UI*>(hash) + 1) = B;
	*(reinterpret_cast<UI*>(hash) + 2) = C;
	*(reinterpret_cast<UI*>(hash) + 3) = D;

	char hashstr[33]; //переведем последоваельность чисел с строку
	for (int j = 0; j < 16; j++) {
		if (hash[j] < 16) {
			hashstr[j * 2] = '0';
			_itoa_s(hash[j], reinterpret_cast<char*>(hashstr + j * 2 + 1), 3, 16);
		}
		else
			_itoa_s(hash[j], reinterpret_cast<char*>(hashstr + j * 2), 3, 16);
	}
	//cout.fill('0'); cout.setf(ios::uppercase);
	//cout << hash1 << endl;
	return string(hashstr);
}