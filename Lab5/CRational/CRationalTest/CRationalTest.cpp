#include "stdafx.h"
#include "..\CRational\CRational.h"
#include <vector>
#include <sstream>

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
		
	BOOST_AUTO_TEST_CASE(increase_the_number_on_rational_or_int)
	{
		CRational rational(3, 5);
		CRational increaseRational(7, 5);
		rational += increaseRational;
		BOOST_CHECK(IsRationalEqual(rational, 2, 1));

		int increaseInt = 4;
		rational += increaseInt;
		BOOST_CHECK(IsRationalEqual(rational, 6, 1));
	}

	BOOST_AUTO_TEST_CASE(reducing_the_number_on_rational_or_int)
	{
		CRational rational(3, 5);
		CRational reducingRational(2, 5);
		rational -= reducingRational;
		BOOST_CHECK(IsRationalEqual(rational, 1, 5));

		int reducingInt = 2;
		rational -= reducingInt;
		BOOST_CHECK(IsRationalEqual(rational, -9, 5));
	}

	BOOST_AUTO_TEST_CASE(multiply_the_number_on_rational_or_int)
	{
		CRational rational(2, 3);
		CRational multiplyRational(7, 5);
		rational *= multiplyRational;
		BOOST_CHECK(IsRationalEqual(rational, 14, 15));

		int multiplyInt = 4;
		rational *= multiplyInt;
		BOOST_CHECK(IsRationalEqual(rational, 56, 15));
	}

	BOOST_AUTO_TEST_CASE(devide_the_number_on_rational_or_int)
	{
		CRational rational(3, 5);
		CRational devideRational(2, 5);
		rational /= devideRational;
		BOOST_CHECK(IsRationalEqual(rational, 3, 2));

		int devideInt = 2;
		rational /= devideInt;
		BOOST_CHECK(IsRationalEqual(rational, 3, 4));
	}

	BOOST_FIXTURE_TEST_SUITE(check_boolean_operators, Rational)

		BOOST_AUTO_TEST_CASE(check_equality_of_two_rational_numbers)
		{
			int intNum = 4;
			BOOST_CHECK(rational == rational);
			BOOST_CHECK(!(rational == CRational(1, 7)));
			BOOST_CHECK(!(rational == CRational(1, 7)));
			BOOST_CHECK(CRational(80, 20) == intNum);
			BOOST_CHECK(intNum == CRational(80, 20));
		}

		BOOST_AUTO_TEST_CASE(check_not_equality_of_two_rational_numbers)
		{
			int intNum = 7;
			CRational intNumInRat = CRational(49, 7);
			CRational notEqualrat = CRational(1, 7);

			BOOST_CHECK(!(rational != rational));
			BOOST_CHECK(rational != notEqualrat);
			BOOST_CHECK(notEqualrat != rational);
			BOOST_CHECK(!(intNumInRat != intNum));
		}

		BOOST_AUTO_TEST_CASE(ñhecking_less_than_operator)
		{
			int intNumber = 2;
			CRational majorRat = rational + CRational(6, 7);
			CRational minorRat = rational - CRational(2, 7);

			BOOST_CHECK(!(rational < rational));
			BOOST_CHECK(rational < majorRat);
			BOOST_CHECK(minorRat < rational);
 			BOOST_CHECK(!(intNumber < rational));
			BOOST_CHECK(majorRat < intNumber);
		}

		BOOST_AUTO_TEST_CASE(ñhecking_less_than_or_equal_operator)
		{
			int intNumber = 4;
			CRational majorRat = rational + CRational(2, 7);
			CRational minorRat = rational - CRational(10, 7);

			BOOST_CHECK(rational <= rational);
			BOOST_CHECK(rational <= majorRat);
			BOOST_CHECK(rational <= intNumber);
			BOOST_CHECK(!(intNumber <= rational));
			BOOST_CHECK(minorRat <= majorRat);
		}

		BOOST_AUTO_TEST_CASE(ñhecking_more_than_operator)
		{
			int intNumber = 5;
			CRational majorRat = rational + CRational(13, 2);
			CRational minorRat = rational - CRational(100, 20);

			BOOST_CHECK(majorRat > minorRat);
			BOOST_CHECK(intNumber > minorRat);
			BOOST_CHECK(majorRat > intNumber);
			BOOST_CHECK(!(rational > rational));
		}

		BOOST_AUTO_TEST_CASE(ñhecking_more_than_or_equal_operator)
		{
			int intNumber = 5;
			CRational majorRat = rational + CRational(13, 2);
			CRational minorRat = rational - CRational(100, 20);

			BOOST_CHECK(majorRat >= minorRat);
			BOOST_CHECK(majorRat >= majorRat);
			BOOST_CHECK(intNumber >= rational);
			BOOST_CHECK(majorRat >= intNumber);
		}

		BOOST_AUTO_TEST_CASE(output_operator_can_write_rational_number)
		{
			ostringstream out1;
			out1 << CRational(4, 3);
			BOOST_CHECK_EQUAL(out1.str(), "4/3");

			ostringstream out2;
			out2 << CRational(-4, 3);
			BOOST_CHECK_EQUAL(out2.str(), "-4/3");

			ostringstream out3;
			out3 << CRational(-4, 0);
			BOOST_CHECK_EQUAL(out3.str(), "0/1");
		}

		BOOST_AUTO_TEST_CASE(input_operator_can_read_rational_number)
		{
			istringstream normalInput("3/4");
			normalInput >> rational;
			BOOST_CHECK(IsRationalEqual(rational, 3, 4));

			istringstream negativeInput("-3/4");
			negativeInput >> rational;
			BOOST_CHECK(IsRationalEqual(rational, -3, 4));

			istringstream invalidInput("3</>4");
			invalidInput >> rational;
			BOOST_CHECK(invalidInput.failbit);
		}

		BOOST_AUTO_TEST_CASE(convert_to_mixed_numeral)
		{
			rational = CRational(18, 3);
			int number;
			CRational newRat;

			rational.ToMixedNumeral(number, newRat);
			BOOST_CHECK(number == 6);
			BOOST_CHECK(IsRationalEqual(newRat, 0, 1));

			rational = CRational(-31, 19);
			rational.ToMixedNumeral(number, newRat);
			BOOST_CHECK(number == -1);
			BOOST_CHECK(IsRationalEqual(newRat, 12, 19));
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()