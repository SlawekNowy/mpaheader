#ifndef __MPACSTDFILE_HPP__
#define __MPACSTDFILE_HPP__

#include "mpafilestream.hpp"

// Example implementation of CMPAIFile, based on C's fopen.
struct DLLMPAH CMPACSTDFile : CMPAIFile
{
    CMPACSTDFile(std::string);
    ~CMPACSTDFile();
    size_t Read(void *, size_t) override;
    void Seek(size_t, Whence) override;
    size_t GetSize() override;

private:
    FILE *filePtr;
    size_t fileSize; // cached file size. File is opened as read-only, so that won't change.
};

#endif /* __MPACSTDFILE_HPP__ */
