#include <iostream>
#include <iomanip>
#include "hasher.h"


constexpr char HELP[] =
"The program is designed to check the integrity of files by calculating the MD5 hash.\n\n\
MD5 [/H | /S STRING | /F FILE [/B] | /T | /W FILE | /C FILE1 FILE2 | /V FILE HASH]\n\
The calculated hashes are stored in 'Hashfile.txt'. Running without arguments \
displays all stored hashes.\n\n\
    /H - get help.\n\
    /S - calculate hash of string.\n\
    /F - calculate file hash and tries to verify it (/B - only calculate hash).\n\
    /T - turns on text input mode (calculate the hash of the text. Signal to end input: ^Z).\n\
    /W - updates or writes new hash to the database.\n\
    /C - compares file hashes.\n\
    /V - verify a file by hash.\n";


int main(const int argc, const char* argv[])
{
	try {
		// print hash file
		if (argc == 1)
		{
			printAllHash();
		}
		// get help
		else if (argc == 2 && strcmp(argv[1], "/H") == 0)
		{
			std::cout << HELP;
		}
		// calculate hash of text
		else if (argc == 2 && strcmp(argv[1], "/T") == 0)
		{
			std::cout << hashForStream(std::cin);
		}
		// calculate hash of string
		else if (argc == 3 && strcmp(argv[1], "/S") == 0)
		{
			auto&& hash = hashForString(argv[2]);
			std::cout << hash;
		}
		// calculate file hash and tries to verify it
		else if (argc == 3 && strcmp(argv[1], "/F") == 0)
		{
			comparison_info comp_info;
			if (compareHash(argv[2], comp_info)) {
				std::cout << "Result - TRUE. File has NOT been modified!\n";
			}
			else if (comp_info.storedhash.empty())
			{
				std::cout << "There are no such file in the database!\n";
			}
			else {
				std::cout << "Result - FALSE. File has been modified!\n";
			}
			std::cout << "File name:        " << argv[2] << '\n' << comp_info;
		}
		// updates or writes new hash to the database
		else if (argc == 3 && strcmp(argv[1], "/W") == 0)
		{
			comparison_info comp_info;
			updateHash(argv[2], comp_info);

			std::cout << "File name:        " << argv[2] << '\n' << comp_info;
		}
		// only calculate file hash
		else if (argc == 4 && strcmp(argv[1], "/F") == 0 && strcmp(argv[3], "/B") == 0)
		{
			auto&& hash = hashForFile(argv[2]);
			std::cout << hash << std::endl;
		}
		// compares file hashes
		else if (argc == 4 && strcmp(argv[1], "/C") == 0)
		{
			auto&& hash1 = hashForFile(argv[2]);
			auto&& hash2 = hashForFile(argv[3]);
			std::cout << "File 1: " << std::left << std::setw(30) << argv[2] 
				      << "   Hash: " << hash1 << '\n'
			          << "File 2: " << std::left << std::setw(30) << argv[3]
				      << "   Hash: " << hash2 << '\n';
			if (hash1 == hash2) {
				std::cout << "Files are IDENTICAL!\n";
			}
			else {
				std::cout << "Files are DIFFERENT!\n";
			}
		}
		// verify a file by hash
		else if (argc == 4 && strcmp(argv[1], "/V") == 0)
		{
			auto&& hash1 = hashForFile(argv[2]);
			const auto& hash2 = argv[3];
			std::cout << "Calculated hash:   " << hash1 << '\n'
			          << "Verification hash: " << hash2 << '\n';
			if (hash1 == hash2) {
				std::cout << "Verification was SUCCESSFUL!\n";
			}
			else {
				std::cout << "Verification FAILED!\n";
			}
		}
		else {
			std::cout << "Invalid argument list.\n\n" << HELP;
		}
	}
	catch (std::runtime_error err) {
		std::cerr << err.what();
		return -1;
	}
	catch (std::logic_error err) {
		std::cerr << err.what();
		return -1;
	}

	return 0;
}