
     NAME
          times - get process and child process times

     SYNTAX
          #include <sys/types.h>
          #include <sys/times.h>

          long times (buffer)
          struct tms *buffer;

     DESCRIPTION
          Times fills the structure pointed to by buffer with time-
          accounting information.  The following are the contents of
          this structure:

          struct    tms {
               time_t      tms_utime;
               time_t      tms_stime;
               time_t      tms_cutime;
               time_t      tms_cstime;
          };

          This information comes from the calling process.  All times
          are in 60ths of a second.

          Tms_utime is the CPU time used while executing instructions
          in the user space of the calling process.  This is the only
          parameter value returned on MPX.

          Tms_stime is the CPU time used by the system on behalf of
          the calling process.  Always zero on MPX.

          Tms_cutime is the sum of the tms_utimes and tms_cutimes of
          the child processes.  Always zero on MPX.

          Tms_cstime is the sum of the tms_stimes and tms_cstimes of
          the child processes.  Always zero on MPX.

          [EFAULT]  Times will fail if buffer points to an illegal
                    address.

     RETURN VALUE
          Upon successful completion, times returns the elapsed real
          time, in 60ths of a second, since an arbitrary point in the
          past (e.g., system start-up time).  This point does not
          change from one invocation of times to another.  If times
          fails, a -1 is returned and errno is set to indicate the
          error.

     SEE ALSO
          exec.m, fork.m, time.m

          (printed 08/01/92 - J B Systems)

