
     NAME
          setbuf, setvbuf - assign buffering to a stream

     SYNTAX
          #include <stdio.h>

          void setbuf (stream, buf)
          FILE *stream;
          char *buf;

          int setvbuf (stream, buf, type, size)
          FILE *stream;
          char *buf;
          int type, size;

     DESCRIPTION
          Setbuf may be used after a stream has been opened but before
          it is read or written.  It causes the array pointed to by
          buf to be used instead of an automatically allocated buffer.
          If buf is the NULL pointer input/output will be completely
          unbuffered.

          A constant BUFSIZ, defined in the <stdio.h> header file,
          tells how big an array is needed:

               char buf[BUFSIZ];

          Setvbuf may be used after a stream has been opened but
          before it is read or written.  Type determines how stream
          will be buffered.  Legal values for type (defined in
          stdio.h) are:

          _IOFBF  causes input/output to be fully buffered.

          _IOLBF  causes output to be line buffered; the buffer will
                  be flushed when a newline is written, the buffer is
                  full, or input is requested.

          _IONBF  causes input/output to be completely unbuffered.

          If buf is not the NULL pointer, the array it points to will
          be used for buffering, instead of an automatically allocated
          buffer.  Size specifies the size of the buffer to be used.
          The constant BUFSIZ in <stdio.h> is suggested as a good
          buffer size.  If input/output is unbuffered, buf and size
          are ignored.

          By default, output to a terminal is line buffered and all
          other input/output is fully buffered.

     SEE ALSO
          fopen.m, getc.m, malloc.m, putc.m, stdio.m

     DIAGNOSTICS
          If an illegal value for type or size is provided, setvbuf
          returns a non-zero value. Otherwise, the value returned will
          be zero.

     NOTE
          A common source of error is allocating buffer space as an
          ``automatic'' variable in a code block, and then failing to
          close the stream in the same block.

          (printed 07/30/92 - J B Systems)

