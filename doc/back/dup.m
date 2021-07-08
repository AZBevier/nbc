
     NAME
          dup - duplicate an open file descriptor

     SYNTAX
          int dup (fildes)
          int fildes;

     DESCRIPTION
          This service is not implemented on MPX.

     RETURN VALUE
          A value of -1 is always returned and errno is set EMFILE
          to indicate the error.

     SEE ALSO
          creat.m, close.m, exec.m, open.m

          (printed 07/30/92 - J B Systems)

