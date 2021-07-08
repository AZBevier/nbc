
     NAME
          getc, getchar, fgetc, getw - get character or word from a
          stream

     SYNTAX
          #include <stdio.h>

          int getc (stream)
          FILE *stream;

          int getchar ()

          int fgetc (stream)
          FILE *stream;

          int getw (stream)
          FILE *stream;

     DESCRIPTION
          Getc returns the next character (i.e., byte) from the named
          input stream, as an integer.  It also moves the file
          pointer, if defined, ahead one character in stream.  Getchar
          is defined as getc(stdin).  Getc and getchar are macros.

          Fgetc behaves like getc, but is a function rather than a
          macro.  Fgetc runs more slowly than getc, but it takes less
          space per invocation and its name can be passed as an
          argument to a function.

          Getw returns the next word (i.e., integer) from the named
          input stream.  Getw increments the associated file pointer,
          if defined, to point to the next word.  The size of a word
          is the size of an integer and varies from machine to
          machine.  Getw assumes no special alignment in the file.

     SEE ALSO
          fclose.m, ferror.m, fopen.m, fread.m, gets.m,
          putc.m, scanf.m

     DIAGNOSTICS
          These functions return the constant EOF at end-of-file or
          upon an error.  Because EOF is a valid integer, ferror()
          should be used to detect getw errors.

     WARNING
          If the integer value returned by getc, getchar, or fgetc is
          stored into a character variable and then compared against
          the integer constant EOF, the comparison may never succeed,
          because sign-extension of a character on widening to integer
          is machine-dependent.

     SPECIAL CONSIDERATIONS
          Because it is implemented as a macro, getc treats
          incorrectly a stream argument with side effects.  In
          particular, getc(*f++) does not work sensibly.  Fgetc should
          be used instead.

          Because of possible differences in word length and byte
          ordering, files written using putw are machine-dependent,
          and may not be read using getw on a different processor.

          (printed 07/30/92 - J B Systems)

