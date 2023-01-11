#ifdef __MINGW32__

#define WIN32_LEAN_AND_MEAN 1
// See http://utf8everywhere.org/ for the general idea of managing text as utf-8 on windows
#define UNICODE
#define _UNICODE
#include <windows.h>
#include <shellapi.h>

#include "os.h"

noreturn void fs_exit(int status)
{
    ExitProcess(status);
    while(1); // Making it noreturn
}

#define RET_BOOL_TO_INT(result) if(result) return 0; else return -1

long fs_write(FD fd, const void *buf, size_t count)
{
    DWORD written;
    HANDLE out;
    if(fd == FOUT) { // Writing to stdout, need to set the console to utf8
        out = GetStdHandle(STD_OUTPUT_HANDLE);
    } else {
        out = (HANDLE)fd;
    }
    BOOL result = WriteFile(out, buf, count, &written, NULL);
    RET_BOOL_TO_INT(result);
}

#endif
