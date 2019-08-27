
     NAME
          wait - wait for child process to stop or terminate

     SYNTAX
          int wait (stat_loc)
          int *stat_loc;

          int wait ((int *)0)

     DESCRIPTION
          This service is not supported by MPX.  It always returns a
          -1 and sets errno to ECHILD.

          Wait will fail and return immediately if the following is
          true:

          [ECHILD]       The calling process has no existing
                         unwaited-for child processes.

     RETURN VALUE
          A value of -1 is returned and errno is set to indicate the
          error.

     SEE ALSO
          exec.m, exit.m, fork.m, pause.m, signal.m

     WARNING
          See WARNING in signal.m

          (printed 07/31/92 - J B Systems)

