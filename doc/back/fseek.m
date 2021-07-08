
     NAME
          fseek, rewind, ftell - reposition a file pointer in a stream

     SYNTAX
          #include <stdio.h>

          int fseek (stream, offset, ptrname)
          FILE *stream;
          long offset;
          int ptrname;

          void rewind (stream)
          FILE *stream;

          long ftell (stream)
          FILE *stream;

     DESCRIPTION
          Fseek sets the position of the next input or output
          operation on the stream.  The new position is at the signed
          distance offset bytes from the beginning, from the current
          position, or from the end of the file, according as ptrname
          has the value 0, 1, or 2.

          Rewind(stream) is equivalent to fseek(stream, 0L, 0), except
          that no value is returned.

          Fseek and rewind undo any effects of ungetc().

          After fseek or rewind, the next operation on a file opened
          for update may be either input or output.

          Ftell returns the offset of the current byte relative to the
          beginning of the file associated with the named stream.

     SEE ALSO
          lseek.m, fopen.m, ungetc.m

     DIAGNOSTICS
          Fseek returns non-zero for improper seeks, otherwise zero.
          An improper seek can be, for example, an fseek done on a
          file that has not been opened via fopen; in particular,
          fseek may not be used on a terminal.

     WARNING
          Although on the UNIX system an offset returned by ftell is
          measured in bytes, and it is permissible to seek to
          positions relative to that offset, portability to non-UNIX
          systems requires that an offset be used by fseek directly.
          Arithmetic may not meaningfully be performed on such an
          offset, which is not necessarily measured in bytes.

          MPX blocked files can only be rewound or seeked to EOF.
          An error will be returned for these requested operations.

          (printed 07/30/92 - J B Systems)

