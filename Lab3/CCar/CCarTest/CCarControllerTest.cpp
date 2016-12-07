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

BOOST_AUTO_TEST_CASE(try_to_get_error_output)
{
	VerifyCommands("EngineOn", "");
	car.TurnOnEngine();
	VerifyCommands("SetSpeed 100", "The vehicle gear is not suitable for this speed\n");

	car.TurnOffEngine();
	VerifyCommands("SetSpeed 100", "The engine is not turned on\n");

	VerifyCommands("SetGear 4", "The engine is not turned on\n");

	car.TurnOnEngine();
	car.SetGear(1);
	VerifyCommands("SetGear 4", "The vehicle speed is not suitable\n");
}

BOOST_AUTO_TEST_CASE(get_normal_info)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(57);
	VerifyCommands("Info", "Engine is turned on \nDirection is: forward\nSpeed is: 57\nGear is: third\n");
}


BOOST_AUTO_TEST_SUITE_END()
