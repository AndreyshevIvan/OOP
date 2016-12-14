#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

enum Protocol
{
	HTTP,
	HTTPS,
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = HTTP, unsigned short port = 80);
	
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

	std::string Info();
	std::string GetStringURL();
	std::string ParseUrl(std::string const& url);
	Protocol ParseProtocol(std::string protocol);

private:
	std::string m_url;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

};