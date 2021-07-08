
     NAME
          write - write on a file

     SYNTAX
          int write (fildes, buf, nbyte)
          int fildes;
          char *buf;
          int nbyte;

     DESCRIPTION
          Fildes is a file descriptor obtained from a creat or open
          system call.

          Write attempts to write nbyte bytes from the buffer pointed
          to by buf to the file associated with the fildes.

          On devices capable of seeking, the actual writing of data
          proceeds from the position in the file indicated by the file
          pointer.  Upon return from write, the file pointer is
          incremented by the number of bytes actually written.

          On devices incapable of seeking, writing always takes place
          starting at the current position.  The value of a file
          pointer associated with such a device is undefined.  This
          is true for MPX blocked files.

          If the O_APPEND flag of the file status flags is set, the
          file pointer will be set to the end of the file prior to
          each write.

          Write will fail and the file pointer will remain unchanged
          if one or more of the following are true:

          [EBADF]        Fildes is not a valid file descriptor open
                         for writing.

          [EFBIG]        An attempt was made to write a file that
                         exceeds the extension limit or the
                         maximum file size.

          [EFAULT]       Buf points outside the process's allocated
                         address space.

          [EINTR]        A signal was caught during the write system
                         call.

          If a write requests that more bytes be written than there is
          room for (e.g., the physical end of a medium), only as many
          bytes as there is room for will be written.  For example,
          suppose there is space for 20 bytes more in a file before
          reaching a limit.  A write of 512 bytes will return 20.  The
          next write of a non-zero number of bytes will give a failure
          return.

     RETURN VALUE
          Upon successful completion the number of bytes actually
          written is returned.  Otherwise, -1 is returned and errno is
          set to indicate the error.

     SEE ALSO
          creat.m, lseek.m, open.m, mpxccset.m, fcbadr.m, writraw.m

     SPECIAL CONSIDERATIONS
          MPX files opened as unblocked will be treated as UNIX style
          byte stream files.  Files opened as binary will be treated
          as MPX blocked files without newline translation.  If the
          carriage control flag is set, via mpxccset(), a carriage
          control character will be prepended to the output buffer
          for terminals and SLO files.

          On MPX blocked, non binary files, newline translation is
          performed.  Output lines with only a linefeed character
          (0x0a), will be written to the file as a single blank (0x20)
          character.  On normal lines, the linefeed character is
          stripped before writing the file.  If a line is longer than
          254 characters, the first 254 characters will be written
          to the file followed by the remaining characters in the
          next MPX record.  

          The first terminal output written will be preceeded by a
          carriage return/newline to insure starting on the next
          line after the TSM command line.  During normal output
          to terminals, a carrage return/newline will be output
          when a newline character is detected.  Each call to the
          write service will cause the requested number of characters
          to be written in unformated mode.
          
          (printed 08/03/92 - J B Systems)

