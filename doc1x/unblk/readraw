
     NAME
          fcbadr - get FCB address
          read1ln, readraw, writraw - special MPX I/O calls

     SYNTAX
          #include <stdio.h>
          #include <fcb.h>
          
          struct fcb *fcbadr (fildes)
          int fildes;

          int read1ln (fildes, buf, nbyte)
          int fildes;
          char * buf;
          int nbyte;

          int readraw (fildes, buf, nbyte)
          int fildes;
          char * buf;
          int nbyte;

          int writraw (fildes, buf, nbyte)
          int fildes;
          char * buf;
          int nbyte;

     DESCRIPTION
          Fildes is a file descriptor obtained from a creat or open
          system call.  Buf is the input/output buffer address.
          Nbyte determines the maximum read/write count in bytes.

          Fcbadr returns a pointer to the FCB used by the unixio
          emulation software.  This FCB can be used in MPX SVC
          calls to issue I/O directly.  It is a 16 word FCB.  The
          user can use open() to assign and allocate the FCB.  Care
          should be taken when modifying any fields within the FCB.
          The results may be unpredictable.

          Read1ln reads just one MPX blocked record from the specified
          file descriptor.  Normal newline translation will be
          completed.  The number of characters read will be returned
          to the caller.  The standard read() routine will always
          return the requested number of bytes.

          Readraw reads one MPX record from the specified file
          descriptor directly into the users buffer.  Writraw writes
          one MPX record to the specified file descriptor from the
          users buffer.  A maximum of nbyte bytes will be read or
          written.  The number of characters read or written will be
          returned.  Sequential access is used.  The random flag in
          the FCB is forced off prior to calling the MPX I/O SVC.
          This entry is normally used to issue I/O requests to
          magnetic tapes where one logical block of data is required.
          It can also be used to do single character I/O to/from
          terminals.  No newline translation is completed nor is
          the user's buffer in any way modified.  The callers buffer
          address is inserted directly into the FCB, so it is the
          responsiblity of the user to provide the correct buffer
          allignment.  An EOF (-1) or EOM (-2) is returned if
          encountered.

     RETURN VALUE
          The FCB address or transfer count is returned on success.
          An EOF (-1) or EOM (-2) is returned on error and errno is
          set to the MPX error number. (See errno.h)  The device
          status bits in the FCB can also be observed directly.

     SEE ALSO
          open.m, read.m, write.m

          (printed 08/04/92 - J B Systems)

