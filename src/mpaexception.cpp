#include "pch.hpp"
#include <mpaexception.hpp>
#include <cstdio>

#ifdef _WIN32
#include <Windows.h>
#include <atlstr.h>
#endif

#include <cerrno>  //for errno
#include <clocale> //for setlocale
/// CMPAException: exception class
//////////////////////////////////////////////

using MPAHelper::cloneCString;
CMPAException::CMPAException(ErrorIDs ErrorID, const char *szFile, const char *szFunction, bool bGetLastError) : m_ErrorID(ErrorID), m_bGetLastError(bGetLastError), m_szErrorMsg(NULL)
{
	m_szFile = cloneCString(szFile);
	m_szFunction = cloneCString(szFunction);
}

// copy constructor (necessary for exception throwing without pointers)
CMPAException::CMPAException(const CMPAException &Source)
{
	m_ErrorID = Source.m_ErrorID;
	m_bGetLastError = Source.m_bGetLastError;
	m_szFile = cloneCString(Source.m_szFile);
	m_szFunction = cloneCString(Source.m_szFunction);
}

// destructor
CMPAException::~CMPAException()
{
	if (m_szFile)
		free(m_szFile);
	if (m_szFunction)
		free(m_szFunction);
	if (m_szErrorMsg)
		delete[] m_szErrorMsg;
}

// should be in resource file for multi language applications
const char *CMPAException::m_szErrors[CMPAException::NumIDs] =
	{
		"Can't open the file.",
		"Can't set file position.",
		"Can't read from file.",
		"No VBR Header found.",
		"Incomplete VBR Header.",
		"No frame found within tolerance range.",
		"No frame found before end of file was reached.",
		"Header corrupt",
		"Free Bitrate currently not supported",
		"Incompatible Header",
		"Corrupt Lyrics3 Tag"};

#define MAX_ERR_LENGTH 4096
void CMPAException::ShowError()
{
	const char *pErrorMsg = GetErrorDescription();
	// show error message
	//::MessageBox(NULL, pErrorMsg, "MPAFile Error", MB_OK);
	// no GUI outside of windows and mac. Log to stderr instead.
	std::fprintf(stderr, "MPAFile Error: {}", pErrorMsg);
}

const char *CMPAException::GetErrorDescription()
{
	if (!m_szErrorMsg)
	{
		m_szErrorMsg = new char[MAX_ERR_LENGTH];
		m_szErrorMsg[0] = '\0';
		char szHelp[MAX_ERR_LENGTH];

		// this is not buffer-overflow-proof!
		if (m_szFunction)
		{
			snprintf(szHelp, MAX_ERR_LENGTH, "%s: ", m_szFunction);
			strncat(m_szErrorMsg, szHelp, MAX_ERR_LENGTH);
		}
		if (m_szFile)
		{
			snprintf(szHelp, MAX_ERR_LENGTH, "'%s'\n", m_szFile);
			strncat(m_szErrorMsg, szHelp, MAX_ERR_LENGTH);
		}
		strncat(m_szErrorMsg, m_szErrors[m_ErrorID], MAX_ERR_LENGTH);

		if (m_bGetLastError)
		{
			// get error message of last system error id
#ifdef _WIN32
			void *pMsgBuf;
			if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
							  NULL,
							  GetLastError(),
							  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
							  (char *)&pMsgBuf,
							  0,
							  NULL))
			{
				_tcscat_s(m_szErrorMsg, MAX_ERR_LENGTH, "\n");
				_tcscat_s(m_szErrorMsg, MAX_ERR_LENGTH, (const char *)pMsgBuf);
				LocalFree(pMsgBuf);
			}
#else
			setlocale(LC_MESSAGES, "C");
			strncat(m_szErrorMsg, "\n", MAX_ERR_LENGTH);
			char *strErrorMsg = std::strerror(errno);
			strncat(m_szErrorMsg, strErrorMsg, MAX_ERR_LENGTH);
#endif
		}

		// make sure string is null-terminated
		m_szErrorMsg[MAX_ERR_LENGTH - 1] = '\0';
	}
	return m_szErrorMsg;
}