#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

static const int ARGUMENTS_COUNT = 5;

using namespace std;

bool ReplaceStringsInFile(ifstream& inputFile, ofstream& outputFile, string const& searchStr, string const& replaceStr);
void ReplaceStrings(string& currentStr, string const& searchStr, string const& replaceStr);

int main(int argc, char* argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"
			"Usage: replace.exe <input file> <output file> <search string> <replace string>" "\n";
		return 1;
	}

	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);

	if (!inputFile.is_open())
	{
		cout << "Failed to open " << argv[1] << "\n";
		return 1;
	}

	if (inputFile.peek() == ifstream::traits_type::eof())
	{
		cout << "Empty file " << argv[1] << "\n";
		return 1;
	}

	if (!outputFile.is_open())
	{
		cout << "Failed to open " << argv[2] << "\n";
		return 1;
	}

	const string searchStr = argv[3];
	const string newStr = argv[4];

	if (searchStr.size() == 0)
	{
		cout << "The search string is empty" "\n";
		return 1;
	}

    if (!ReplaceStringsInFile(inputFile, outputFile, searchStr, newStr))
    {
        cout << "The search string is empty" "\n";
        return 1;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}

bool ReplaceStringsInFile(ifstream& inputFile, ofstream& outputFile, string const& searchStr, string const& replaceStr)
{
    if (searchStr.empty())
    {
        return false;
    }

	string currentStr;

	while (getline(inputFile, currentStr))
	{
        ReplaceStrings(currentStr, searchStr, replaceStr);
		outputFile << currentStr << "\n";
	}

    return true;
}

void ReplaceStrings(string& currentStr, string const& searchStr, string const& replaceStr)
{
	if (searchStr != "")
	{
		size_t copiedPos = 0;
		size_t searchStrPos = currentStr.find(searchStr, 0);

		string newStr;

		while (copiedPos != currentStr.length() || searchStrPos != string::npos)
		{
			if (copiedPos != searchStrPos)
			{
				newStr += currentStr[copiedPos];
				++copiedPos;
			}
			else
			{
				newStr += replaceStr;
				copiedPos += searchStr.length();
				searchStrPos = currentStr.find(searchStr, copiedPos);
			}
		}
		currentStr.swap(newStr);
	}
}