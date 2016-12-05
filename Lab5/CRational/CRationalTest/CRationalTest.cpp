#include "stdafx.h"
#include "..\CRational\CRational.h"
#include <vector>

using namespace std;

bool IsRationalEqual(CRational const& CheckRational, int expectedNumerator, int expectedDenominator)
{
	if (CheckRational.GetNumerator() != expectedNumerator)
	{
		return false;
	}
	if (CheckRational.GetDenominator() != expectedDenominator)
	{
		return false;
	}

	return true;
}

BOOST_AUTO_TEST_SUITE(construct_rational_numbers)

	BOOST_AUTO_TEST_CASE(can_be_constructed_without_numerator_and_denominator)
	{
	BOOST_CHECK(IsRationalEqual(CRational(), 0, 1));
	}

	BOOST_AUTO_TEST_CASE(can_be_constructed_without_denominator)
	{
		BOOST_CHECK(IsRationalEqual(CRational(30), 30, 1));
		BOOST_CHECK(IsRationalEqual(CRational(0), 0, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-150), -150, 1));
	}

	BOOST_AUTO_TEST_CASE(create_rational_with_denominator_and_numerator)
	{
		BOOST_CHECK(IsRationalEqual(CRational(0, 0), 0, 1));
		BOOST_CHECK(IsRationalEqual(CRational(10, 2), 5, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-20, 200), -1, 10));
		BOOST_CHECK(IsRationalEqual(CRational(1, -50), -1, 50));
		BOOST_CHECK(IsRationalEqual(CRational(8, -2), -4, 1));
		BOOST_CHECK(IsRationalEqual(CRational(2, 0), 0, 1));
	}

	BOOST_AUTO_TEST_CASE(rational_number_can_convert_to_double)
	{
		double positiveDouble = 5 / 3;
		BOOST_CHECK(CRational(5, 3).ToDouble() == positiveDouble);

		double zeroDouble = 0;
		BOOST_CHECK(CRational(0, 13).ToDouble() == zeroDouble);

		double negativeDouble = -1 / 3;
		BOOST_CHECK(CRational(1, -3).ToDouble() == negativeDouble);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_operators_for_rational_numbers)

	BOOST_AUTO_TEST_CASE(check_unary_plus)
	{
		CRational num1(-2, 4);
		CRational num2 = +num1;
		BOOST_CHECK(IsRationalEqual(num1, num2.GetNumerator(), num2.GetDenominator()));
	}

	BOOST_AUTO_TEST_CASE(check_unary_minus)
	{
		CRational num1(1, 3);
		CRational num2 = -num1;
		BOOST_CHECK(IsRationalEqual(num1, -num2.GetNumerator(), num2.GetDenominator()));
	}

	BOOST_AUTO_TEST_CASE(check_addition_of_two_rational_numbers)
	{
		BOOST_CHECK(IsRationalEqual(CRational(1, 3) + CRational(2, 3), 1, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-1, 3) + CRational(4, 3), 1, 1));
		BOOST_CHECK(IsRationalEqual(CRational(0, 0) + CRational(0, 0), 0, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-10, 2) + CRational(10, 2), 0, 1));
	}

	struct Rational
	{
		CRational rational = CRational(5, 7);
	};
	BOOST_FIXTURE_TEST_SUITE(binary_plus_with, Rational)

		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(IsRationalEqual(rational + rational, 10, 7));
		}

		BOOST_AUTO_TEST_CASE(int_with_rational)
		{
			int iNum = 4;
			BOOST_CHECK(IsRationalEqual(iNum + rational, 33, 7));
		}

		BOOST_AUTO_TEST_CASE(rational_with_int)
		{
			int iNum = -2;
			BOOST_CHECK(IsRationalEqual(rational + iNum, -9, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(binary_minus_with, Rational)

		BOOST_AUTO_TEST_CASE(rational_and_rational)
		{
			BOOST_CHECK(IsRationalEqual(rational - rational, 0, 1));
		}

		BOOST_AUTO_TEST_CASE(int_and_rational)
		{
			int iNum = 5;
			BOOST_CHECK(IsRationalEqual(iNum - rational, 30, 7));
		}

		BOOST_AUTO_TEST_CASE(rational_and_int)
		{
			int iNum = 3;
			BOOST_CHECK(IsRationalEqual(rational - iNum, -16, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(binary_multiplication_with, Rational)

		BOOST_AUTO_TEST_CASE(rational_and_rational)
		{
			BOOST_CHECK(IsRationalEqual(rational * rational, 25, 49));
		}

		BOOST_AUTO_TEST_CASE(int_and_rational)
		{
			int iNum = 5;
			BOOST_CHECK(IsRationalEqual(iNum * rational, 25, 7));
		}

		BOOST_AUTO_TEST_CASE(rational_and_int)
		{
			int iNum = -3;
			BOOST_CHECK(IsRationalEqual(rational * iNum, -15, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(binary_division_with, Rational)

		BOOST_AUTO_TEST_CASE(rational_and_rational)
		{
			BOOST_CHECK(IsRationalEqual(rational / rational, 1, 1));
		}

		BOOST_AUTO_TEST_CASE(int_and_rational)
		{
			int iNum = 2;
			BOOST_CHECK(IsRationalEqual(iNum / rational, 14, 5));
		}

		BOOST_AUTO_TEST_CASE(rational_and_int)
		{
			int iNum = -3;
			BOOST_CHECK(IsRationalEqual(rational / iNum, -5, 21));
		}

		BOOST_AUTO_TEST_CASE(rational_and_zero_int)
		{
			int iNum = 0;
			BOOST_CHECK(IsRationalEqual(rational / iNum, 0, 1));
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()