#pragma once
#include "stdafx.h"
#include "CBody.h"

class CCone : public CBody
{
public:
	CCone(double density, double radius, double height);
	double GetBaseRadius() const;
	double GetHeight() const;
	double GetVolume() const override;

protected:
	void AddProperties(std::ostream& strm) const override;

private:
	double m_radius;
	double m_height;
};