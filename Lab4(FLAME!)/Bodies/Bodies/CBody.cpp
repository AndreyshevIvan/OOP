#include "stdafx.h"
#include "CBody.h"

using namespace std;

CBody::CBody(const std::string& type)
	:m_type(type)
	,m_density(0)
{
}

CBody::CBody(const std::string& type, double density)
	:m_type(type)
{
	if (density < 0)
	{
		throw std::invalid_argument("Density should not be negative\n");
	}
	m_density = density;
}

double CBody::GetDensity() const
{
	return m_density;
}

double CBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

string CBody::ToString() const
{
	std::ostringstream stream;
	stream << m_type << ":\n"
		<< "\tDensity: " << GetDensity() << "\n"
		<< "\tVolume: " << GetVolume() << "\n"
		<< "\tMass: " << GetMass() << "\n";

	AddProperties(stream);
	return stream.str();
}