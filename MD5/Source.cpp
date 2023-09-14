#include <iostream>
#include "hasher.h"

//TODO добавить проверку по размеру файлов

int main(const int argc, const char* argv[])
{
	if (argc == 1) //вывести все хеши из базы
	{
		printAllHash();
		return 0;
	}
	if (argc == 2) //сверить хеш
	{
		checkFile(argv[1]);
		return 0;
	}
	if (argc == 3 && strcmp(argv[2], "/W")==0) //записать новый хеш
	{
		updateHash(argv[1]);
		return 0;
	}
	if (argc == 3 && strcmp(argv[2], "/H") == 0) //только вычислить хеш
	{
		auto&& hash = calculateHash(argv[1]);
		std::cout << hash << std::endl;
		return 0;
	}
	if (argc == 4 && strcmp(argv[2], "/C") == 0) //сравнить два хеша
	{
		auto&& hash1 = calculateHash(argv[1]);
		auto&& hash2 = calculateHash(argv[3]);
		std::cout << "File 1: " << argv[1] << "   Hash: " << hash1 << std::endl;
		std::cout << "File 2: " << argv[3] << "   Hash: " << hash2 << std::endl;
		if (hash1 == hash2) {
			std::cout << "Files are IDENTICAL!\n";
		}
		else {
			std::cout << "files are DIFFERENT!\n";
		}
		return 0;
	}
	std::cerr << "Error, look to help!\n\n";
	std::cout <<
		"The program is designed to check the integrity of files by calculating the MD5 hash.\n\n"
		"MD5 [FILE [/W | /H | /C FILE2]]\n"
		"The calculated hashes are stored in 'Hashfile.txt'. Running without arguments"
		"displays all stored hashes. Running with the argument FILE calculates the hash"
		"and tries to verify it.\n\n"
		"    FILE - file name for hash calculation.\n"
		"    /W - updates or writes new hash to the database.\n"
		"    /H - only calculates hash.\n"
		"    /C FILE2 - compares FILE and FILE2.\n";

	return -1;
}