#include "stdafx.h"
#include "..\bodies\bodies.h"

using namespace std;

struct Struct
{

};

BOOST_FIXTURE_TEST_SUITE(test, Struct)

BOOST_AUTO_TEST_CASE(test_1)
{
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
