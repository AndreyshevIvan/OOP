#include "stdafx.h"
#include "../FindMax/FindMaxEx.h"
#include "Sportsman.h"

class MockClass
{
public:
	MockClass(bool doThrow, int number)
		:m_doThrow(doThrow)
		,m_number(number)
	{
	}
	int m_number;
	bool m_doThrow;
};

bool MockLess(MockClass const& firstMock, MockClass const& secondMock)
{
	if (firstMock.m_doThrow || secondMock.m_doThrow)
	{
		throw std::logic_error("Memory error\n");
	}
	if (firstMock.m_number <= secondMock.m_number)
	{
		return false;
	}

	return true;
}

const Sportsman sportsmanFirst = { "Ivan Andreyshev", 77.3, 185.93f };
const Sportsman sportsmanSecond = { "Jason Statham", 80.5, 206.1f };
const Sportsman sportsmanThird = { "Arny", 105.3, 178.88f };

const std::vector<Sportsman> sportsmans = { sportsmanFirst , sportsmanSecond, sportsmanThird };

Sportsman man;

BOOST_AUTO_TEST_SUITE(FindMaxEx_)

BOOST_AUTO_TEST_CASE(can_work_with_empty_vector)
{
	std::vector<Sportsman> emptyVector;
	BOOST_CHECK(emptyVector.empty());
	BOOST_CHECK(!FindMaxEx(emptyVector, man, IsNameLess));
	BOOST_CHECK(!FindMaxEx(emptyVector, man, IsWeightLess));
	BOOST_CHECK(!FindMaxEx(emptyVector, man, IsHeightLess));
}

BOOST_AUTO_TEST_CASE(can_found_max_string)
{
	std::string maxName = sportsmanSecond.name;
	BOOST_CHECK(FindMaxEx(sportsmans, man, IsNameLess));
	BOOST_CHECK_EQUAL(man.name, maxName);
}

BOOST_AUTO_TEST_CASE(can_found_max_double)
{
	double maxWeight = sportsmanThird.weight;
	BOOST_CHECK(FindMaxEx(sportsmans, man, IsWeightLess));
	BOOST_CHECK_EQUAL(man.weight, maxWeight);
}

BOOST_AUTO_TEST_CASE(can_found_max_float)
{
	float maxHeight = sportsmanSecond.height;
	BOOST_CHECK(FindMaxEx(sportsmans, man, IsHeightLess));
	BOOST_CHECK_EQUAL(man.height, maxHeight);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Variable_for_the_maximum_value_does_not_change_if)
	
BOOST_AUTO_TEST_CASE(_the_input_vector_is_empty)
{
	const std::vector<Sportsman> emptyVector;
	Sportsman maxValue = { "Name", 100.99, 199.99f };

	FindMaxEx(sportsmans, maxValue, IsHeightLess);

	BOOST_CHECK_EQUAL(maxValue.height, maxValue.height);
	BOOST_CHECK_EQUAL(maxValue.name, maxValue.name);
	BOOST_CHECK_EQUAL(maxValue.weight, maxValue.weight);
}

BOOST_AUTO_TEST_CASE(_program_throw_exception_then_find_started)
{
	const std::vector<MockClass> mockVector = {
		MockClass(false, 1),
		MockClass(false, 2),
		MockClass(true, 3),
		MockClass(false, 4)
	};

	MockClass maxElement(false, 0);
	MockClass copy_maxElement = maxElement;

	BOOST_REQUIRE_THROW(FindMaxEx(mockVector, maxElement, MockLess), std::logic_error);
	BOOST_CHECK_EQUAL(maxElement.m_number, copy_maxElement.m_number);
}

BOOST_AUTO_TEST_SUITE_END()