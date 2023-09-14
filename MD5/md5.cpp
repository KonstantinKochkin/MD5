#include<iostream>
#include<string>
#include<fstream>
#include<cstring>

constexpr uint32_t CONST_TABLE[] = {
             0, 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613,
    0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e,
    0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,  0x2441453, 0xd8a1e681,
    0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9,
    0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60,
    0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085,  0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8,
    0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d,
    0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
};

using abcd_selector_type = void (*)(uint32_t*& a, uint32_t*& b, uint32_t*& c, uint32_t*& d,
    uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D);

struct Instruction
{
    constexpr Instruction(abcd_selector_type abcd_selector, uint16_t k, uint16_t s, uint16_t i) noexcept
        : abcd_selector(abcd_selector), k(k), s(s), i(i) {}

    abcd_selector_type abcd_selector;
    uint16_t k, s, i;
};

void ABCD(uint32_t*& a, uint32_t*& b, uint32_t*& c, uint32_t*& d,
          uint32_t& A,  uint32_t& B,  uint32_t& C,  uint32_t& D  )
{
    a = &A;
    b = &B;
    c = &C;
    d = &D;
}

void BCDA(uint32_t*& a, uint32_t*& b, uint32_t*& c, uint32_t*& d,
          uint32_t& A,  uint32_t& B,  uint32_t& C,  uint32_t& D  )
{
    a = &B;
    b = &C;
    c = &D;
    d = &A;
}

void CDAB(uint32_t*& a, uint32_t*& b, uint32_t*& c, uint32_t*& d,
          uint32_t& A,  uint32_t& B,  uint32_t& C,  uint32_t& D  )
{
    a = &C;
    b = &D;
    c = &A;
    d = &B;
}

void DABC(uint32_t*& a, uint32_t*& b, uint32_t*& c, uint32_t*& d,
          uint32_t& A,  uint32_t& B,  uint32_t& C,  uint32_t& D  )
{
    a = &D;
    b = &A;
    c = &B;
    d = &C;
}

constexpr Instruction INSTRUCTIONS[4][16] = {
    //этап 1
    { {&ABCD,  0,  7,  1}, {&DABC,  1, 12,  2}, {&CDAB,  2, 17,  3}, {&BCDA,  3, 22,  4},
      {&ABCD,  4,  7,  5}, {&DABC,  5, 12,  6}, {&CDAB,  6, 17,  7}, {&BCDA,  7, 22,  8},
      {&ABCD,  8,  7,  9}, {&DABC,  9, 12, 10}, {&CDAB, 10, 17, 11}, {&BCDA, 11, 22, 12},
      {&ABCD, 12,  7, 13}, {&DABC, 13, 12, 14}, {&CDAB, 14, 17, 15}, {&BCDA, 15, 22, 16}  },
    //этап 2
    { {&ABCD,  1,  5, 17}, {&DABC,  6,  9, 18}, {&CDAB, 11, 14, 19}, {&BCDA,  0, 20, 20},
      {&ABCD,  5,  5, 21}, {&DABC, 10,  9, 22}, {&CDAB, 15, 14, 23}, {&BCDA,  4, 20, 24},
      {&ABCD,  9,  5, 25}, {&DABC, 14,  9, 26}, {&CDAB,  3, 14, 27}, {&BCDA,  8, 20, 28},
      {&ABCD, 13,  5, 29}, {&DABC,  2,  9, 30}, {&CDAB,  7, 14, 31}, {&BCDA, 12, 20, 32}  },
    //этап 3
    { {&ABCD,  5,  4, 33}, {&DABC,  8, 11, 34}, {&CDAB, 11, 16, 35}, {&BCDA, 14, 23, 36},
      {&ABCD,  1,  4, 37}, {&DABC,  4, 11, 38}, {&CDAB,  7, 16, 39}, {&BCDA, 10, 23, 40},
      {&ABCD, 13,  4, 41}, {&DABC,  0, 11, 42}, {&CDAB,  3, 16, 43}, {&BCDA,  6, 23, 44},
      {&ABCD,  9,  4, 45}, {&DABC, 12, 11, 46}, {&CDAB, 15, 16, 47}, {&BCDA,  2, 23, 48}  },
    //этап 4
    { {&ABCD,  0,  6, 49}, {&DABC,  7, 10, 50}, {&CDAB, 14, 15, 51}, {&BCDA,  5, 21, 52},
      {&ABCD, 12,  6, 53}, {&DABC,  3, 10, 54}, {&CDAB, 10, 15, 55}, {&BCDA,  1, 21, 56},
      {&ABCD,  8,  6, 57}, {&DABC, 15, 10, 58}, {&CDAB,  6, 15, 59}, {&BCDA, 13, 21, 60},
      {&ABCD,  4,  6, 61}, {&DABC, 11, 10, 62}, {&CDAB,  2, 15, 63}, {&BCDA,  9, 21, 64}  }
};

