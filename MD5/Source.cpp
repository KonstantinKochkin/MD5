#include<iostream>
#include<fstream>
#include<iomanip>
#include"md5.h";
using namespace std;

const char HASHFILE_NAME[] = "Hashfile.txt";
const int LNAME = 30;
const int LHASH = 32;

int main(int argc, char* argv[])
{
	if (argc < 1 || argc>3)
	{
		cerr << "Eror, look to help!\n";
		exit(-1);
	}
	if (argc == 1) //вывести все хеши из базы
	{
		ifstream hashfile(HASHFILE_NAME);
		if (!hashfile) {
			cerr << "HashFile is not found!\n";
			exit(-1);
		}
		char name[LNAME];
		char hash[LHASH + 1];
		cout << setw(20) << left << "Name " << "   Hash md5" << endl;
		hashfile.peek(); 
		if (!hashfile) 
			cout << "HashFile is empty!\n";
		while (hashfile)
		{
			hashfile.getline(name, LNAME, ' ');
			hashfile.getline(hash, LHASH + 1, '\n');
			if (hashfile)
			cout << setw(20) << left << name << "   " << hash << endl;
		}
		return 0;
	}
	if (argc == 2) //сверить хеш
	{
		//посчитаем хеш
		string hashnow = md5(argv[1]);
		if (hashnow == "NULL") {
			cerr << "File is not found or already open!\n";
			exit(-1);
		}
		//отбрасывания пути к файлу
		char filename[LNAME];
		char temp[LNAME];
		strcpy_s(temp, argv[1]);
		_strrev(temp);
		int len = strcspn(temp, "/\\");
		strncpy_s(filename, temp, len);
		_strrev(filename);

		cout << "File name       : " << filename << "   Hash: " << hashnow << endl;

		//просмотреть базу с хешами
		ifstream hashfile(HASHFILE_NAME);
		if (!hashfile) {
			cerr << "HashFile is not found!\n";
			exit(-1);
		}
		char name[LNAME];
		char hash[LHASH+1];
		bool checked_file_is_found=false;
		while (hashfile)
		{
			hashfile.getline(name, LNAME, ' ');
			hashfile.getline(hash, LHASH+1, '\n');
			if (strcmp(name,filename)==0) {
				checked_file_is_found = true;
				break;
			}
		}
		//вывести результат
		if (!checked_file_is_found)
			cout << "There are no such file in the database!\n";
		else
		{
			cout << "File in database: " << filename << "   Hash: " << hash << endl;
			if (strcmp(hash, hashnow.c_str()) == 0)
				cout << "Result - TRUE. File has NOT been modified!\n";
			else cout << "Result - FALSE. File has been modified!\n";
		}
		return 0;
	}
	if (argc == 3 && strcmp(argv[2],"/w")==0) //записать новый хеш
	{
		fstream hashfile(HASHFILE_NAME,ios::in|ios::out|ios::_Nocreate);
		if (!hashfile) {
			cerr << "HashFile is not found!\n";
			exit(-1);
		}
		//отбрасывания пути к файлу
		char filename[LNAME];
		char temp[LNAME];
		strcpy_s(temp, argv[1]);
		_strrev(temp);
		int len = strcspn(temp, "/\\");
		strncpy_s(filename, temp, len);
		_strrev(filename);

		//поиск файла в базе
		char name[LNAME];
		char hash[LHASH+1];
		bool checked_file_is_found = false;
		while (hashfile)
		{
			hashfile.getline(name, LNAME, ' ');
			hashfile.getline(hash, LHASH+1, '\n');
			if (strcmp(name, filename) == 0) {
				checked_file_is_found = true;
				break;
			}
		}

		cout << "File : " << filename << endl;
		if (!checked_file_is_found)
		{
			hashfile.clear();
			hashfile.seekp(0, ios::end);
			hashfile.write(filename, strlen(filename));
			hashfile.put(' ');
		}
		else {
			hashfile.seekg(-LHASH - 2, ios::cur);
			cout << "The old hash        : " << hash << endl;
		}
		//считаем хеш
		string hashnow = md5(argv[1]);
		if (hashnow == "NULL") {
			cerr << "File is not found or already open!\n";
			exit(-1);
		}

		cout << "The new hash was got: " << hashnow << endl;
		hashfile.seekp(hashfile.tellg());
		hashfile.write(hashnow.c_str(), LHASH);
		hashfile.put('\n');
		return 0;
	}
	if (argc == 3 && strcmp(argv[2], "/h") == 0) //только вычислить хеш
	{
		string hashnow = md5(argv[1]);
		if (hashnow == "NULL") {
			cerr << "File is not found or already open!\n";
			exit(-1);
		}
		cout << hashnow << endl;
		return 0;
	}
	cerr << "Eror, look to help!\n";
	return 0;
}

/*int main()
{
	char argv1[] = "MD5";
	char argv2[] = "..\\MD5\\test4.txt";
	char argv3[] = "";
	char* argv[] = { argv1, argv2, argv3 };
	main1(2, argv);
	return 0;
}*/