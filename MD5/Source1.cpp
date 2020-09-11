/*ULL nblock = (countbyte) / 64; // число полных блоков по 512 бит
for (ULL i = 0; i < nblock; i++)
{
	file.read(reinterpret_cast<char*>(block), 64);
	roundmd5(block, T, A, B, C, D, mem); //проведем раунд
	AA = A = AA + A;
	BB = B = BB + B;
	CC = C = CC + C;
	DD = D = DD + D;
}
//обработка хвоста
ULL remainder = (countbyte) % 64;
file.read(reinterpret_cast<char*>(block), remainder);
block[remainder++] = 0x80;
if (remainder > 56)
{
	for (int j = remainder; j < 64; j++)
		block[j] = 0;
	roundmd5(block, T, A, B, C, D, mem);
	AA = A = AA + A;
	BB = B = BB + B;
	CC = C = CC + C;
	DD = D = DD + D;
	remainder = 0;
}
for (int j = remainder; j < 56; j++)
	block[j] = 0;
countbyte *= 8;
UI litLen = countbyte;
UI bigLen = countbyte << 32;
*(reinterpret_cast<UI*>(block + 56)) = litLen;
*(reinterpret_cast<UI*>(block + 60)) = bigLen;
roundmd5(block, T, A, B, C, D, mem);

A = AA + A;
B = BB + B;
C = CC + C;
D = DD + D;*/



/*char num[3];
for (int j = 0; j < 16; j++)
{
	_itoa_s(hash[j], num, 16);
	if (hash[j] < 16) {
		num[2] = '\x0';
		num[1] = num[0];
		num[0] = '0';
	}
	hashstr.append(num);
}*/

//убрать слеши
/*char filename[LNAME];
if (strchr(argv[1], '/'))
{
	char temp[LNAME];
	strcpy_s(temp, argv[1]);
	_strrev(temp);
	int len = strcspn(temp, "/");
	strncpy_s(filename, temp, len);
	_strrev(filename);
}
else
	strcpy_s(filename, argv[1]);*/