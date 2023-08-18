#pragma once
#include "mpastream.hpp"

class CTag
{
public:
	std::uint32_t GetOffset() const { return m_dwOffset; };
	std::uint32_t GetEnd() const { return m_dwOffset + m_dwSize; };
	LPCTSTR GetName() const { return m_szName; };
	std::uint32_t GetSize() const { return m_dwSize; };
	float GetVersion() const { return m_fVersion; };

	virtual ~CTag(void);

protected:
	CMPAStream *m_pStream;

	CTag(CMPAStream *pStream, LPCTSTR szName, bool bAppended, std::uint32_t dwOffset = 0, std::uint32_t dwSize = 0);

	std::uint32_t m_dwOffset; // beginning of tag
	std::uint32_t m_dwSize;	  // size of tag
	bool m_bAppended;		  // true if at the end of file
	float m_fVersion;		  // format x.yz
	LPTSTR m_szName;		  // name of tag

	void SetVersion(BYTE bVersion1, BYTE bVersion2 = 0, BYTE bVersion3 = 0);
};
