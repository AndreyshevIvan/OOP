#include "stdafx.h"
#include "primeNumbers.h"

const int ARGUMENTS_COUNT = 2;

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Invalid arguments count" << "\n"
			<< "Usage: primeNumbers.exe <upperBound>" "\n";
		return 1;
	}

	bool wasError = false;
	int upperBound = StrToInt(argv[1], wasError);

	if (wasError)
	{
		return 1;
	}
	if (upperBound > MAX_UPPER_BOUND)
	{
		cout << "Invalid upperBound. UpperBound can be in range [0, 1000000000]" << "\n";
		return 1;
	}
	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);

	cout << primeNumbers.size() << "\n";

	return 0;
}