uint32_t func(int stage, uint32_t X, uint32_t Y, uint32_t Z)
{
    switch (stage)
    {
    case 0: return ((X & Y) | (~X & Z));
    case 1: return ((X & Z) | (~Z & Y));
    case 2: return (X ^ Y ^ Z);
    case 3: return (Y ^ (~Z | X));
    }
}

void roundmd5(char* block, uint32_t& A, uint32_t& B, uint32_t& C, uint32_t& D)
{
    uint32_t* X = reinterpret_cast<uint32_t*>(block);
    uint32_t* a, * b, * c, * d;
    uint32_t temp;

    for (int stage = 0; stage < 4; stage++)
    {
        for (int step = 0; step < 16; step++)
        {
            INSTRUCTIONS[stage][step].abcd_selector(a, b, c, d, A, B, C, D);
            const auto& k = INSTRUCTIONS[stage][step].k;
            const auto& s = INSTRUCTIONS[stage][step].s;
            const auto& i = INSTRUCTIONS[stage][step].i;

            temp = *a + func(stage, *b, *c, *d) + X[k] + CONST_TABLE[i];
            temp = (temp << s) + (temp >> (32 - s));
            *a = *b + temp;
        }
    }
}

template<size_t N>
std::string hexPresentaiton(uint8_t(&data)[N])
{
	char hashstr[N * 2 + 1];
	for (int j = 0; j < N; j++)
	{
		if (data[j] < 16)
			hashstr[j * 2] = '0';
		_itoa_s(data[j], hashstr + j * 2 + (data[j] < 16 ? 1 : 0), 3, 16);
	}
	hashstr[N * 2] = 0;
	return hashstr;
};


// Возвращает хеш, параметр - имя файла
std::string md5(const char* filename)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);
    if (!file) 
        return std::string("NULL");  // string("File is not found or already open!");
    file.seekg(0, std::ios::end);
    int64_t file_length { file.tellg() };
    file.seekg(0);

    uint32_t A{ 0x67452301 }, AA{ A },
             B{ 0xEFCDAB89 }, BB{ B },
             C{ 0x98BADCFE }, CC{ C },
             D{ 0x10325476 }, DD{ D };

    char block[64]; // очередной блок 512 бит

    uint64_t&& bit_file_length = file_length * 8;
    uint32_t first_path_len = bit_file_length << 32;        // старшие 4 байта длины файла
    uint32_t second_path_len = bit_file_length;             // младшие 4 байта длины файла
    bool is_bit_added = false;                              // дополнительный единичный бит

    while (file_length >= 0)
    {
        if (file_length >= 64)                              // если целый блок данных
			file.read(block, 64);                           // считать 64 байта в block
        else                                                // неполный блок
        {
            file.read(block, file_length);
            // неполный блок, не вмещающий единичный бит и длину файла
            if (file_length > 55) {
                block[file_length++] = 0x80;                      // добавить единичный бит
                is_bit_added = true;
				memset(block + file_length, 0, 64 - file_length); // заполнить остальное нулями
                file_length = 64;
            }
            else  // неполный блок, вмещающий единичный бит и длину файла
            {
                if (!is_bit_added)
                    block[file_length++] = 0x80;
				memset(block + file_length, 0, 56 - file_length); // заполнить остальное нулями
                *(reinterpret_cast<uint32_t*>(block + 56)) = second_path_len; // записать в блок 
                *(reinterpret_cast<uint32_t*>(block + 60)) = first_path_len;  // длину файла
            }
        }
        roundmd5(block, A, B, C, D);
        AA = A = AA + A;
        BB = B = BB + B;
        CC = C = CC + C;
        DD = D = DD + D;
        file_length -= 64;
    }

    uint8_t hash[16]; //запишем ABCD в единый блок
    *(reinterpret_cast<uint32_t*>(hash)    ) = A;
    *(reinterpret_cast<uint32_t*>(hash) + 1) = B;
    *(reinterpret_cast<uint32_t*>(hash) + 2) = C;
    *(reinterpret_cast<uint32_t*>(hash) + 3) = D;

    return std::move(hexPresentaiton(hash));
}