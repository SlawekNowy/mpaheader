#pragma once
#include "mpaexception.hpp"
#include "mpafilestream.hpp"
#include "mpaframe.hpp"
#include "tags.hpp"

class CMPAFile
{
public:
	CMPAFile(LPCTSTR szFile);
	CMPAFile(CMPAStream *pStream);
	~CMPAFile(void);

	std::uint32_t GetBegin() const { return m_pTags->GetBegin(); };
	std::uint32_t GetEnd() const { return m_pTags->GetEnd(); };
	std::uint32_t GetFileSize() const { return (GetEnd() - GetBegin()); };
	std::uint32_t GetLengthSec() const { return (GetFileSize() / m_dwBytesPerSec); };

	enum GetType
	{
		First,
		Last,
		Next,
		Prev,
		Resync
	};

	CMPAFrame *GetFrame(GetType Type, CMPAFrame *pFrame = NULL, bool bDeleteOldFrame = true, std::uint32_t dwOffset = 0);

private:
	void CalcBytesPerSec();

	CMPAStream *m_pStream;
	std::uint32_t m_dwBytesPerSec;

public:
	CTags *m_pTags;			  // contain list of present tags
	CMPAFrame *m_pFirstFrame; // always first frame
	CVBRHeader *m_pVBRHeader; // XING or VBRI or NULL
};
