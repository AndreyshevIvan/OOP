#include "stdafx.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

using namespace std;

CHttpUrl::CHttpUrl(string const& url)
try
{
	size_t pos = 0;
	ParseProtocol(url, pos);
	ParseDomain(url, pos);
	
	if (url[pos] == ':')
	{
		pos++;
		ParsePort(url, pos);
	}
	ParseDocument(url, pos);

}
catch (CUrlParsingError const& e)
{
	std::cout << e.what();
}

void CHttpUrl::ParseProtocol(string const& url, size_t& pos)
{
	string protocolStr = "";
	while(pos != url.size())
	{
		if (!(url[pos] > 'a' && url[pos] < 'z') && !(url[pos] > 'A' && url[pos] < 'Z'))
		{
			break;
		}
		else
		{
			protocolStr += url[pos];
		}
		pos++;
	}

	protocolStr = boost::algorithm::to_lower_copy(protocolStr);
	if (protocolStr == "http")
	{
		m_port = 80;
		m_protocol = Protocol::HTTP;
	}
	else if (protocolStr == "https")
	{
		m_port = 443;
		m_protocol = Protocol::HTTPS;
	}
	else
	{
		throw CUrlParsingError("Invalid protocol. Usage http or https\n");
	}

	if (url.find("://") == pos)
	{
		pos += 3;
	}
	else
	{
		throw CUrlParsingError("Invalid URL. Needed :// after protocol\n");
	}
}

void CHttpUrl::ParseDomain(string const& url, size_t& pos)
{
	while (pos != url.size())
	{
		if (url[pos] == ':' || url[pos] == '/')
		{
			break;
		}
		else
		{
			m_domain += url[pos];
		}
		pos++;
	}

	if (m_domain == "")
	{
		throw CUrlParsingError("Invalid domain\n");
	}

}

void CHttpUrl::ParsePort(string const& url, size_t& pos)
{
	if (url[pos] > '9' || url[pos] < '0')
	{
		throw CUrlParsingError("Unknown port\n");
	}
	m_port = 0;
	unsigned short digit = 0;
	while (url[pos] <= '9' && url[pos] >= '0')
	{
		digit = (int)url[pos] - '0';
		if ((USHRT_MAX / 10) - digit > m_port)
		{
			m_port = m_port * 10 + digit;
		}
		else
		{
			throw CUrlParsingError("Port longer than it possible\n");
		}
		pos++;
	}
}

void CHttpUrl::ParseDocument(std::string const& url, size_t& pos)
{
	string documentStr = "";
	if (url[pos] != '/')
	{
		documentStr += '/';
	}
	while (pos != url.size())
	{
		documentStr += url[pos];
		pos++;
	}
	m_document = documentStr;
}

CHttpUrl::CHttpUrl(string const& domain, string const& document, Protocol protocol, unsigned short port)
	:m_domain(domain)
	,m_document(document)
	,m_protocol(protocol)
	,m_port(port)
{
	if (domain.empty())
	{
		throw CUrlParsingError("Empty domain\n");
	}

	size_t pos = 0;
	ParseDocument(m_document, pos);
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
