
     NAME
          stdio - standard buffered input/output package

     SYNTAX
          #include <stdio.h>

          FILE *stdin, *stdout, *stderr;

     DESCRIPTION
          The functions described in the entries for I/O constitute
          an efficient, user-level I/O buffering scheme.  The in-line
          macros getc() and putc() handle characters quickly.  The
          macros getchar and putchar, and the higher-level routines
          fgetc, fgets, fprintf, fputc, fputs, fread, fscanf, fwrite,
          gets, getw, printf, puts, putw, and scanf all use or act as
          if they use getc and putc; they can be freely intermixed.

          A file with associated buffering is called a stream and is
          declared to be a pointer to a defined type FILE.  Fopen()
          creates certain descriptive data for a stream and returns a
          pointer to designate the stream in all further transactions.
          Normally, there are three open streams with constant
          pointers declared in the <stdio.h> header file and
          associated with the standard open files:

               stdin     standard input file
               stdout    standard output file
               stderr    standard error file

          A constant NULL (0) designates a nonexistent pointer.

          An integer-constant EOF (-1) is returned upon end-of-file or
          error by most integer functions that deal with streams (see
          the individual descriptions for details).

          An integer constant BUFSIZ specifies the size of the buffers
          used by the particular implementation.

          Any program that uses this package must include the header
          file of pertinent macro definitions, as follows:

               #include <stdio.h>

          The functions and constants mentioned in the I/O manual
          entries are declared in that header file and need no further
          declaration.  The constants and the following ``functions''
          are implemented as macros (redeclaration of these names is
          perilous): getc, getchar, putc, putchar, ferror, feof,
          clearerr, and fileno.

     SEE ALSO
          open.m, close.m, lseek.m, read.m, write.m, fclose.m,
          ferror.m, fopen.m, fread.m, fseek.m, getc.m, gets.m,
          printf.m, putc.m, puts.m, scanf.m, setbuf.m, tmpfile.m,
          tmpnam.m, ungetc.m.

     DIAGNOSTICS
          Invalid stream pointers will usually cause problems,
          possibly including program termination.  Individual function
          descriptions describe the possible error conditions.

          (printed 07/30/92 - J B Systems)

