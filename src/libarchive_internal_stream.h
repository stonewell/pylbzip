#pragma once

#include "lib7zip.h"

class ArchiveInStream : public C7ZipInStream
{
private:
	FILE * m_pFile = nullptr;
	std::string m_strFileName{};
	int m_nFileSize = 0;

public:
	ArchiveInStream() = default;
	virtual ~ArchiveInStream();

public:
    bool Load(const std::string & path);

    virtual wstring GetExt() const
	{
		return L"";
	}

	virtual int Read(void *data, unsigned int size, unsigned int *processedSize);

	virtual int Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition);

	virtual int GetSize(unsigned __int64 * size);
};

class ArchiveOutStream : public C7ZipOutStream
{
private:
	FILE * m_pFile;
public:
	ArchiveOutStream() = default;
    virtual ~ArchiveOutStream();

public:
    bool Init(const std::string & path);
	virtual int Write(const void *data, unsigned int size, unsigned int *processedSize);
    virtual int Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition);
    virtual int SetSize(unsigned __int64 size) { return 0; }
};
