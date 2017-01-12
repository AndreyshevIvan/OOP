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

struct Rational
{
	CRational rational = CRational(5, 7);
};

BOOST_AUTO_TEST_SUITE(Constructor_of_rational_numbers_can_work_)

	BOOST_AUTO_TEST_CASE(without_numerator_and_denominator)
	{
		BOOST_CHECK(IsRationalEqual(CRational(), 0, 1));
	}

	BOOST_AUTO_TEST_CASE(with_numerator_only)
	{
		BOOST_CHECK(IsRationalEqual(CRational(30), 30, 1));
		BOOST_CHECK(IsRationalEqual(CRational(0), 0, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-150), -150, 1));
	}

	BOOST_AUTO_TEST_CASE(with_numerator_and_denominator)
	{
		BOOST_CHECK(IsRationalEqual(CRational(0, 0), 0, 1));
		BOOST_CHECK(IsRationalEqual(CRational(10, 2), 5, 1));
		BOOST_CHECK(IsRationalEqual(CRational(-20, 200), -1, 10));
		BOOST_CHECK(IsRationalEqual(CRational(1, -50), -1, 50));
		BOOST_CHECK(IsRationalEqual(CRational(8, -2), -4, 1));
		BOOST_CHECK(IsRationalEqual(CRational(2, 0), 0, 1));
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rational_numbers_can_)

	BOOST_AUTO_TEST_CASE(convert_to_double)
	{
		double positiveDouble = 5 / 3;
		BOOST_CHECK(CRational(5, 3).ToDouble() == positiveDouble);

		double zeroDouble = 0;
		BOOST_CHECK(CRational(0, 13).ToDouble() == zeroDouble);

		double negativeDouble = -1 / 3;
		BOOST_CHECK(CRational(1, -3).ToDouble() == negativeDouble);
	}

	BOOST_AUTO_TEST_CASE(convert_to_compound_fraction)
	{
		CRational rational(18, 3);
		std::pair<int, CRational> positiveCompoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(positiveCompoundFraction.first, 6);
		BOOST_CHECK_EQUAL(positiveCompoundFraction.second, CRational(0, 1));

		rational = CRational(-31, 5);
		std::pair<int, CRational> negativeCompoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(negativeCompoundFraction.first, -6);
		BOOST_CHECK_EQUAL(negativeCompoundFraction.second, CRational(-1, 5));

		rational = CRational(0, 100);
		std::pair<int, CRational> zeroCompoundFraction = rational.ToCompoundFraction();
		BOOST_CHECK_EQUAL(zeroCompoundFraction.first, 0);
		BOOST_CHECK_EQUAL(zeroCompoundFraction.second, CRational(0, 1));
	}

	BOOST_AUTO_TEST_CASE(rational_must_be_able_to_create_compound_fraction_from_a_constant)
	{
		const CRational rational(10, 3);
		std::pair<int, CRational> compoundFraction = rational.ToCompoundFraction();
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rational_numbers_have_)

	BOOST_AUTO_TEST_CASE(unary_plus_operator)
	{
		CRational const num1(-2, 4);
		CRational num2 = +num1;
		BOOST_CHECK(IsRationalEqual(num1, num2.GetNumerator(), num2.GetDenominator()));
	}

	BOOST_AUTO_TEST_CASE(unary_minus_operator)
	{
		CRational const num1(1, 3);
		CRational num2 = -num1;
		BOOST_CHECK(IsRationalEqual(num1, -num2.GetNumerator(), num2.GetDenominator()));
	}

	BOOST_FIXTURE_TEST_SUITE(binary_plus_with, Rational)

		BOOST_AUTO_TEST_CASE(rational_and_rational)
		{
			BOOST_CHECK(IsRationalEqual(CRational(1, 3) + CRational(2, 3), 1, 1));
			BOOST_CHECK(IsRationalEqual(CRational(-1, 3) + CRational(4, 3), 1, 1));
			BOOST_CHECK(IsRationalEqual(CRational(0, 0) + CRational(0, 0), 0, 1));
			BOOST_CHECK(IsRationalEqual(CRational(-10, 2) + CRational(10, 2), 0, 1));
		}

		BOOST_AUTO_TEST_CASE(int_and_rational)
		{
			int iNum = 4;
			BOOST_CHECK(IsRationalEqual(iNum + rational, 33, 7));
		}

		BOOST_AUTO_TEST_CASE(rational_and_int)
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

	BOOST_FIXTURE_TEST_SUITE(increase_itself_on, Rational)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CRational increaseRational(3, 7);
			rational += increaseRational;
			BOOST_CHECK(IsRationalEqual(rational, 8, 7));
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			int increaseInt = 4;
			rational += increaseInt;
			BOOST_CHECK(IsRationalEqual(rational, 33, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(reduction_itself_on, Rational)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CRational reducingRational(2, 7);
			rational -= reducingRational;
			BOOST_CHECK(IsRationalEqual(rational, 3, 7));
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			int reducingInt = 2;
			rational -= reducingInt;
			BOOST_CHECK(IsRationalEqual(rational, -9, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(multiplication_itself_on, Rational)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CRational multiplyRational(5, 7);
			rational *= multiplyRational;
			BOOST_CHECK(IsRationalEqual(rational, 25, 49));
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			int multiplyInt = 4;
			rational *= multiplyInt;
			BOOST_CHECK(IsRationalEqual(rational, 20, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(division_itself_on, Rational)

		BOOST_AUTO_TEST_CASE(rational_number)
		{
			CRational divisionRational(2, 5);
			rational /= divisionRational;
			BOOST_CHECK(IsRationalEqual(rational, 25, 14));
		}

		BOOST_AUTO_TEST_CASE(int_number)
		{
			int multiplyInt = 4;
			rational *= multiplyInt;
			BOOST_CHECK(IsRationalEqual(rational, 20, 7));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(boolean_operators, Rational)

		BOOST_AUTO_TEST_CASE(equality_operator)
		{
			int intNum = 4;
			BOOST_CHECK(rational == rational);
			BOOST_CHECK(!(rational == CRational(1, 7)));
			BOOST_CHECK(!(rational == CRational(1, 7)));
			BOOST_CHECK(CRational(80, 20) == intNum);
			BOOST_CHECK(intNum == CRational(80, 20));
		}

		BOOST_AUTO_TEST_CASE(not_equality_operator)
		{
			int intNum = 7;
			CRational intNumInRat = CRational(49, 7);
			CRational notEqualrat = CRational(1, 7);

			BOOST_CHECK(!(rational != rational));
			BOOST_CHECK(rational != notEqualrat);
			BOOST_CHECK(notEqualrat != rational);
			BOOST_CHECK(!(intNumInRat != intNum));
		}

		BOOST_AUTO_TEST_CASE(less_than_operator)
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

		BOOST_AUTO_TEST_CASE(than_or_equal_operator)
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

		BOOST_AUTO_TEST_CASE(more_than_operator)
		{
			int intNumber = 5;
			CRational majorRat = rational + CRational(13, 2);
			CRational minorRat = rational - CRational(100, 20);

			BOOST_CHECK(majorRat > minorRat);
			BOOST_CHECK(intNumber > minorRat);
			BOOST_CHECK(majorRat > intNumber);
			BOOST_CHECK(!(rational > rational));
		}

		BOOST_AUTO_TEST_CASE(more_than_or_equal_operator)
		{
			int intNumber = 5;
			CRational majorRat = rational + CRational(13, 2);
			CRational minorRat = rational - CRational(100, 20);

			BOOST_CHECK(majorRat >= minorRat);
			BOOST_CHECK(majorRat >= majorRat);
			BOOST_CHECK(intNumber >= rational);
			BOOST_CHECK(majorRat >= intNumber);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(stream_operatrs, Rational)

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
	
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Others)

	BOOST_AUTO_TEST_CASE(adding_assignment_must_be_composable)
	{
		{
			int x = 3, y = 5;
			(x += y) += y;
		}
		{
			CRational x = 3, y = 5;
			(x += y) += y;
		}
	}
BOOST_AUTO_TEST_SUITE_END()