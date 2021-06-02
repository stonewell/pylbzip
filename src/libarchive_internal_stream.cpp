#include <cstddef>
#include <stdio.h>

#include "libarchive.h"
#include "libarchive_internal_stream.h"

ArchiveInStream::~ArchiveInStream()
{
    if (m_pFile)
        fclose(m_pFile);
}

bool ArchiveInStream::Load(const std::string & path)
{
    m_strFileName = path;
    m_pFile = fopen(path.c_str(), "rb");
    if (m_pFile) {
        fseek(m_pFile, 0, SEEK_END);
        m_nFileSize = ftell(m_pFile);
        fseek(m_pFile, 0, SEEK_SET);

        return true;
    }
    else {
        return false;
    }
}

int ArchiveInStream::Read(void *data, unsigned int size, unsigned int *processedSize)
{
    if (!m_pFile)
        return 1;

    int count = fread(data, 1, size, m_pFile);

    if (count >= 0) {
        if (processedSize != NULL)
            *processedSize = count;

        return 0;
    }

    return 1;
}

int ArchiveInStream::Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition)
{
    if (!m_pFile)
        return 1;

    int result = fseek(m_pFile, (long)offset, seekOrigin);

    if (!result) {
        if (newPosition)
            *newPosition = ftell(m_pFile);

        return 0;
    }

    return result;
}

int ArchiveInStream::GetSize(unsigned __int64 * size)
{
    if (size)
        *size = m_nFileSize;
    return 0;
}

ArchiveOutStream::~ArchiveOutStream()
{
    if (m_pFile)
        fclose(m_pFile);
}

bool ArchiveOutStream::Init(const std::string & path)
{
    m_pFile = fopen(path.c_str(), "wb");

    return m_pFile != nullptr;
}

int ArchiveOutStream::Write(const void *data, unsigned int size, unsigned int *processedSize)
{
    int count = fwrite(data, 1, size, m_pFile);

    if (count >= 0)
    {
        if (processedSize != NULL)
            *processedSize = count;

        return 0;
    }

    return 1;
}

int ArchiveOutStream::Seek(__int64 offset, unsigned int seekOrigin, unsigned __int64 *newPosition)
{
    int result = fseek(m_pFile, (long)offset, seekOrigin);

    if (!result)
    {
        if (newPosition)
            *newPosition = ftell(m_pFile);

        return 0;
    }

    return result;
}
