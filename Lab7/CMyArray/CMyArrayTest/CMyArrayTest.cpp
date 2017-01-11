#include "stdafx.h"
#include "../CMyArray/CMyArray.h"

#include <new>
#include <algorithm>

struct ArrayItem
{
	ArrayItem(int value = 0) : value(value)
	{}
	int value;
};

struct EmptyStringArray
{
	CMyArray<ArrayItem> arr;
};

BOOST_AUTO_TEST_SUITE(CMyArray_constructor)

BOOST_AUTO_TEST_CASE(_constrict_empty_array_by_default)
{
	CMyArray<std::string> strArr;
	BOOST_CHECK_EQUAL(strArr.GetSize(), 0);
}

BOOST_AUTO_TEST_CASE(_constrict_array_with_0_capacity_by_default)
{
	CMyArray<std::string> strArr;
	BOOST_CHECK_EQUAL(strArr.GetCapacity(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CMyArray_provides_the_ability_to_)

BOOST_AUTO_TEST_CASE(add_element_to_end)
{
	CMyArray<ArrayItem> arr;
	arr.Append(ArrayItem());
	BOOST_CHECK_EQUAL(arr.GetBack(), ArrayItem());
}

BOOST_AUTO_TEST_CASE(get_array_size)
{
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()