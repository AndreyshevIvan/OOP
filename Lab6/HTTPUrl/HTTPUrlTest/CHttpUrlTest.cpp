#include "stdafx.h"
#include "..\HTTPUrl\CHttpUrl.h"

BOOST_AUTO_TEST_SUITE(class_functions)
	BOOST_AUTO_TEST_CASE(functions_return_value_from_normal_url)
	{
		CHttpUrl normalURL("http://domain.ru:80/document");
		BOOST_CHECK_EQUAL(normalURL.GetProtocol(), Protocol::HTTP);
		BOOST_CHECK_EQUAL(normalURL.GetDomain(), "domain.ru");
		BOOST_CHECK_EQUAL(normalURL.GetPort(), 80);
		BOOST_CHECK_EQUAL(normalURL.GetDocument(), "/document");
		CHttpUrl httpsURL("https://domain.ru:80/document");
		BOOST_CHECK_EQUAL(httpsURL.GetProtocol(), Protocol::HTTPS);
	}

	BOOST_AUTO_TEST_CASE(function_can_return_default_por_for_http)
	{
		CHttpUrl url("http://domain.ru/document");
		BOOST_CHECK_EQUAL(url.GetPort(), 80);
	}

	BOOST_AUTO_TEST_CASE(function_can_return_default_por_for_https)
	{
		CHttpUrl url("https://domain.ru/document");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
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
		std::string refStr = "https://site.com:100/documentation";
		std::string url = "https://site.com:100/documentation";
		BOOST_CHECK_EQUAL(CHttpUrl(url).GetURL(), refStr);
	}

	BOOST_AUTO_TEST_CASE(port_equal_1_avalable)
	{
		std::string url = "https://site.com:1/documentation";
		BOOST_CHECK_EQUAL(CHttpUrl(url).GetPort(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(class_constructor)
	BOOST_AUTO_TEST_CASE(url_can_be_construct_with_two_args)
	{
		CHttpUrl url2("vk.com", "document");
		BOOST_CHECK_EQUAL(url2.GetProtocol(), Protocol::HTTP);
		BOOST_CHECK_EQUAL(url2.GetDomain(), "vk.com");
		BOOST_CHECK_EQUAL(url2.GetPort(), 80);
		BOOST_CHECK_EQUAL(url2.GetDocument(), "/document");
	}
	BOOST_AUTO_TEST_CASE(url_can_be_construct_with_three_args)
	{
		CHttpUrl url3("vk.com", "document", Protocol::HTTP);
		BOOST_CHECK_EQUAL(url3.GetProtocol(), Protocol::HTTP);
		BOOST_CHECK_EQUAL(url3.GetDomain(), "vk.com");
		BOOST_CHECK_EQUAL(url3.GetPort(), 80);
		BOOST_CHECK_EQUAL(url3.GetDocument(), "/document");
	}
	BOOST_AUTO_TEST_CASE(url_can_be_construct_with_four_args)
	{
		CHttpUrl url4("vk.com", "document", Protocol::HTTPS, 500);
		BOOST_CHECK_EQUAL(url4.GetProtocol(), Protocol::HTTPS);
		BOOST_CHECK_EQUAL(url4.GetDomain(), "vk.com");
		BOOST_CHECK_EQUAL(url4.GetPort(), 500);
		BOOST_CHECK_EQUAL(url4.GetDocument(), "/document");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(exceptions_test)

	BOOST_AUTO_TEST_CASE(invalid_protocol_or_protocol_s_absent)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("ftp://domain/document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("://domain/document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("", "", Protocol::HTTP, 300), std::invalid_argument);
	}
	
	BOOST_AUTO_TEST_CASE(url_without_slashes_invalid)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http/domain/document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("https:domain/document"), std::invalid_argument);
	}
	
	BOOST_AUTO_TEST_CASE(invalid_domain_or_they_absent)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http:///document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("https://:10/document"), std::invalid_argument);
	}
	
	BOOST_AUTO_TEST_CASE(port_equal_zero_or_max_unsigned_short_or_absent)
	{
		BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:/document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:65536/document"), std::invalid_argument);
		BOOST_REQUIRE_THROW(CHttpUrl("http://site.com:0/document"), std::invalid_argument);
	}
	
BOOST_AUTO_TEST_SUITE_END()