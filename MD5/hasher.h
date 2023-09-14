#pragma once

#include<iostream>
#include<string>

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

constexpr size_t FILENAME_SIZE = 120;
constexpr size_t HASH_SIZE = 32;
constexpr char HASHFILE_NAME[] = "Hashfile.txt";

void checkFile(const std::istream& inp, const char* filename);

void checkHash(const std::string& hash);

void checkData(const std::string& filename, const std::string& hash);

bool findInHashfile(std::istream& hashfile, const std::string& filename, std::string& hash);

std::string calculateHash(const char* filename);

void printAllHash();

void checkFile(const char* filename);

void updateHash(const char* filename);
