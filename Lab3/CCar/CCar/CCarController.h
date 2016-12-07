#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "CCar.h"
#include <sstream>

class CCarController
{
public:
	CCarController(std::istream& input, std::ostream& output, CCar& car);

	bool HandleCommand();

	std::string GetDirection();
	std::string GetGear();
private:
	bool Info(std::istream& arguments);
	bool EngineOn(std::istream& arguments);
	bool EngineOff(std::istream& arguments);
	bool SetGear(std::istream& arguments);
	bool SetSpeed(std::istream& arguments);

	typedef std::map<std::string, std::function<bool(std::istream& arguments)>> ActionsMap;

	std::istream& m_input;
	std::ostream& m_output;
	std::string m_commandLine;
	const ActionsMap m_actions;
	CCar& m_car;
};