#include <cstddef>
#include "libarchive.h"

archive_t open_archive(const char * path, int mode, archive_error_t * err)
{
    *err = ARCHIVE_SUCCESS;

    return nullptr;
}

archive_error_t close_archive(archive_t archive)
{
    (void)archive;
    return ARCHIVE_SUCCESS;
}

archive_entry_t archive_get_entry(archive_t archive, int entry_idx, archive_error_t * err)
{
    return NULL;
}

archive_error_t archive_extract_entry(archive_t archive, archive_entry_t entry, const char * target_path)
{
    return ARCHIVE_SUCCESS;
}

int archive_get_entry_count(archive_t archive, archive_error_t * err)
{
    return 0;
}
