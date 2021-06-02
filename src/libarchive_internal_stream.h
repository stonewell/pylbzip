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
