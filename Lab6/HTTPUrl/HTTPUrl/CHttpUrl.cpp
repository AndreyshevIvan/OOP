#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
try
	:m_url(ParseUrl(url))
{}
catch (CUrlParsingError const& e)
{
	throw CUrlParsingError(e);
}

std::string CHttpUrl::ParseUrl(string const& url)
{
	smatch matches;
	std::regex urlRegularExpression("^([a-zA-Z]{4}|[a-zA-Z]{5})://([0-9a-z\\.-]+)(:?([0-9]+))?(/(.*))?$");

	if (!std::regex_match(url, matches, urlRegularExpression))
	{
		throw CUrlParsingError("Invalid URL. Usage: <protocol>://<domain>:<port>/<document>\n");
	}

	m_protocol = ParseProtocol(matches[1].str());
	string test(matches[2]);
	m_domain = test;
	cout << "test";

	string port = matches[4].str();
	if (port != "")
	{
		m_port = static_cast<unsigned short>(stoi(port));
	}
	m_document = matches[6].str();

	return GetStringURL();
}

Protocol CHttpUrl::ParseProtocol(string protocol)
{
	Protocol newProtocol = Protocol::HTTP;
	protocol = boost::algorithm::to_lower_copy(protocol);
	if (protocol == "https" || protocol == "http")
	{
		if (protocol == "http")
		{
			newProtocol = Protocol::HTTP;
			m_port = 80;
		}
		else
		{
			newProtocol = Protocol::HTTPS;
			m_port = 443;
		}
		return newProtocol;
	}
	else
	{
		throw CUrlParsingError("Invalid protocol. Usage http or https\n");
	}
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
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

std::string CHttpUrl::GetStringURL()
{
	string url;
	string protocol;
	string port;

	(GetProtocol() == Protocol::HTTP) ? protocol = "http" : protocol = "https";
	port = to_string(GetPort());

	url = protocol + "://" + GetDomain() + GetDocument() + "\n";

	return url;
}

std::string CHttpUrl::Info()
{
	std::string result;
	std::string protocol;
	std::string port;

	(GetProtocol() == Protocol::HTTP) ? protocol = "http" : protocol = "https";
	port = to_string(GetPort());

	result = "URL: " + GetStringURL();
	result += "\tProtocol: " + protocol + "\n";
	result += "\tDomain: " + GetDomain() + "\n";
	result += "\tPort: " + port + "\n";
	result += "\tDocument: " + GetDocument() + "\n";

	return result;
}
