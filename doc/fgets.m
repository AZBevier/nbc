
     NAME
          gets, fgets - get a string from a stream

     SYNTAX
          #include <stdio.h>

          char *gets (s)
          char *s;

          char *fgets (s, n, stream)
          char *s;
          int n;
          FILE *stream;

     DESCRIPTION
          Gets reads characters from the standard input stream, stdin,
          into the array pointed to by s, until a new-line character
          is read or an end-of-file condition is encountered.  The
          new-line character is discarded and the string is terminated
          with a null character.

          Fgets reads characters from the stream into the array
          pointed to by s, until n-1 characters are read, or a new-
          line character is read and transferred to s, or an end-of-
          file condition is encountered.  The string is then
          terminated with a null character.

     SEE ALSO
          ferror.m, fopen.m, fread.m, getc.m, scanf.m

     DIAGNOSTICS
          If end-of-file is encountered and no characters have been
          read, no characters are transferred to s and a NULL pointer
          is returned.  If a read error occurs, such as trying to use
          these functions on a file that has not been opened for
          reading, a NULL pointer is returned.  Otherwise s is
          returned.

          (printed 07/30/92 - J B Systems)

