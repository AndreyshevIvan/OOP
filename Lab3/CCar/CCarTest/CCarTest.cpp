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

BOOST_AUTO_TEST_CASE(try_to_set_speed_or_gear_with_turned_off_engin)
{
	BOOST_CHECK(!car.SetGear(-1));
	BOOST_CHECK(!car.SetGear(0));
	BOOST_CHECK(!car.SetGear(1));
	BOOST_CHECK(!car.SetGear(2));
	BOOST_CHECK(!car.SetGear(3));
	BOOST_CHECK(!car.SetGear(4));
	BOOST_CHECK(!car.SetGear(5));

	BOOST_CHECK(!car.SetSpeed(10));
	BOOST_CHECK(!car.SetSpeed(30));
	BOOST_CHECK(!car.SetSpeed(80));
	BOOST_CHECK(!car.SetSpeed(100));
}

BOOST_AUTO_TEST_CASE(try_to_set_invalid_gear_for_turned_on_engin)
{
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(!car.SetGear(2));
	BOOST_CHECK(!car.SetGear(3));
	BOOST_CHECK(!car.SetGear(4));
	BOOST_CHECK(!car.SetGear(5));
}

BOOST_AUTO_TEST_CASE(try_to_gain_invalid_speed_for_this_gear)
{
	BOOST_CHECK(car.TurnOnEngine());
	BOOST_CHECK(!car.SetGear(2));
	BOOST_CHECK(!car.SetGear(3));
	BOOST_CHECK(!car.SetGear(4));
	BOOST_CHECK(!car.SetGear(5));
}

BOOST_AUTO_TEST_CASE(try_to_set_direction_stay_on_second_gear)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	BOOST_CHECK(!car.SetSpeed(0));
}

BOOST_AUTO_TEST_CASE(try_to_set_gear_first_when_direction_is_backward)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(15);
	BOOST_CHECK(!car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(double_set_gears)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	BOOST_CHECK(car.SetGear(-1));
	car.SetSpeed(0);
	car.SetGear(0);
	BOOST_CHECK(car.SetGear(0));
	car.SetSpeed(20);
	car.SetGear(1);
	BOOST_CHECK(car.SetGear(1));
	car.SetSpeed(30);
	car.SetGear(2);
	BOOST_CHECK(car.SetGear(2));
}

BOOST_AUTO_TEST_CASE(set_max_and_min_speed)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	BOOST_CHECK(car.SetSpeed(20));
	BOOST_CHECK(!car.SetSpeed(-21));
	car.SetSpeed(0);
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(3);
	car.SetSpeed(60);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);
	BOOST_CHECK(car.SetSpeed(150));
	BOOST_CHECK(!car.SetSpeed(151));
}

BOOST_AUTO_TEST_CASE(try_to_set_fitst_gear_on_neutral_when_car_go_back)
{
	car.TurnOnEngine();
	car.SetGear(-1);
	car.SetSpeed(13);
	car.SetGear(0);
	BOOST_CHECK(!car.SetGear(1));
}

BOOST_AUTO_TEST_CASE(gain_speed_on_neutral_gear)
{
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(0);
	BOOST_CHECK(!car.SetSpeed(42));
	BOOST_CHECK(car.SetSpeed(38));
}

BOOST_AUTO_TEST_SUITE_END()
