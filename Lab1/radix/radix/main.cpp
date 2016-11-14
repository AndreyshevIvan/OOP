#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>

const int ARGUMENTS_COUNT = 4;
const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

using namespace std;

bool CheckArgumentsCount(int& argc);
bool CheckRadix(int& radix);
int StringToInt(const string& str, int radix, bool& wasError);
int CharToDigit(const char& ch);

int main(int argc, char * argv[])
{
	bool wasError = false;

	if (!CheckArgumentsCount(argc))
		return EXIT_FAILURE;

	int sourceRadix = stoi(argv[1]);
	int destenationRadix = stoi(argv[2]);

	if (!CheckRadix(sourceRadix) || !CheckRadix(destenationRadix))
		return EXIT_FAILURE;

	const string value = argv[3];

	if (sourceRadix == destenationRadix)
	{
		cout << value << "\n";
		return 1;
	}

	int valueInDec = StringToInt(value, sourceRadix, wasError);
	cout << valueInDec << "\n";


    return 0;
}

bool CheckArgumentsCount(int& argc)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" "\n"; 
		cout << "Usage: replace.exe <source notation> <destenation notation> <value>" "\n";
		return false;
	}

	return true;
}

bool CheckRadix(int& radix)
{
	if (radix < MIN_RADIX || radix > MAX_RADIX)
	{
		cout << "Invalid notation value" "\n";
		cout << "Radix should be in the range [2; 36]" "\n";
		return false;
	}
	
	return true;
}

int StringToInt(const string& str, int radix, bool& wasError)
{
	int result = 0;
	int digit = 0;

	cout << str << "\n";

	if (str[0] == '-')
	{
		for (size_t i = 1; i < str.length(); i++)
		{
			digit = CharToDigit(str[i]);
			cout << i << " : " << digit << "\n";
			result += digit * (int)pow(radix, str.length() - i - 1);
		}
		result = -result;
	}
	else
	{
		for (size_t i = 0; i < str.length(); i++)
		{
			digit = CharToDigit(str[i]);
			result += digit * (int)pow(radix, str.length() - i - 1);
		}
	}

	return result;
}

int CharToDigit(const char& ch)
{
	int result;

	if (ch >= '0' && ch <= '9')
	{
		result = (int)ch - '0';
		cout << ch << " - " << result << "\n";
	}
	else if (ch > '9' && ch <= 'Z')
	{
		result = (int)ch - 'A' + 10;
		cout << (int)ch << "\n";
		cout << (int)'A' << "\n";
		cout << ch << " - " << result << "\n";
	}

	return result;
}