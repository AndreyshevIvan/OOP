#include "stdafx.h"
#include "..\HTTPUrl\CHttpUrl.h"

BOOST_AUTO_TEST_CASE(check_get_functions)
{
	CHttpUrl normalURL("http://domain.ru:80/document");
	BOOST_CHECK_EQUAL(normalURL.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(normalURL.GetDomain(), "domain.ru");
	BOOST_CHECK_EQUAL(normalURL.GetPort(), 80);
	BOOST_CHECK_EQUAL(normalURL.GetDocument(),"/document");

	CHttpUrl httpsURL("https://domain.ru:80/document");
	BOOST_CHECK_EQUAL(httpsURL.GetProtocol(), Protocol::HTTPS);

	CHttpUrl urlWithoutPortHTTP("http://domain.ru/document");
	BOOST_CHECK_EQUAL(urlWithoutPortHTTP.GetPort(), 80);

	CHttpUrl urlWithoutPortHTTPS("https://domain.ru/document");
	BOOST_CHECK_EQUAL(urlWithoutPortHTTPS.GetPort(), 443);
}

BOOST_AUTO_TEST_CASE(check_get_functions_with_invalid_url)
{
	CHttpUrl url("http://domain.ru:80/document");
	BOOST_CHECK_EQUAL(url.GetProtocol(), Protocol::HTTP);
	BOOST_CHECK_EQUAL(url.GetDomain(), "domain.ru");
	BOOST_CHECK_EQUAL(url.GetPort(), 80);
	BOOST_CHECK_EQUAL(url.GetDocument(), "/document");
}

BOOST_AUTO_TEST_CASE(exception_invalid_protocol)
{
	BOOST_REQUIRE_THROW(CHttpUrl("ftp://domain/document"), std::invalid_argument);
}