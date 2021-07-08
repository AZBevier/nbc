
     NAME
          ferror, feof, clearerr, fileno - stream status inquiries

     SYNTAX
          #include <stdio.h>

          int ferror (stream)
          FILE *stream;

          int feof (stream)
          FILE *stream;

          void clearerr (stream)
          FILE *stream;

          int fileno (stream)
          FILE *stream;

     DESCRIPTION
          Ferror returns non-zero when an I/O error has previously
          occurred reading from or writing to the named stream,
          otherwise zero.

          Feof returns non-zero when EOF has previously been detected
          reading the named input stream, otherwise zero.

          Clearerr resets the error indicator and EOF indicator to
          zero on the named stream.

          Fileno returns the integer file descriptor associated with
          the named stream (refer to open.m).

     NOTE
          All these functions are implemented as macros; they cannot
          be declared or redeclared.

     SEE ALSO
          open.m, fopen.m

          (printed 07/30/92 - J B Systems)

