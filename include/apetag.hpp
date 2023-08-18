#ifndef __MPAHEADER_APETAG_HPP__
#define __MPAHEADER_APETAG_HPP__
#pragma once
#include "tag.hpp"
#include <cstdint>

class CAPETag : public CTag
{
public:
	static CAPETag *CAPETag::FindTag(CMPAStream *pStream, bool bAppended, std::uint32_t dwBegin, std::uint32_t dwEnd);
	~CAPETag(void);

private:
	CAPETag(CMPAStream *pStream, bool bAppended, std::uint32_t dwOffset);
};
#endif