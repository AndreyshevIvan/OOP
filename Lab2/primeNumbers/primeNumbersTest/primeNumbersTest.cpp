#include "stdafx.h"
#include "..\primeNumbers\primeNumbers.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(PrimeNumbers_function)

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_0)
{
	set<int> requiredSet;
	BOOST_CHECK(GeneratePrimeNumbersSet(0) == requiredSet);
}

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_is_less_than_0)
{
	set<int> requiredSet;
	BOOST_CHECK(GeneratePrimeNumbersSet(-1) == requiredSet);
}

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_equal_2)
{
	set<int> requiredSet = { 2 };
	BOOST_CHECK(GeneratePrimeNumbersSet(0) == requiredSet);
}

BOOST_AUTO_TEST_CASE(generate_set_when_upperBound_equal_100)
{
	set<int> requiredSet = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
		37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };
	BOOST_CHECK(GeneratePrimeNumbersSet(0) == requiredSet);
}

BOOST_AUTO_TEST_CASE(size_of_set_than_upperBound_is_max_100000000)
{
	int requiredSize = 5761456;
	BOOST_CHECK(GeneratePrimeNumbersSet(100000000).size() == requiredSize);
}

BOOST_AUTO_TEST_SUITE_END()