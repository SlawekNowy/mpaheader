#pragma once
#include "mpaframe.hpp"
#include "vbrheader.hpp"
#include "lametag.hpp"

class CXINGHeader : public CVBRHeader
{
public:
	static CXINGHeader *FindHeader(const CMPAFrame *pFrame);

	CXINGHeader(const CMPAFrame *pFrame, std::uint32_t dwOffset);
	virtual ~CXINGHeader(void);

	virtual std::uint32_t SeekPosition(float &fPercent) const;

	CLAMETag *m_pLAMETag;
};
