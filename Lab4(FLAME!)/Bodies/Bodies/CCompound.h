#pragma once
#include "stdafx.h"
#include "CBody.h"

class CCompound : public CBody
{
public:
	CCompound();
	bool AddBody(std::shared_ptr<CBody> const &element);
	double GetMass() const override;
	double GetVolume() const override;

protected:
	void AddProperties(std::ostream &strm) const override;

private:
	std::vector<std::shared_ptr<CBody>> m_elements;
	void SetDensity();
};