#include "hasher.h"
#include <fstream>
#include <iomanip>
#include <filesystem>
#include "md5.h"

namespace fs = std::filesystem;

void checkFile(const std::istream& inp, const char* filename) {
	if (!inp) {
		std::cerr << filename << " is not found!\n";
		exit(-1);
	}
}

void checkHash(const std::string& hash) {
	if (hash == "NULL") {
		std::cerr << "Target file is not found or already open!\n";
		exit(-1);
	}
}

void checkData(const std::string& filename, const std::string& hash) {
	if (filename.length() > FILENAME_SIZE || hash.length() != HASH_SIZE) {
		std::cerr << "HashFile contains incorrect data!\n";
		exit(-1);
	}
}

bool findInHashfile(std::istream& hashfile, const std::string& filename, std::string& hash)
{
	std::string name;
	while (hashfile)
	{
		hashfile >> name >> hash;
		hashfile.ignore(1000, '\n');
		if (hashfile)
		{
			checkData(name, hash);

			if (name == filename) {
				return true;
			};
		}
	}
	return false;
}

std::string calculateHash(const char* filename) 
{
	auto&& hash = md5(filename);
	checkHash(hash);
	return std::forward<std::string>(hash);
}

void printAllHash()
{
	std::ifstream hashfile(HASHFILE_NAME);
	checkFile(hashfile, "Hashfile");

	hashfile.seekg(0, std::ios::end);
	if (hashfile.tellg() == 0) {
		std::cout << "HashFile is empty!\n";
		return;
	}
	hashfile.seekg(0);


	std::cout << std::setw(20) << std::left << "Filename " << "   Hash md5" << std::endl;

	std::string filename, hash;
	while (hashfile)
	{
		hashfile >> filename >> hash;
		hashfile.ignore(1000, '\n');
		if (hashfile)
		{
			checkData(filename, hash);
			std::cout << std::setw(20) << std::left << filename << "   " << hash << std::endl;
		}
	}
}

void checkFile(const char* filename)
{
	auto&& newhash = calculateHash(filename);

	fs::path target_path {filename};
	auto&& normal_path = replaceSpaces(fs::absolute(target_path).string());

	std::cout << "File name:        " << normal_path << "   Hash: " << newhash << std::endl;

	std::ifstream hashfile(HASHFILE_NAME);
	checkFile(hashfile, "Hashfile");

	std::string hash;
	if (!findInHashfile(hashfile, normal_path, hash)) {
		std::cout << "There are no such file in the database!\n";
	}
	else
	{
		std::cout << "File in database: " << normal_path << "   Hash: " << hash << std::endl;
		if (newhash == hash) {
			std::cout << "Result - TRUE. File has NOT been modified!\n";
		}
		else {
			std::cout << "Result - FALSE. File has been modified!\n";
		}
	}
}

void updateHash(const char* filename)
{
	std::fstream hashfile(HASHFILE_NAME, std::ios::in | std::ios::out | std::ios::_Nocreate);
	checkFile(hashfile, "Hashfile");

	fs::path target_path {filename};
	auto&& normal_path = replaceSpaces(fs::absolute(target_path).string());
	std::cout << "File : " << normal_path << std::endl;

	std::string hash;
	if (!findInHashfile(hashfile, normal_path, hash))
	{
		hashfile.clear();
		hashfile.seekp(0, std::ios::end);
		hashfile.put('\n');
		hashfile.write(normal_path.c_str(), normal_path.length());
		hashfile.put(' ');
	}
	else {
		hashfile.seekg(-2 - HASH_SIZE, std::ios::cur);
		std::cout << "The old hash        : " << hash << std::endl;
	}
	
	auto&& newhash = calculateHash(filename);

	std::cout << "The new hash was got: " << newhash << std::endl;
	hashfile.seekp(hashfile.tellg());
	hashfile.write(newhash.c_str(), HASH_SIZE);
}