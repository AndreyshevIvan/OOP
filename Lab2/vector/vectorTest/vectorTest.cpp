#include "stdafx.h"
#include "..\vector\processVector.h"
#include <vector>

using namespace std;

bool IsVectorsAreEquals(vector<double> const& numbers, vector<double> const& requiredNumbers)
{
	if (numbers.size() != requiredNumbers.size())
	{
		return false;
	}
	for (size_t i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] != requiredNumbers[i])
		{
			return false;
		}
	}
	
	return true;
}

BOOST_AUTO_TEST_SUITE(SearchMinElement_function)

BOOST_AUTO_TEST_CASE(check_search_min_element_if_all_elements_are_equals)
{
	vector<double> numbers = { 0, 0, 0, 0, 0 };
	double searchElement;
	SearchMinElement(numbers, searchElement);
	BOOST_CHECK(searchElement == 0);
}

BOOST_AUTO_TEST_CASE(check_search_min_element)
{
	vector<double> numbers = { -10, -5, 0, -1000.5, 4 };
	double searchElement;
	SearchMinElement(numbers, searchElement);
	BOOST_CHECK(searchElement == -1000.5);
}

BOOST_AUTO_TEST_CASE(check_search_min_element_in_empty_vector)
{
	vector<double> numbers = {};
	double searchElement = 0;
	BOOST_CHECK(!SearchMinElement(numbers, searchElement));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ProcessVector_function)

BOOST_AUTO_TEST_CASE(make_empty_vector_from_empty_vector)
{
	vector<double> numbers = {};
	vector<double> requiredNumbers = {};
	ProcessVector(numbers);
	BOOST_CHECK(IsVectorsAreEquals(numbers, requiredNumbers));
}

BOOST_AUTO_TEST_CASE(check_search_and_multiplication_elements)
{
	vector<double> numbers = {-10, 0, 100, -1};
	vector<double> requiredNumbers = {100, 0, -1000, 10};
	ProcessVector(numbers);
	BOOST_CHECK(IsVectorsAreEquals(numbers, requiredNumbers));

	numbers = {-12.5, -100, 0, 1};
	requiredNumbers = {1250, 10000, 0, -100};
	ProcessVector(numbers);
	BOOST_CHECK(IsVectorsAreEquals(numbers, requiredNumbers));
}

BOOST_AUTO_TEST_SUITE_END()