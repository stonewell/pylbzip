#include <cstddef>
#include <memory>

#include "libarchive.h"
#include "libarchive_internal.h"

static
C7ZipLibrary g_7ziplib{};

class GlobalLibraryInitializer
{
public:
    GlobalLibraryInitializer()
    {
        g_7ziplib.Initialize();
    }

};

static
GlobalLibraryInitializer g_LibInitializer{};

archive_t open_archive(const char * path, int mode, archive_error_t * err)
{
    if (!g_7ziplib.IsInitialized()) {
        *err = ERR_ARCHIVE_7ZIPLIB_INIT_FAILED;
        return nullptr;
    }

    auto archive = std::make_unique<archive_s>();

    if (!archive->in_stream.Load(path)) {
        *err = ERR_ARCHIVE_OPEN_FAILED;
        return nullptr;
    }

    if (g_7ziplib.OpenArchive(&archive->in_stream,
                              &archive->pArchive,
                              true)) {
        *err = ARCHIVE_SUCCESS;

        return archive.release();
    } else {
        *err = ERR_ARCHIVE_OPEN_FAILED;
        return nullptr;
    }
}

archive_error_t close_archive(archive_t archive)
{
    std::unique_ptr<archive_s> archive_ptr{reinterpret_cast<archive_s*>(archive)};
    return ARCHIVE_SUCCESS;
}

archive_entry_t archive_open_entry(archive_t archive, int entry_idx, archive_error_t * err)
{
    auto archive_ptr = reinterpret_cast<archive_s*>(archive);

    auto entry_ptr = std::make_unique<archive_entry_s>();

    if (!archive_ptr->pArchive->GetItemInfo(entry_idx, &entry_ptr->pArchiveItem)) {
        *err = ERR_ARCHIVE_GET_ENTRY_FAILED;
        return nullptr;
    }

    *err = ARCHIVE_SUCCESS;
    return entry_ptr.release();
}

archive_error_t archive_extract_entry(archive_t archive, archive_entry_t entry, const char * target_path)
{
    return ARCHIVE_SUCCESS;
}

int archive_get_entry_count(archive_t archive, archive_error_t * err)
{
    auto archive_ptr = reinterpret_cast<archive_s*>(archive);

    unsigned int numItems = 0;

    archive_ptr->pArchive->GetItemCount(&numItems);

    *err = ARCHIVE_SUCCESS;
    return numItems;
}

const wchar_t * entry_get_fullpath(archive_entry_t entry, archive_error_t * err)
{
    *err = ARCHIVE_SUCCESS;
    auto entry_ptr = reinterpret_cast<archive_entry_s *>(entry);

    entry_ptr->full_path = entry_ptr->pArchiveItem->GetFullPath();

    return entry_ptr->full_path.c_str();
}

archive_error_t close_entry(archive_entry_t entry)
{
    std::unique_ptr<archive_entry_s> entry_ptr{reinterpret_cast<archive_entry_s*>(entry)};

    return ARCHIVE_SUCCESS;
}
