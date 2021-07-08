
     NAME
          fopen, freopen, fdopen - open a stream

     SYNTAX
          #include <stdio.h>

          FILE *fopen (file-name, type)
          char *file-name, *type;

          FILE *freopen (file-name, type, stream)
          char *file-name, *type;
          FILE *stream;

          FILE *fdopen (fildes, type)
          int fildes;
          char *type;

     DESCRIPTION
          Fopen opens the file named by file-name and associates a
          stream with it.  Fopen returns a pointer to the FILE
          structure associated with the stream.

          File-name points to a character string that contains the
          name of the file to be opened.

          Type is a character string having one of the following
          values:

               "b"       open as binary MPX blocked file.  Must be used
                         with r, w, or a.  This option inhibits newline
                         and allows r/w of binary data to/from MPX
                         blocked files.  Useful for reading or writing
                         object files.

               "r"       open for reading

               "u"       open as unblocked MPX file.  Must be used
                         with r, w, or a.

               "w"       truncate or create for writing

               "a"       append; open for writing at end of file, or
                         create for writing

               "r+"      open for update (reading and writing)

               "w+"      truncate or create for update

               "a+"      append; open or create for update at end-of-
                         file

          Freopen substitutes the named file in place of the open
          stream.  The original stream is closed, regardless of
          whether the open ultimately succeeds.  Freopen returns a
          pointer to the FILE structure associated with stream.

          Freopen is typically used to attach the preopened streams
          associated with stdin, stdout and stderr to other files.

          Fdopen associates a stream with a file descriptor.  File
          descriptors are obtained from open or creat which open
          files but do not return pointers to a FILE structure
          stream. Streams are necessary input for many of the
          library routines.  The type of stream must agree with
          the mode of the open file.

          When a file is opened for update, both input and output may
          be done on the resulting stream.  However, output may not be
          directly followed by input without an intervening fseek or
          rewind, and input may not be directly followed by output
          without an intervening fseek, rewind, or an input operation
          which encounters end-of-file.

          When a file is opened for append (i.e., when type is "a" or
          "a+"), it is impossible to overwrite information already in
          the file.  Fseek may be used to reposition the file pointer
          to any position in the file, but when output is written to
          the file, the current file pointer is disregarded.  All
          output is written at the end of the file and causes the file
          pointer to be repositioned at the end of the output.  If two
          separate processes open the same file for append, each
          process may write freely to the file without fear of
          destroying output being written by the other.  The output
          from the two processes will be intermixed in the file in the
          order in which it is written.

     SEE ALSO
          creat.m, open.m, fclose.m, fseek

     DIAGNOSTICS
          Fopen and freopen return a NULL pointer on failure.

          (printed 07/30/92 - J B Systems)

