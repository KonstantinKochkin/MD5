#include<iostream>
#include<string>
#include<fstream>
#include<cstring>
#include "md5.h"

constexpr uint32_t CONST_TABLE[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,  0x2441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085,  0x4881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
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
    //stage 1
    { {&ABCD,  0,  7,  1}, {&DABC,  1, 12,  2}, {&CDAB,  2, 17,  3}, {&BCDA,  3, 22,  4},
      {&ABCD,  4,  7,  5}, {&DABC,  5, 12,  6}, {&CDAB,  6, 17,  7}, {&BCDA,  7, 22,  8},
      {&ABCD,  8,  7,  9}, {&DABC,  9, 12, 10}, {&CDAB, 10, 17, 11}, {&BCDA, 11, 22, 12},
      {&ABCD, 12,  7, 13}, {&DABC, 13, 12, 14}, {&CDAB, 14, 17, 15}, {&BCDA, 15, 22, 16}  },
    //stage 2
    { {&ABCD,  1,  5, 17}, {&DABC,  6,  9, 18}, {&CDAB, 11, 14, 19}, {&BCDA,  0, 20, 20},
      {&ABCD,  5,  5, 21}, {&DABC, 10,  9, 22}, {&CDAB, 15, 14, 23}, {&BCDA,  4, 20, 24},
      {&ABCD,  9,  5, 25}, {&DABC, 14,  9, 26}, {&CDAB,  3, 14, 27}, {&BCDA,  8, 20, 28},
      {&ABCD, 13,  5, 29}, {&DABC,  2,  9, 30}, {&CDAB,  7, 14, 31}, {&BCDA, 12, 20, 32}  },
    //stage 3
    { {&ABCD,  5,  4, 33}, {&DABC,  8, 11, 34}, {&CDAB, 11, 16, 35}, {&BCDA, 14, 23, 36},
      {&ABCD,  1,  4, 37}, {&DABC,  4, 11, 38}, {&CDAB,  7, 16, 39}, {&BCDA, 10, 23, 40},
      {&ABCD, 13,  4, 41}, {&DABC,  0, 11, 42}, {&CDAB,  3, 16, 43}, {&BCDA,  6, 23, 44},
      {&ABCD,  9,  4, 45}, {&DABC, 12, 11, 46}, {&CDAB, 15, 16, 47}, {&BCDA,  2, 23, 48}  },
    //stage 4
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

            temp = *a + func(stage, *b, *c, *d) + X[k] + CONST_TABLE[i-1];
            temp = (temp << s) + (temp >> (32 - s));
            *a = *b + temp;
        }
    }
}

// Return hash string
std::string md5(std::istream& stream, bool ignore_last_byte /*= false*/)
{
    uint32_t A{ 0x67452301 }, AA{ A },
             B{ 0xEFCDAB89 }, BB{ B },
             C{ 0x98BADCFE }, CC{ C },
             D{ 0x10325476 }, DD{ D };

    char block[BLOCK_SIZE];

    bool is_bit_added = false;       // extra unit bit
	bool is_final_run = false;


	uint64_t stream_size = 0;
	while (!stream.eof() || is_final_run)
	{
		stream.read(block, BLOCK_SIZE);
		int16_t rbyte_count = stream.gcount();

		//If the stream is empty, ignore last '\n' byte in block
		if (ignore_last_byte && stream.peek() == -1 && rbyte_count != 0) {
			rbyte_count--;
			ignore_last_byte = false;
		}

		if (rbyte_count == BLOCK_SIZE) {
			stream_size += rbyte_count;
		}
		else {
			// Ignore last '\n' byte in block
			if (ignore_last_byte && rbyte_count != 0) {
				rbyte_count--;
			}
			stream_size += rbyte_count;

			// Block size is not sufficient to store stream length and unit bit
			if (rbyte_count > BLOCK_SIZE - 8 - 1) 
			{
				block[rbyte_count++] = UNIT_BIT;
				is_bit_added = true;
				// Padding a block with zeros
				memset(block + rbyte_count, 0, BLOCK_SIZE - rbyte_count);

				is_final_run = true;
			}
			else {  // The block size is sufficient to store the length of the stream and the unit bit
				if (!is_bit_added) {
					block[rbyte_count++] = UNIT_BIT;
				}
				// Padding a block with zeros
				memset(block + rbyte_count, 0, BLOCK_SIZE - 8 - rbyte_count);

				uint64_t&& bit_stream_size = stream_size * 8;
				uint32_t first_path_size = bit_stream_size << 32;  // high 4 bytes
				uint32_t second_path_size = bit_stream_size;       // low 4 bytes

				// Write the length of the stream into a block
				*(reinterpret_cast<uint32_t*>(block + BLOCK_SIZE - 8)) = second_path_size;
				*(reinterpret_cast<uint32_t*>(block + BLOCK_SIZE - 4)) = first_path_size;

				is_final_run = false;
			}
		}

        roundmd5(block, A, B, C, D);
        AA = A = AA + A;
        BB = B = BB + B;
        CC = C = CC + C;
        DD = D = DD + D;
    }

    uint8_t hash[16];
    *(reinterpret_cast<uint32_t*>(hash)    ) = A;
    *(reinterpret_cast<uint32_t*>(hash) + 1) = B;
    *(reinterpret_cast<uint32_t*>(hash) + 2) = C;
    *(reinterpret_cast<uint32_t*>(hash) + 3) = D;

    return std::move(hexPresentaiton(hash));
}