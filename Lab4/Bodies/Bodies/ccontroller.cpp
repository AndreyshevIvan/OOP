#include "stdafx.h"
#include "ccontroller.h"

using namespace std;
using namespace std::placeholders;

CController::CController(std::vector<std::shared_ptr<CBody>>& bodies, std::istream& input, std::ostream& output)
	:m_bodies(bodies)
	,m_input(input)
	,m_output(output)
	,m_actions({
		{ "Help", bind(&CController::Help, this) },
		{ "Sphere", bind(&CController::CreateSphere, this, _1) },
		{ "Parallelepiped", bind(&CController::CreateParallelepiped, this, _1) },
		{ "Cone", bind(&CController::CreateCone, this, _1) },
		{ "Cylinder", bind(&CController::CreateCylinder, this, _1) },
		{ "Compound", bind(&CController::CreateCompoundBody, this, _1) },
		})
{

}
bool CController::HandleCommand()
{
	string commandLine;

	if (!getline(m_input, commandLine) || (commandLine == "Finish"))
	{
		return false;
	}

	istringstream stream(commandLine);
	string action;
	stream >> action;
	
	auto it = m_actions.find(action);
	if (it != m_actions.end())
	{
		it->second(stream);
		return true;
	}

	m_output << "Invalid command!" "\n";
	return false;
}

bool CController::Help()
{
	m_output << "Commands:\n"
		<< "> Sphere <density> <radius>\n"
		<< "> Parallelepiped <density> <width> <height> <depth>\n"
		<< "> Cone <density> <radius> <height>\n"
		<< "> Cylinder <density> <radius> <height>\n"
		<< "> Compound - to begining add elements to compound body\n"
		<< "> Finish - to finish add elements to compound body or exit\n";

	return true;
}

void CController::PrintAllBodies(std::vector<std::shared_ptr<CBody>> const& bodies)
{
	if (!bodies.empty())
	{
		for (auto &body : bodies)
		{
			m_output << body->ToString();
		}
	}
	else
	{
		m_output << "You have not entered figures\n";
	}
}

void CController::FindBodyWithMaxMass(std::vector<std::shared_ptr<CBody>> const& bodies)
{
	bodies;
}

void CController::FindBodyWithSmallestWeight(std::vector<std::shared_ptr<CBody>> const& bodies)
{
	bodies;
}

bool CController::CreateSphere(std::istream& args)
{
	bool isAdded = true;
	double density;
	double radius;

	if (!(args >> density) || !(args >> radius))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Sphere <density> <radius>\n";
		isAdded = false;
	}

	if (isAdded)
	{
		try
		{
			shared_ptr<CBody> sphere = make_shared<CSphere>(density, radius);
			m_bodies.push_back(sphere);
		}
		catch (invalid_argument const& e)
		{
			m_output << e.what();
		}
	}
	return isAdded;
}

bool CController::CreateParallelepiped(std::istream& args)
{
	bool isAdded = true;
	double density;
	double width;
	double height;
	double depth;

	if (!(args >> density) || !(args >> width) || !(args >> height) || !(args >> depth))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Parallelepiped <density> <width> <height> <depth>\n";
		isAdded = false;
	}

	if (isAdded)
	{
		try
		{
			shared_ptr<CBody> parallelepiped = make_shared<CParallelepiped>(density, width, height, depth);
			m_bodies.push_back(parallelepiped);
		}
		catch (invalid_argument const& e)
		{
			m_output << e.what();
		}
	}
	return isAdded;
}

bool CController::CreateCone(std::istream& args)
{
	bool isAdded = true;
	double density;
	double height;
	double radius;

	if (!(args >> density) || !(args >> radius) || !(args >> height))
	{
		m_output << "Invalid count of arguments\n"
			<< "Usage: Cone <density> <radius> <height>\n";
		isAdded = false;
	}

	if (isAdded)
	{
		try
		{
			shared_ptr<CBody> cone = make_shared<CCone>(density, radius, height);
			m_bodies.push_back(cone);
		}
		catch (invalid_argument const& e)
		{
			m_output << e.what();
		}
	}
	return isAdded;
}

bool CController::CreateCylinder(std::istream& args)
{
	args;
	return true;
}

bool CController::CreateCompoundBody(std::istream& args)
{
	args;
	return true;
}