
     NAME
          isatty - determine if fildes is assigned to a terminal

     SYNTAX
          int isatty (fildes)
          int fildes;

     DESCRIPTION
          Isatty returns 1 if fildes is associated with a terminal
          device, 0 otherwise.  I/O associated with the fildes will
          have newline translation completed on the I/O buffer.
          See unixio.m.

     SEE ALSO
          unixio.m

          (printed 05/31/94 - J B Systems)

