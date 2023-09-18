#include "hasher.h"
#include <fstream>
#include <iomanip>
#include <filesystem>
#include "md5.h"
#include <sstream>

namespace fs = std::filesystem;

std::ostream& operator<<(std::ostream& os, comparison_info& comp_info)
{
	os << "Full path:        " << comp_info.fullpath
	   << "\nNew hash:         " << comp_info.newhash << std::endl;
	if (!comp_info.storedhash.empty()) {
		std::cout << "Hash in hashfile: " << comp_info.storedhash << std::endl;
	}
	return os;
}


void checkFile(const std::istream& inp, const char* filename) 
{
	if (!inp.good()) {
		throw std::runtime_error('\"' + std::string(filename)
			                     + "\" file does not exist or busy with another process!\n");
	}
}

void checkData(const std::string& filename, const std::string& hash) 
{
	if (filename.length() > FILENAME_SIZE || hash.length() != HASH_SIZE) {
		throw std::length_error("Hashfile contains incorrect data!\n");
	}
}

bool findInHashfile(std::istream& hashfile, const std::string& filename, std::string& storedhash)
{
	std::string name, hash;

	while (hashfile)
	{
		hashfile >> name >> hash;
		if (hashfile)
		{
			checkData(name, hash);

			if (name == filename) {
				storedhash = hash;
				return true;
			};
		}
	}
	return false;
}


std::string hashForFile(const char* filename) 
{
	std::ifstream file(filename, std::ios::binary);
	checkFile(file, filename);

	return std::move(md5(file));
}

std::string hashForString(const char* str)
{
	std::istringstream stream(str);
	return std::move(md5(stream));
}

std::string hashForStream(std::istream& stream)
{
	return std::move(md5(stream, true));
}

void printAllHash()
{
	std::ifstream hashfile(HASHFILE_NAME);
	checkFile(hashfile, HASHFILE_NAME);

	if (hashfile.peek() == -1) {
		std::cout << "HashFile is empty!\n";
		return;
	}

	std::cout << std::setw(55) << std::left << "Filename " << "md5 hash" << std::endl;

	std::string filename, hash;
	while (hashfile)
	{
		hashfile >> filename >> hash;
		if (hashfile)
		{
			checkData(filename, hash);
			std::cout << std::setw(20) << std::left << filename << "   " << hash << std::endl;
		}
	}
}

bool compareHash(const char* filename)
{
	comparison_info comp_info;
	return compareHash(filename, comp_info);
}

bool compareHash(const char* filename, comparison_info& comp_info)
{
	comp_info.newhash = hashForFile(filename);

	fs::path target_path {filename};
	comp_info.fullpath = replaceSpaces(fs::absolute(target_path).string());

	std::ifstream hashfile(HASHFILE_NAME);
	checkFile(hashfile, HASHFILE_NAME);

	return (findInHashfile(hashfile, comp_info.fullpath, comp_info.storedhash)
		    && comp_info.newhash == comp_info.storedhash                      );
}

void updateHash(const char* filename)
{
	comparison_info comp_info;
	return updateHash(filename, comp_info);
}

void updateHash(const char* filename, comparison_info& comp_info)
{
	std::fstream hashfile(HASHFILE_NAME, std::ios::in | std::ios::out | std::ios::_Nocreate);
	checkFile(hashfile, HASHFILE_NAME);

	fs::path target_path {filename};

	auto& fullpath = comp_info.fullpath;
	fullpath = replaceSpaces(fs::absolute(target_path).string());

	comp_info.newhash = hashForFile(filename);

	if (!findInHashfile(hashfile, fullpath, comp_info.storedhash))
	{
		hashfile.clear();
		hashfile.seekp(0, std::ios::end);

		if (hashfile.tellp() != 0) {
			hashfile.put('\n');
		}
		hashfile.write(fullpath.c_str(), fullpath.length());
		hashfile.put(' ');
	}
	else {
		hashfile.seekg(0-HASH_SIZE, std::ios::cur);
	}

	hashfile.seekp(hashfile.tellg());
	hashfile.write(comp_info.newhash.c_str(), HASH_SIZE);
}