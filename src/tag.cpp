#include "pch.hpp"
#include <tag.hpp>
#include "helper.hpp"

CTag::CTag(CMPAStream *pStream, const char *szName, bool bAppended, std::uint32_t dwOffset, std::uint32_t dwSize) : m_pStream(pStream), m_bAppended(bAppended), m_dwOffset(dwOffset), m_dwSize(dwSize)
{
	m_szName = MPAHelper::cloneCString(szName);
}

CTag::~CTag(void)
{
	free(m_szName);
}

void CTag::SetVersion(char bVersion1, char bVersion2, char bVersion3)
{
	// only values between 0 and 9 are displayed correctly
	m_fVersion = bVersion1;
	m_fVersion += bVersion2 * 0.1f;
	m_fVersion += bVersion3 * 0.01f;
}