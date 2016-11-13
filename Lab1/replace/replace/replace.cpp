#include "stdafx.h"
#include <iostream>
#include <fstream>

const int ARGUMENTS_COUNT = 5;

using namespace std;

bool checkArgumentsCount(int &argc);
bool checkInputFile(char* argv[], ifstream &inputFile);
bool checkOutputFile(char* argv[], ifstream &outputFile);
bool checkSearchStr(string &searchStr);

int main(int argc, char* argv[])
{
	if (!checkArgumentsCount(argc))
	{
		cout << "Invalid arguments count" "\n";
		cout << "Usage: replace.exe <input file> <output file> <search string> <replace string>" "\n";
		return EXIT_FAILURE;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (!checkInputFile(argv, inputFile))
		return EXIT_FAILURE;

	if (!checkOutputFile(argv, inputFile))
		return EXIT_FAILURE;

	string searchStr = argv[3];
	string newStr = argv[4];

	if (!checkSearchStr(searchStr))
		return EXIT_FAILURE;

	inputFile.close();
	outputFile.close();
    return 0;
}

bool checkArgumentsCount(int &argc)
{
	if (argc != ARGUMENTS_COUNT)
		return false;

	return true;
}

bool checkInputFile(char* argv[], ifstream &inputFile)
{
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << "\n";
		return  false;
	}
	if (inputFile.peek() == ifstream::traits_type::eof())
	{
		cout << "Empty file " << argv[1] << "\n";
		return false;
	}

	return true;
}

bool checkOutputFile(char* argv[], ifstream &outputFile)
{
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << "\n";
		return  false;
	}

	return true;
}

bool checkSearchStr(string &searchStr)
{
	if (searchStr.size() == 0)
	{
		cout << "The search string is empty" "\n";
		return false;
	}

	return true;
}