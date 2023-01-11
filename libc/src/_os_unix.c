#ifdef __unix__

#include <asm/unistd.h>
#include "os.h"

#if defined(__x86_64__)
/* Syscalls for x86_64 :
 *   - registers are 64-bit
 *   - syscall number is passed in rax
 *   - arguments are in rdi, rsi, rdx, r10, r8, r9 respectively
 *   - the system call is performed by calling the syscall instruction
 *   - syscall return comes in rax
 *   - rcx and r8..r11 may be clobbered, others are preserved.
 *   - the arguments are cast to long and assigned into the target registers
 *     which are then simply passed as registers to the asm code, so that we
 *     don't have to experience issues with register constraints.
 *   - the syscall number is always specified last in order to allow to force
 *     some registers before (gcc refuses a %-register at the last position).
 */

#define my_syscall0(num)                                                      \
         long _ret;                                                            \
         register long _num  asm("rax") = (num);                               \
         \
         asm volatile (                                                        \
                         "syscall\n"                                                   \
                         : "=a" (_ret)                                                 \
                         : "0"(_num)                                                   \
                         : "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
                         )

#define my_syscall1(num, arg1)                                                \
         long _ret;                                                            \
         register long _num  asm("rax") = (num);                               \
         register long _arg1 asm("rdi") = (long)(arg1);                        \
         \
         asm volatile (                                                        \
                         "syscall\n"                                                   \
                         : "=a" (_ret)                                                 \
                         : "r"(_arg1),                                                 \
                         "0"(_num)                                                   \
                         : "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
                         )

#define my_syscall2(num, arg1, arg2)                                          \
         long _ret;                                                            \
         register long _num  asm("rax") = (num);                               \
         register long _arg1 asm("rdi") = (long)(arg1);                        \
         register long _arg2 asm("rsi") = (long)(arg2);                        \
         \
         asm volatile (                                                        \
                         "syscall\n"                                                   \
                         : "=a" (_ret)                                                 \
                         : "r"(_arg1), "r"(_arg2),                                     \
                         "0"(_num)                                                   \
                         : "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
                         )

#define my_syscall3(num, arg1, arg2, arg3)                                    \
         long _ret;                                                            \
         register long _num  asm("rax") = (num);                               \
         register long _arg1 asm("rdi") = (long)(arg1);                        \
         register long _arg2 asm("rsi") = (long)(arg2);                        \
         register long _arg3 asm("rdx") = (long)(arg3);                        \
         \
         asm volatile (                                                        \
                         "syscall\n"                                                   \
                         : "=a" (_ret)                                                 \
                         : "r"(_arg1), "r"(_arg2), "r"(_arg3),                         \
                         "0"(_num)                                                   \
                         : "rcx", "r8", "r9", "r10", "r11", "memory", "cc"             \
                         )

#else
#error "Just linux x86_64 and windows are supported. Paste relevant nolibc.h sections for more archs"
#endif

typedef   signed long       ssize_t;

noreturn void fs_exit(int status) {
  my_syscall1(__NR_exit, status & 255);
  while(1); /* making the function not returning */
}


ssize_t fs_write(FD fd, const void *buf, size_t count)
{
    my_syscall3(__NR_write, fd, buf, count);
    return _ret;
}

#endif
