#include "stdafx.h"
#include "CBody.h"
#include "CController.h"

using namespace std;

int main()
{
	vector<shared_ptr<CBody>> bodies;
	CController controller(bodies, cin, cout);
	controller.Help();
	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		controller.HandleCommand();
	}

	controller.PrintAllBodies(bodies);
	//controller.FindBodyWithMaxMass(bodies);
	//controller.FindBodyWithSmallestWeight(bodies);

	return 0;
}