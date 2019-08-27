
     NAME
          puts, fputs - put a string on a stream

     SYNTAX
          #include <stdio.h>

          int puts (s)
          char *s;

          int fputs (s, stream)
          char *s;
          FILE *stream;

     DESCRIPTION
          Puts writes the null-terminated string pointed to by s,
          followed by a new-line character, to the standard output
          stream stdout.

          Fputs writes the null-terminated string pointed to by s to
          the named output stream.

          Neither function writes the terminating null character.

     DIAGNOSTICS
          Both routines return EOF on error. This will happen if the
          routines try to write on a file that has not been opened for
          writing.  If no error occurs, the last character copied is
          returned.

     SEE ALSO
          ferror.m, fopen.m, fread.m, printf.m, putc.m

     NOTES
          Puts appends a new-line character while fputs does not.

          (printed 07/30/92 - J B Systems)

