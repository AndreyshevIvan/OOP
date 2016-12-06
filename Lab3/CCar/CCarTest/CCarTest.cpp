#include "stdafx.h"
#include "..\CCar\CCar.h"

using namespace std;

struct FixtureCar
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(test_ccar, FixtureCar)

BOOST_AUTO_TEST_CASE(is_engine_turn_off_by_default)
{
	BOOST_CHECK(!car.TurnOffEngine());
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(car.TurnOffEngine());
}

BOOST_AUTO_TEST_CASE(set_invalid_gear_for_turned_on_engin)
{
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(!car.SetGear(2));
	BOOST_CHECK(!car.SetGear(3));
	BOOST_CHECK(!car.SetGear(4));
	BOOST_CHECK(!car.SetGear(5));
}

BOOST_AUTO_TEST_SUITE_END()
