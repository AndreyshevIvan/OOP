#include "stdafx.h"
#include "CCar.h"
#include "CCarController.h"

using namespace std;

int main()
{
	CCar car;
	CCarController controller(cin, cout, car);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!controller.HandleCommand())
		{
			cout << "Uncnown command!" "\n";
		}
	}

	return 0;
}