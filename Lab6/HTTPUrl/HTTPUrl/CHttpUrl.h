#pragma once
#include "stdafx.h"
#include "CUrlParsingError.h"

enum Protocol
{
	HTTP = 80,
	HTTPS = 443,
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document
	);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol
	);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port
	);
	
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	void ParseProtocol(std::string const& protocol, size_t& pos);
	void ParseDomain(std::string const& domain, size_t& pos);
	void ParsePort(std::string const& url, size_t& pos);
	void ParseDocument(std::string const& url, size_t& pos);

	std::string m_url;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

};

std::string Info(CHttpUrl const& url);