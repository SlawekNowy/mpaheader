
// exception class

#ifndef MPAEXCEPTION_BF58A528_6C6F_41FB_8986_C9EE61D1BB3F
#define MPAEXCEPTION_BF58A528_6C6F_41FB_8986_C9EE61D1BB3F
class CMPAException
{
public:
	enum ErrorIDs
	{
		ErrOpenFile,
		ErrSetPosition,
		ErrReadFile,
		NoVBRHeader,
		IncompleteVBRHeader,
		NoFrameInTolerance,
		EndOfFile,
		HeaderCorrupt,
		FreeBitrate,
		IncompatibleHeader,
		CorruptLyricsTag,
		NumIDs // this specifies the total number of possible IDs
	};

	CMPAException(ErrorIDs ErrorID, const char *szFile = NULL, const char *szFunction = NULL, bool bGetLastError = false);
	// copy constructor (necessary because of LPSTR members)
	CMPAException(const CMPAException &Source);
	virtual ~CMPAException(void);

	ErrorIDs GetErrorID() const { return m_ErrorID; };
	const char *GetErrorDescription();
	void ShowError();

private:
	ErrorIDs m_ErrorID;
	bool m_bGetLastError;
	char *m_szFunction;
	char *m_szFile;
	char *m_szErrorMsg;

	static const char *m_szErrors[CMPAException::NumIDs];
};

#endif /* MPAEXCEPTION_BF58A528_6C6F_41FB_8986_C9EE61D1BB3F */
