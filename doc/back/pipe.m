
     NAME
          pipe - create an interprocess channel

     SYNTAX
          int pipe (fildes)
          int fildes[2];

     DESCRIPTION
          This service is not supported by MPX.  A value of -1 is
          always returned and errno is set to EMFILE.

          [EMFILE]       To many open files.

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          read.m, write.m

          (printed 08/01/92 - J B Systems)

