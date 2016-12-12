#include "stdafx.h"
#include "CSphere.h"

using namespace std;

CSphere::CSphere(double density, double radius)
	:CBody("Sphere", density)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius should not be negative\n");
	}

	m_radius = radius;
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (pow(m_radius, 3) * M_PI) * 4 / 3;
}

void CSphere::AddProperties(ostream& strm) const
{
	strm << "\tRadius: " << GetRadius() << "\n";
}