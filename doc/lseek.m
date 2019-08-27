
     NAME
          lseek, seek - move read/write file pointer

     SYNTAX
          #include <stdio.h>

          long lseek (fildes, offset, whence)
          int fildes;
          long offset;
          int whence;

          long seek (fildes, offset, whence)
          int fildes;
          long offset;
          int whence;

     DESCRIPTION
          Fildes is a file descriptor returned from a creat or open
          system call.  Lseek sets the file pointer associated with
          fildes as specified by the value of the argument whence.
          Values for whence are as follows:

               Name      Description
               0         set file pointer equal to offset bytes.
               1         set file pointer to current location plus
                         offset.
               2         set file pointer to EOF plus offset.

          Upon successful completion, the resulting pointer location,
          as measured in bytes from the beginning of the file, is
          returned.

          Lseek will fail and the file pointer will remain unchanged
          if one or more of the following are true:

          [EBADF]        Fildes is not an open file descriptor.

          [EINVAL]       Whence is not 0, 1 or 2.

          [EINVAL]       The resulting file pointer would be negative.

          Some devices are incapable of seeking.  The value of the
          file pointer associated with such a device is undefined.
          MPX blocked files can only be rewound or seeked to EOF,
          otherwise an error will be returned.

     RETURN VALUE
          Upon successful completion, a non-negative integer
          indicating the file pointer value is returned.  Otherwise, a
          value of -1 is returned and errno is set to indicate the
          error.

     SEE ALSO
          creat.m, open.m

          (printed 07/32/92 - J B Systems)

