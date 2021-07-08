
     NAME
          read - read from file

     SYNTAX
          int read (fildes, buf, nbyte)
          int fildes;
          char *buf;
          int nbyte;

     DESCRIPTION
          Fildes is a file descriptor obtained from a creat or open
          system call.

          Read attempts to read nbyte bytes from the file associated
          with fildes into the buffer pointed to by buf.

          On devices capable of seeking, the read starts at a position
          in the file given by the file pointer associated with
          fildes.  Upon return from read, the file pointer is
          incremented by the number of bytes actually read.

          Devices that are incapable of seeking always read from the
          current position.  The value of a file pointer associated
          with such a file is undefined.  This is always true with
          MPX blocked files.

          Upon successful completion, read returns the number of bytes
          actually read and placed in the buffer; this number may be
          less than nbyte if the file is associated with a terminal,
          or if the number of bytes left in the file is less than
          nbyte bytes.  A value of 0 is returned when an end-of-file
          has been reached.

          When attempting to read a file associated with a tty that
          has no data currently available:

               If O_NDELAY is set, the read will return a 0.
               This option is no supported on MPX.

               If O_NDELAY is clear, the read will block until data
               becomes available.

          Read will fail if one or more of the following are true:

          [EBADF]        Fildes is not a valid file descriptor open
                         for reading.

          [EFAULT]       Buf points outside the allocated address
                         space.

     RETURN VALUE
          Upon successful completion a non-negative integer is
          returned indicating the number of bytes actually read.
          Otherwise, a -1 is returned and errno is set to indicate the
          error.

     SEE ALSO
          creat.m, open.m, write.m

     SPECIAL CONSIDERATIONS
          When reading a non binary MPX blocked file, a single space
          character (0x20) read from the MPX file is converted to a
          single newline character.  See write.m.

          Editor saved files are read by the read() service, however
          only stored files are written.  This conversion is done
          automatically by the read() service.

          (printed 08/03/92 - J B Systems)

