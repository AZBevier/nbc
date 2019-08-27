
     NAME
          time - get time

     SYNTAX
          #include <sys/types.h>

          time_t time (tloc)
          time_t *tloc;

     DESCRIPTION
          Time returns the value of time in seconds since 00:00:00
          GMT, January 1, 1970.

          If tloc (taken as an integer) is non-zero, the return value
          is also stored in the location to which tloc points.

          [EFAULT]  Time will fail if tloc points to an illegal
                    address.

     RETURN VALUE
          Upon successful completion, time returns the value of time.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          stime.m

          (printed 08/01/92 - J B Systems)

