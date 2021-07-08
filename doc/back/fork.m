
     NAME
          fork - create a new process

     SYNTAX
          int fork ()

     DESCRIPTION
          This service is not implemented on MPX.

     RETURN VALUE
          A value of -1 is always returned to the parent process,
          and no child process is created, and errno is set to 
          EAGAIN to indicate the error.

     SEE ALSO
          exec.m, nice.m, signal.m

          (printed 07/30/92 - J B Systems)

