#include "stdafx.h"
#include "CCar.h"
#include "CCarController.h"

using namespace std;
using namespace std::placeholders;

CCarController::CCarController(istream& input, ostream& output, CCar& car)
	:m_input(input)
	,m_output(output)
	,m_car(car)
	,m_actions({
		{"Info", bind(&CCarController::Info, this, _1)},
		{"EngineOn", bind(&CCarController::EngineOn, this, _1)},
		{"EngineOff", bind(&CCarController::EngineOff, this, _1)},
		{"SetGear", bind(&CCarController::SetGear, this, _1)},
		{"SetSpeed", bind(&CCarController::SetSpeed, this, _1)}
		})
{
}

bool CCarController::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream stream(commandLine);

	string action;
	stream >> action;

	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		return it->second(stream);
	}
	return false;
}

bool CCarController::Info(std::istream& arguments)
{
	string info;

	if (m_car.IsEngineTurnOn())
	{
		info += "Engine is turned on \nDirection is: " + GetDirection() + "\nSpeed is: " + to_string(m_car.GetSpeed()) + "\nGear is: " + GetGear() + "\n";
	}
	else
	{
		info += "Engine is turned off" "\n";
	}

	m_output << info;

	return true;
}

string CCarController::GetDirection()
{
	switch (m_car.GetDirection())
	{
	case Direction::BACKWARD:
		return "backward";
	case Direction::STAY:
		return "stay";
	case Direction::FORWARD:
		return "forward";
	default:
		return "";
		break;
	}
}

string CCarController::GetGear()
{
	switch (m_car.GetGear())
	{
	case Gear::REAR:
		return "rear";
	case Gear::NEUTRAL:
		return "neutral";
	case Gear::FIRST:
		return "first";
	case Gear::SECOND:
		return "second";
	case Gear::THIRD:
		return "third";
	case Gear::FOURTH:
		return "fourth";
	case Gear::FIFTH:
		return "fifth";
	default:
		return "";
		break;
	}
}

bool CCarController::EngineOn(std::istream& arguments)
{
	m_car.TurnOnEngine();
	return true;
}

bool CCarController::EngineOff(std::istream& arguments)
{
	if (!m_car.TurnOffEngine())
	{
		m_output << "The engine is not turned on" "\n";
	}

	return true;
}

bool CCarController::SetGear(std::istream& arguments)
{
	int gear;
	arguments >> gear;

	if (!m_car.IsEngineTurnOn())
	{
		m_output << "The engine is not turned on" "\n";
	}
	else if(!m_car.SetGear(gear))
	{
		m_output << "The vehicle speed is not suitable\n";
	}

	return true;
}

bool CCarController::SetSpeed(std::istream& arguments)
{
	int speed;
	arguments >> speed;

	if (!m_car.IsEngineTurnOn())
	{
		m_output << "The engine is not turned on" "\n";
	}
	else if (!m_car.SetSpeed(speed))
	{
		m_output << "The vehicle gear is not suitable for this speed\n";
	}

	return true;
}