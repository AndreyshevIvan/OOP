#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

static const int ARGUMENTS_COUNT = 5;

using namespace std;

bool IsArgumentsCountValid(int argc);
bool IsInputNotEmpty(char* argv[], ifstream &inputFile);
bool IsOutputNotEmpty(char* argv[], ofstream &outputFile);
bool IsSearchStrEmpty(string searchStr);
void EnterReplacing(ifstream &inputFile, ofstream &outputFile, string searchStr, string newStr);
string ReplaceStrings(string &currentStr, string searchStr, string subStr);

int main(int argc, char* argv[])
{
	if (!IsArgumentsCountValid(argc))
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <input file> <output file> <search string> <replace string>" "\n";
		return 1;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (!IsInputNotEmpty(argv, inputFile))
		return 1;

	if (!IsOutputNotEmpty(argv, outputFile))
		return 1;

	string searchStr = argv[3];
	string newStr = argv[4];


	if (!IsSearchStrEmpty(searchStr))
		return 1;

	EnterReplacing(inputFile, outputFile, searchStr, newStr);

	inputFile.close();
	outputFile.close();
    return 0;
}

bool IsArgumentsCountValid(int argc)
{
	if (argc != ARGUMENTS_COUNT)
		return false;

	return true;
}

bool IsInputNotEmpty(char* argv[], ifstream &inputFile)
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

bool IsOutputNotEmpty(char* argv[], ofstream &outputFile)
{
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << "\n";
		return  false;
	}

	return true;
}

bool IsSearchStrEmpty(string searchStr)
{
	if (searchStr.size() == 0)
	{
		cout << "The search string is empty" "\n";
		return false;
	}

	return true;
}

void EnterReplacing(ifstream &inputFile, ofstream &outputFile, string searchStr, string newStr)
{
	string currentStr;

	while (getline(inputFile, currentStr))
	{
		if (!currentStr.empty())
		{
			currentStr = ReplaceStrings(currentStr, searchStr, newStr);
			outputFile << currentStr;
		}
		outputFile << "\n";
	}
}

string ReplaceStrings(string &currentStr, string searchStr, string newStr)
{
	const size_t searchStrLen = searchStr.length();

	string resultStr = "";
	size_t startSearchPos = 0;
	size_t searchStrPos = currentStr.find(searchStr, startSearchPos);

	while (searchStrPos != string::npos)
	{
		currentStr.replace(searchStrPos, searchStr.length(), newStr);
		startSearchPos = searchStrPos + newStr.length();
		searchStrPos = currentStr.find(searchStr, startSearchPos);
	}

	return currentStr;
}