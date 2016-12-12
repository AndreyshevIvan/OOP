#include "stdafx.h"
#include "CCompound.h"

CCompound::CCompound()
	: CBody("Compound")
{
}

bool CCompound::AddBody(std::shared_ptr<CBody> const &element)
{
	bool isAdded = true;
	if (this == &(*element))
	{
		isAdded = false;
	}

	if (isAdded)
	{
		m_elements.push_back(element);
		SetDensity();
	}
	return isAdded;
}

double CCompound::GetMass() const
{
	auto Mass = [](double &a, std::shared_ptr<CBody> b)
	{
		return a + b->GetMass();

	};
	return std::accumulate(m_elements.begin(), m_elements.end(), 0.0, Mass);
}

double CCompound::GetVolume() const
{
	auto Volume = [](double &a, std::shared_ptr<CBody> b)
	{
		return a + b->GetVolume();

	};
	return std::accumulate(m_elements.begin(), m_elements.end(), 0.0, Volume);

}

void CCompound::AddProperties(std::ostream & strm) const
{
	size_t elementsCount = m_elements.size();
	strm << "Compound body have " << std::to_string(elementsCount) << " elements\n";
	for (auto element : m_elements)
	{
		strm << "\t" << element->ToString();
	}
}

void CCompound::SetDensity()
{
	m_density = GetMass() / GetVolume();
}