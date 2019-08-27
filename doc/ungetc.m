
     NAME
          ungetc - push character back into input stream

     SYNTAX
          #include <stdio.h>

          int ungetc (c, stream)
          int c;
          FILE *stream;

     DESCRIPTION
          Ungetc inserts the character c into the buffer associated
          with an input stream.  That character, c, will be returned
          by the next getc() call on that stream.  Ungetc returns c,
          and leaves the file stream unchanged.

          One character of pushback is guaranteed, provided something
          has already been read from the stream and the stream is
          actually buffered.  In the case that stream is stdin, one
          character may be pushed back onto the buffer without a
          previous read statement.

          If c equals EOF, ungetc does nothing to the buffer and
          returns EOF.

          Fseek() erases all memory of inserted characters.

     SEE ALSO
          fseek.m, getc.m, setbuf.m

     DIAGNOSTICS
          Ungetc returns EOF if it cannot insert the character.

          (printed 07/30/92 - J B Systems)

