#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const& url)
	:m_url(url)
{
	try
	{
		smatch matches;
		const regex urlRegularExpression(
			"^(http?|https)"
			"(://)"
			"([0-9a-z\\.-]+)"
			"(:?([0-9]+))"
			"?(/(.*))?$"
		);

		if (!std::regex_match(url, matches, urlRegularExpression))
		{
			throw CUrlParsingError("Invalid URL. Usage: <protocol>://<domain>:<port>/<document>\n");
		}
		(matches[1].str() == "http") ? m_protocol = Protocol::HTTP : m_protocol = Protocol::HTTPS;
		m_domain = matches[3].str();
		m_document = matches[6];
	}
	catch (CUrlParsingError const& e)
	{
		throw CUrlParsingError(e);
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	:m_domain(domain)
	,m_document(document)
	,m_protocol(protocol)
	,m_port(port)
{

}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ToString()
{

	std::string result;
	std::string protocol;
	std::string port;

	(GetProtocol() == Protocol::HTTP) ? protocol = "http" : protocol = "https";
	port = to_string(GetPort());

	result = "URL: " + GetURL() + "\n";
	result += "\tProtocol: " + protocol + "\n";
	result += "\tDomain: " + GetDomain() + "\n";
	result += "\tPort: " + port + "\n";
	result += "\tDocument: " + GetDocument() + "\n";

	return result;
}
