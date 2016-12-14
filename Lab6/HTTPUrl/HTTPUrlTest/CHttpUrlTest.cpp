#include "stdafx.h"
#include "..\HTTPUrl\CHttpUrl.h"

BOOST_AUTO_TEST_CASE(check_get_functions)
{
	CHttpUrl url("http://domain.ru:80/document");
	BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(url.GetDomain(), "domain.ru");
	BOOST_CHECK_EQUAL(url.GetPort(), 80);
	BOOST_CHECK_EQUAL(url.GetDocument(),"/document");
}

BOOST_AUTO_TEST_CASE(invalid_protocol)
{
	BOOST_REQUIRE_THROW(CHttpUrl("ftp://domain/document"), std::invalid_argument);
}