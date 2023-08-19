#include "pch.hpp"
#include "lametag.hpp"
#include <cstring>

const char *CLAMETag::m_szVBRInfo[10] =
	{
		"Unknown",
		"CBR",
		"ABR",
		"VBR1",
		"VBR2",
		"VBR3",
		"VBR4",
		"Reserved",
		"CBR2Pass",
		"ABR2Pass"};

CLAMETag *CLAMETag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd)
{
	// check for LAME Tag extension (always 120 bytes after XING ID)
	std::uint32_t dwOffset = dwBegin + 120;

	char *pBuffer = pStream->ReadBytes(9, dwOffset, false);
	if (std::memcmp(pBuffer, "LAME", 4) == 0)
		return new CLAMETag(pStream, bAppended, dwOffset);

	return nullptr;
}

CLAMETag::CLAMETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset) : CTag(pStream, "LAME", bAppended, dwOffset)
{
	char *pBuffer = pStream->ReadBytes(20, dwOffset, false);

	std::string strVersion = std::string((char *)pBuffer + 4, 4);
	m_fVersion = (float)std::atof(strVersion.c_str());

	// LAME prior to 3.90 writes only a 20 byte encoder string
	if (m_fVersion < 3.90)
	{
		m_bSimpleTag = true;
		m_strEncoder = std::string((char *)pBuffer, 20);
	}
	else
	{
		m_bSimpleTag = false;
		m_strEncoder = std::string((char *)pBuffer, 9);
		dwOffset += 9;

		// cut off last period
		if (m_strEncoder[8] == '.')
			m_strEncoder.erase(8);

		// version information
		char bInfoAndVBR = *(pStream->ReadBytes(1, dwOffset));

		// revision info in 4 MSB
		m_bRevision = bInfoAndVBR & 0xF0;
		// invalid value
		if (m_bRevision == 15)
			throw nullptr;

		// VBR info in 4 LSB
		m_bVBRInfo = bInfoAndVBR & 0x0F;

		// lowpass information
		m_dwLowpassFilterHz = *(pStream->ReadBytes(1, dwOffset)) * 100;

		// skip replay gain values
		dwOffset += 8;

		// skip encoding flags
		dwOffset += 1;

		// average bitrate for ABR, bitrate for CBR and minimal bitrat for VBR [in kbps]
		// 255 means 255 kbps or more
		m_bBitrate = *(pStream->ReadBytes(1, dwOffset));
	}
}

CLAMETag::~CLAMETag(void)
{
}

bool CLAMETag::IsVBR() const
{
	if (m_bVBRInfo >= 3 && m_bVBRInfo <= 6)
		return true;
	return false;
}

bool CLAMETag::IsABR() const
{
	if (m_bVBRInfo == 2 || m_bVBRInfo == 9)
		return true;
	return false;
}

bool CLAMETag::IsCBR() const
{
	if (m_bVBRInfo == 1 || m_bVBRInfo == 8)
		return true;
	return false;
}

const char *CLAMETag::GetVBRInfo() const
{
	if (m_bVBRInfo > 9)
		return m_szVBRInfo[0];

	return m_szVBRInfo[m_bVBRInfo];
}