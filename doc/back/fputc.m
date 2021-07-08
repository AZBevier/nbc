
     NAME
          putc, putchar, fputc, putw - put character or word on a
          stream

     SYNTAX
          #include <stdio.h>

          int putc (c, stream)
          int c;
          FILE *stream;

          int putchar (c)
          int c;

          int fputc (c, stream)
          int c;
          FILE *stream;

          int putw (w, stream)
          int w;
          FILE *stream;

     DESCRIPTION
          Putc writes the character c onto the output stream (at the
          position where the file pointer, if defined, is pointing).
          Putchar(c) is defined as putc(c, stdout).  Putc and putchar
          are macros.

          Fputc behaves like putc, but is a function rather than a
          macro.  Fputc runs more slowly than putc, but it takes less
          space per invocation and its name can be passed as an
          argument to a function.

          Putw writes the word (i.e. integer) w to the output stream
          (at the position at which the file pointer, if defined, is
          pointing).  The size of a word is the size of an integer and
          varies from machine to machine.  Putw neither assumes nor
          causes special alignment in the file.

          Output streams, with the exception of the standard error
          stream stderr, are by default buffered if the output refers
          to a file and line-buffered if the output refers to a
          terminal.  The standard error output stream stderr is by
          default unbuffered, but use of freopen (see fopen.m) will
          cause it to become buffered or line-buffered.  When an
          output stream is unbuffered, information is queued for
          writing on the destination file or terminal as soon as
          written; when it is buffered, many characters are saved up
          and written as a block.  When it is line-buffered, each line
          of output is queued for writing on the destination terminal
          as soon as the line is completed (that is, as soon as a
          new-line character is written or terminal input is
          requested).  Setbuf() may be used to change the stream's
          buffering strategy.

     SEE ALSO
          fclose.m, ferror.m, fopen.m, fread.m, printf.m,
          puts.m, setbuf.m

     DIAGNOSTICS
          On success, these functions each return the value they have
          written.  On failure, they return the constant EOF.  This
          will occur if the file stream is not open for writing or if
          the output file cannot be grown.  Because EOF is a valid
          integer, ferror(3S) should be used to detect putw errors.

     SPECIAL CONSIDERATIONS
          Because it is implemented as a macro, putc incorrectly
          treats a stream argument with side effects.  In particular,
          putc(c, *f++); doesn't work sensibly.  Fputc should be used
          instead.

          Because of possible differences in word length and byte
          ordering, files written using putw are machine-dependent,
          and may not be read using getw on a different processor.

          (printed 07/30/92 - J B Systems)

