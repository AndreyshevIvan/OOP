#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

static const int ARGUMENTS_COUNT = 5;

using namespace std;

bool IsArgumentsCountValid(int argc);
bool IsInputEmpty(ifstream &inputFile);
bool IsInputOpen(ifstream &inputFile);
bool IsOutputOpen(ofstream &outputFile);
bool IsStringEmpty(string const& searchStr);
void EnterReplacing(ifstream &inputFile, ofstream &outputFile, string const& searchStr, string const& newStr);
string ReplaceStrings(string currentStr, string const& searchStr, string const& subStr);

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

	if (IsInputOpen(inputFile))
	{
		cout << "Failed to open " << argv[1] << "\n";
		return 1;
	}

	if (IsInputEmpty(inputFile))
	{
		cout << "Empty file " << argv[1] << "\n";
		return 1;
	}

	if (IsOutputOpen(outputFile))
	{
		cout << "Failed to open " << argv[2] << "\n";
		return 1;
	}

	const string searchStr = argv[3];
	const string newStr = argv[4];


	if (!IsStringEmpty(searchStr))
	{
		cout << "The search string is empty" "\n";
		return 1;
	}

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

bool IsInputEmpty(ifstream &inputFile)
{
	if (inputFile.peek() == ifstream::traits_type::eof())
		return 1;

	return false;
}

bool IsInputOpen(ifstream &inputFile)
{
	if (!inputFile.is_open())
		return  true;

	return false;
}

bool IsOutputOpen(ofstream &outputFile)
{
	if (!outputFile.is_open())
		return  true;

	return false;
}

bool IsStringEmpty(string const& searchStr)
{
	if (searchStr.size() == 0)
		return false;

	return true;
}

void EnterReplacing(ifstream &inputFile, ofstream &outputFile, string const& searchStr, string const& newStr)
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

string ReplaceStrings(string currentStr, string const& searchStr, string const& newStr)
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