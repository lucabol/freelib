#ifndef OS_H
#define OS_H

#include <stddef.h>
#include <stdnoreturn.h>

/* Nice-to-have common abbreviations */
typedef ptrdiff_t FD;

#define FIN   0
#define FOUT  1
#define FERR  2

/* Exported functions */
void fs_exit(int status);
long fs_write(FD fd, const void *buf, size_t count);

#endif
