#include "stdafx.h"
#include "..\CCar\CCar.h"
#include "..\CCar\CCarController.h"

using namespace std;

struct CarControlDependencies
{
	CCar car;
	stringstream input;
	stringstream output;
};

struct CarControlFixture : CarControlDependencies
{
	CCarController controller;

	CarControlFixture()
		: controller(input, output, car)
	{
	}

	void VerifyCommands(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		controller.HandleCommand();
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};


BOOST_FIXTURE_TEST_SUITE(CController_test, CarControlFixture)

BOOST_AUTO_TEST_CASE(check_uncnown_commands)
{
	VerifyCommands("", "");
	VerifyCommands("Info", "Engine is turned off\n");
}

BOOST_AUTO_TEST_SUITE_END()
