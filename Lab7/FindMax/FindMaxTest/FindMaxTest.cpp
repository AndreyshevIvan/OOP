#include "stdafx.h"
#include "../FindMax/FindMaxEx.h"
#include "Sportsman.h"

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