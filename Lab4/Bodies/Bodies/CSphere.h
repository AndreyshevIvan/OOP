#pragma once
#include "stdafx.h"
#include "CBody.h"

class CSphere : public CBody
{
public:
	CSphere(double density, double radius);
	double GetRadius() const;
	double GetVolume() const override;

protected:
	void AddProperties(std::ostream& strm) const override;

private:
	double m_radius;
};