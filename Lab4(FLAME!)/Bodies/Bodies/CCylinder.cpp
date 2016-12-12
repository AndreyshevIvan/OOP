#include "stdafx.h"
#include "CCylinder.h"

using namespace std;

CCylinder::CCylinder(double density, double radius, double height)
	:CBody("Cylinder", density)
{
	if (radius < 0 || height < 0)
	{
		throw std::invalid_argument("Radius and height should not be negative\n");
	}

	m_radius = radius;
	m_height = height;
}

double CCylinder::GetBaseRadius() const
{
	return m_radius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return (pow(m_radius, 2) * M_PI) * m_height;
}

void CCylinder::AddProperties(ostream& strm) const
{
	strm << "\tBaseRadius: " << GetBaseRadius() << "\n";
	strm << "\tHeight: " << GetHeight() << "\n";
}