#include "stdafx.h"
#include "CRational.h"

CRational::CRational(int numerator, int denominator)
	:m_numerator(numerator)
	,m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return static_cast<double>(m_numerator / m_denominator);
}

void CRational::Normalize()
{
	int greaterCommonDivisor;
	int a = abs(m_numerator);
	int b = m_denominator;

	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	greaterCommonDivisor = (a != 0) ? a : 1;

	m_numerator /= greaterCommonDivisor;
	m_denominator /= greaterCommonDivisor;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

const CRational CRational::operator+() const
{
	return *this;
}