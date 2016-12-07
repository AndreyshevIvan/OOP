#pragma once
#include "stdafx.h"
#include <iostream>

class CRational final
{
public:
	CRational::CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;

	const CRational operator-() const;
	const CRational operator+() const;

	const CRational& operator+=(CRational const& value);
	const CRational& operator-=(CRational const& value);
	const CRational& operator*=(CRational const& value);
	const CRational& operator/=(CRational const& value);

	void ToMixedNumeral(int& integer, CRational& rational);
private:
	int m_numerator;
	int m_denominator;

	void Normalize();
};

CRational const operator+(CRational const& firstValue, CRational const& secondValue);
CRational const operator-(CRational const& firstValue, CRational const& secondValue);
CRational const operator*(CRational const& firstValue, CRational const& secondValue);
CRational const operator/(CRational const& firstValue, CRational const& secondValue);

bool operator==(CRational const& firstValue, CRational const& secondValue);
bool operator!=(CRational const& firstValue, CRational const& secondValue);
bool operator<(CRational const& firstValue, CRational const& secondValue);
bool operator<=(CRational const& firstValue, CRational const& secondValue);
bool operator>(CRational const& firstValue, CRational const& secondValue);
bool operator>=(CRational const& firstValue, CRational const& secondValue);

std::ostream& operator<<(std::ostream& output, CRational const& rational);
std::istream& operator>>(std::istream& input, CRational& rational);