
     NAME
          nice - change priority of a process

     SYNTAX
          int nice (incr)
          int incr;

     DESCRIPTION
          This service is not implemented on MPX.  It always returns
          a -1 and sets errno to EPERM.

          [EPERM]        Nice will fail and not change the nice value
                         if incr is negative or greater than 40 and
                         the effective user ID of the calling process
                         is not super-user.

     RETURN VALUE
          A value of -1 is returned and errno is set to indicate
          the error.

     SEE ALSO
          exec.m

          (printed 08/01/92 - J B Systems)

