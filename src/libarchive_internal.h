#pragma once

#include <memory>
#include <forward_list>

#include "lib7zip.h"
#include "libarchive_internal_stream.h"

struct archive_entry_s {
    C7ZipArchiveItem * pArchiveItem = NULL;
    std::wstring full_path;

    ~archive_entry_s() {
    }
};

struct archive_s {
    ArchiveInStream in_stream;
    C7ZipArchive * pArchive = NULL;

    ~archive_s() {
        if (pArchive)
            delete pArchive;
    }
};

