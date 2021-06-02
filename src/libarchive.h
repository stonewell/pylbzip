#pragma once

#ifdef __cplusplus
extern "C" {
#if 0
} /* fix autoindent */
#endif
#endif

typedef int archive_error_t;
typedef void * archive_entry_t;

typedef void * archive_t;

#define ARCHIVE_RDONLY 0

#define ARCHIVE_SUCCESS 0
#define ERR_ARCHIVE_OPEN_FAILED -1
#define ERR_ARCHIVE_7ZIPLIB_INIT_FAILED -2
#define ERR_ARCHIVE_GET_ENTRY_FAILED -3

archive_t open_archive(const char * path, int mode, archive_error_t * err);
archive_error_t close_archive(archive_t archive);

int archive_get_entry_count(archive_t archive, archive_error_t * err);
archive_entry_t archive_open_entry(archive_t archive, int entry_idx, archive_error_t * err);
archive_error_t archive_extract_entry(archive_t archive, archive_entry_t entry, const char * target_path);

const wchar_t * entry_get_fullpath(archive_entry_t entry, archive_error_t * err);
archive_error_t close_entry(archive_entry_t entry);

#ifdef __cplusplus
#if 0
{ /* fix autoindent */
#endif
}
#endif
