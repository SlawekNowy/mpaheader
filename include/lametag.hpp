#pragma once
#include "tag.hpp"

class CLAMETag : public CTag
{
public:
	static CLAMETag *CLAMETag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CLAMETag(void);

	CString m_strEncoder;
	std::uint32_t m_dwLowpassFilterHz;
	BYTE m_bBitrate; // in kbps
	BYTE m_bRevision;

	bool IsVBR() const;
	bool IsABR() const;
	bool IsCBR() const;
	LPCTSTR GetVBRInfo() const;
	bool IsSimpleTag() const { return m_bSimpleTag; };

private:
	CLAMETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset);

	BYTE m_bVBRInfo;
	bool m_bSimpleTag;
	static LPCTSTR m_szVBRInfo[10];
};
