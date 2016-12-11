#include "stdafx.h"
#include "CParallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double density, double width, double height, double depth)
	:CBody("Parallelepiped", density)
{
	if (width < 0 || height < 0 || depth < 0)
	{
		throw std::invalid_argument("Parallelepiped parametres should not be negative\n");
	}

	m_width = width;
	m_height = height;
	m_depth = depth;
}


double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return GetWidth() * GetHeight() * GetDepth();
}
	
void CParallelepiped::AddProperties(ostream& stream) const
{
	stream << "\tWidth: " << GetWidth() << "\n";
	stream << "\tHeight: " << GetHeight() << "\n";
	stream << "\tDepth: " << GetDepth() << "\n";
}