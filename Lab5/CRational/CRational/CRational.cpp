#include "stdafx.h"
#include "CRational.h"
#include <iostream>

CRational::CRational(int numerator, int denominator)
	:m_numerator(numerator)
	,m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	else if (denominator < 0)
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

CRational const operator+(CRational const& firstValue, CRational const& secondValue)
{
	int numerator;
	int denominator;

	if (firstValue.GetDenominator() == secondValue.GetDenominator())
	{
		numerator = firstValue.GetNumerator() + secondValue.GetNumerator();
		denominator = firstValue.GetDenominator();
	}
	else
	{
		denominator = firstValue.GetDenominator() * secondValue.GetDenominator();
		numerator = firstValue.GetNumerator() * secondValue.GetDenominator() +
			secondValue.GetNumerator() * firstValue.GetDenominator();
	}

	return CRational(numerator, denominator);
}

CRational const operator-(CRational const& firstValue, CRational const& secondValue)
{
	return firstValue + (-secondValue);
}

CRational const operator*(CRational const& firstValue, CRational const& secondValue)
{
	int numerator;
	int denominator;

	numerator = firstValue.GetNumerator() * secondValue.GetNumerator();
	denominator = firstValue.GetDenominator() * secondValue.GetDenominator();

	return CRational(numerator, denominator);
}

CRational const operator/(CRational const& firstValue, CRational const& secondValue)
{
	int numerator;
	int denominator;

	numerator = secondValue.GetDenominator();
	denominator = secondValue.GetNumerator();

	return CRational(numerator, denominator) * firstValue;
}

CRational& CRational::operator+=(CRational const& value)
{
	*this = *this + value;

	return *this;
}

CRational& CRational::operator-=(CRational const& value)
{
	*this += -value;

	return *this;
}

CRational& CRational::operator*=(CRational const& value)
{
	*this = *this * value;

	return *this;
}

CRational& CRational::operator/=(CRational const& value)
{
	*this = *this / value;

	return *this;
}

bool operator==(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue - secondValue).GetNumerator() == 0;
}

bool operator!=(CRational const& firstValue, CRational const& secondValue)
{
	if (firstValue == secondValue)
	{
		return false;
	}
	
	return true;
}

bool operator<(CRational const& firstValue, CRational const& secondValue)
{
	int firstNumerator = firstValue.GetNumerator() * secondValue.GetDenominator();
	int secondNumerator = secondValue.GetNumerator() * firstValue.GetDenominator();

	return firstNumerator < secondNumerator;
}

bool operator<=(CRational const& firstValue, CRational const& secondValue)
{
	return (firstValue < secondValue) || (firstValue == secondValue);
}

bool operator>(CRational const& firstValue, CRational const& secondValue)
{
	return !(firstValue <= secondValue);
}

bool operator>=(CRational const& firstValue, CRational const& secondValue)
{
	return !(firstValue < secondValue);
}

std::ostream& operator<<(std::ostream& output, CRational const& rational)
{
	output << rational.GetNumerator() << '/' << rational.GetDenominator();
	return output;
}

std::istream& operator>>(std::istream& input, CRational& rational)
{
	int numerator;
	int denominator;

	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		rational = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit);
	}

	return input;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	std::pair<int, CRational> result;

	bool isNumberNegative = false;

	int numerator = this->GetNumerator();
	int denominator = this->GetDenominator();
	int intPart = 0;
	
	if (numerator < 0)
	{
		isNumberNegative = true;
		numerator = abs(numerator);
	}

	while (numerator >= denominator)
	{
		numerator -= denominator;
		intPart++;
	}

	if (isNumberNegative)
	{
		intPart = -intPart;
		numerator = -numerator;
	}

	CRational rationalPart(numerator, denominator);
	
	result.first = intPart;
	result.second = rationalPart;

	return result;
}