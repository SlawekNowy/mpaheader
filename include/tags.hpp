#pragma once

#define NUMBER_OF_ELEMENTS(X) (sizeof X / sizeof X[0])

#include <vector>

#include <cstdint>
#include "mpastream.hpp"
#include "tag.hpp"

class CTags
{
public:
	CTags(CMPAStream *pStream);
	~CTags(void);

	CTag *GetNextTag(unsigned int &nIndex) const;
	template <class TagClass>
	bool FindTag(TagClass *&pTag) const;

	// get begin offset after prepended tags
	std::uint32_t GetBegin() const { return m_dwBegin; };
	// get end offset before appended tags
	std::uint32_t GetEnd() const { return m_dwEnd; };

private:
	bool FindAppendedTag(CMPAStream *pStream);
	bool FindPrependedTag(CMPAStream *pStream);

	// definition of function pointer type
	typedef CTag *(*FindTagFunctionPtr)(CMPAStream *, bool, std::uint32_t, std::uint32_t);
	bool FindTag(FindTagFunctionPtr pFindTag, CMPAStream *pStream, bool bAppended);

	std::vector<CTag *> m_Tags;
	std::uint32_t m_dwBegin, m_dwEnd;
	static const FindTagFunctionPtr m_appendedTagFactories[];
	static const FindTagFunctionPtr m_prependedTagFactories[];
};

// you need to compile with runtime information to use this method
template <class TagClass>
bool CTags::FindTag(TagClass *&pTag) const
{
	for (unsigned int nIndex = 0; nIndex < m_Tags.size(); nIndex++)
	{
		pTag = dynamic_cast<TagClass *>(m_Tags[nIndex]);
		if (pTag)
			return true;
	}
	return false;
}
