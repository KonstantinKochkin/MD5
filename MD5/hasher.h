#pragma once
#include<iostream>
#include<string>

constexpr size_t FILENAME_SIZE = 120;
constexpr size_t HASH_SIZE = 32;
constexpr char HASHFILE_NAME[] = "Hashfile.txt";

struct comparison_info
{
	std::string fullpath;
	std::string storedhash;
	std::string newhash;

	friend std::ostream& operator<<(std::ostream& os, comparison_info& comp_info);
};


template<typename T, class = std::enable_if_t<std::is_same<std::decay_t<T>, std::string>::value>>
auto replaceSpaces(T&& str)
{
	if (str.find(' ') == std::string::npos) {
		return std::forward<T>(str);
	}

	auto newstr(str);
	for (auto& ch : newstr) {
		if (ch == ' ')
			ch = '_';
	}
	return std::move(newstr);
}


void checkFile(const std::istream& inp, const char* filename);

void checkData(const std::string& filename, const std::string& hash);

bool findInHashfile(std::istream& hashfile, const std::string& filename, std::string& hash);

std::string hashForFile(const char* filename);

std::string hashForString(const char* str);

std::string hashForStream(std::istream& stream);

void printAllHash();

bool compareHash(const char* filename);
bool compareHash(const char* filename, comparison_info& comp_info);

void updateHash(const char* filename);
void updateHash(const char* filename, comparison_info& comp_info);
