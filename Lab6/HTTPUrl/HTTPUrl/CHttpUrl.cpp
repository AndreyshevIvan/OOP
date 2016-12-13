#include "stdafx.h"
#include "CHttpUrl.h"

using namespace std;

CHttpUrl::CHttpUrl(std::string const& url)
	:m_url(url)
{

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
