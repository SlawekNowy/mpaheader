#include "mpacstdfile.hpp"
#include <string>
#include <cstdio>

CMPACSTDFile::CMPACSTDFile(std::string filename) : fileSize(-1)
{
    filePtr = fopen(filename.c_str(), "rb");
}

CMPACSTDFile::~CMPACSTDFile()
{
    fclose(filePtr);
}

size_t CMPACSTDFile::Read(void *data, size_t size)
{

    return fread(data, sizeof(char), size, filePtr);
}

void CMPACSTDFile::Seek(size_t seekOff, Whence dir)
{
    fseek(filePtr, seekOff, (char)dir);
}

size_t CMPACSTDFile::GetSize()
{
    // return size_t();
    if (fileSize == -1)
    {
        size_t oldPos = ftell(filePtr);
        fseek(filePtr, 0, SEEK_END);
        fileSize = ftell(filePtr);
        fseek(filePtr, oldPos, SEEK_SET);
    }
    return fileSize;
}
