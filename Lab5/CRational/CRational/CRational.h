#pragma once
#include "stdafx.h"
#include <iostream>

class CRational final
{
public:
	CRational::CRational(int numerator = 0, int denominator = 1);

	int GetNumerator()const;
	int GetDenominator()const;
	double ToDouble()const;

	const CRational operator-() const;
	const CRational operator+() const;

private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};
