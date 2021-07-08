
     NAME
          kill - send a signal to a process

     SYNTAX
          int kill (pid, sig)
          int pid, sig;

     DESCRIPTION
          Kill sends a signal to a process.  The process to which the
          signal is to be sent is specified by pid.  The signal that
          is to be sent is specified by sig and is either one from the
          list given in signal.m, or 0.  If sig is 0 (the null signal),
          error checking is performed but no signal is actually sent.
          This can be used to check the validity of the pid.

          If pid is greater than zero, sig will be sent to the process
          whose process ID is equal to pid.  Pid is the MPX task number.

          Kill will fail and no signal will be sent if one or more of
          the following are true:

          [EINVAL]       Sig is not a valid signal number.

          [ESRCH]        No process can be found corresponding to that
                         specified by pid.

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          getpid.m, setpgrp.m, signal.m

          (printed 07/31/92 - J B Systems)

