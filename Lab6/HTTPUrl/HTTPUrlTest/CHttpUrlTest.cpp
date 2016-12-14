#include "stdafx.h"
#include "..\HTTPUrl\CHttpUrl.h"

BOOST_AUTO_TEST_CASE(get_functions_can_return_values)
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

	CHttpUrl urlWithoutZeroPort("https://domain.ru:0/document");
	BOOST_CHECK_EQUAL(urlWithoutZeroPort.GetPort(), 0);

	CHttpUrl urlWithDomainAndDoc("vk.com", "document");
	BOOST_CHECK_EQUAL(urlWithDomainAndDoc.GetPort(), 80);
	BOOST_CHECK_EQUAL(urlWithDomainAndDoc.GetDocument(), "/document");
}

BOOST_AUTO_TEST_CASE(info_can_return_full_information_about_url)
{
	std::string refStr = "URL: http://vk.com:77/doc\n\tProtocol: http\n\tDomain: vk.com\n\tPort: 77\n\tDocument: /doc\n";
	std::ofstream file("output.txt");
	std::string url = "http://vk.com:77/doc";
	file << Info(CHttpUrl(url));
	BOOST_CHECK_EQUAL(Info(CHttpUrl(url)), refStr);
}

BOOST_AUTO_TEST_CASE(get_string_with_url_only)
{
	std::string refStr = "https://site.com:0/documentation";
	std::string url = "https://site.com:0/documentation";
	BOOST_CHECK_EQUAL(CHttpUrl(url).GetURL(), refStr);
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
	BOOST_REQUIRE_THROW(CHttpUrl("://domain/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_url_without_slashes)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http/domain/document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("https:domain/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_invalid_domain)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http:///document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("https://:10/document"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(exception_invalid_port)
{
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:/document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:65536/document"), std::invalid_argument);
	BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:-0/document"), std::invalid_argument);
}

