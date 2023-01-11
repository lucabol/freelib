#include <stdio.h>
#include "os.h"

static int screen_putc(int c, FILE *stream)
{
    unsigned char ch = (unsigned char) c;
    fs_write(1, &ch, 1);
    return c;
}

static int keyboard_getc(FILE *stream)
{
  return 1;
}

static void screen_pre_output(FILE *stream)
{
    // read cursor position before output
}

static void screen_post_output(FILE *stream)
{
    // set cursor position after output
}

FILE scr_term;

void setup_terminal_io()
{
    // required if output is used
    scr_term.putc = screen_putc;

    // required if input is used
    scr_term.getc = keyboard_getc;

    // optional
    scr_term.pre_output = screen_pre_output;
    scr_term.post_output = screen_post_output;

    // required initial state if input
    // is used
    scr_term.ungetc_buf = -1;

    // pointer to custom data
    scr_term.user_ptr = NULL;

    // initialize needed streams
    stdin = stdout = &scr_term;
}
