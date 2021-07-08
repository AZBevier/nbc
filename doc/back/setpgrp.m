
     NAME
          setpgrp - set process group ID

     SYNTAX
          int setpgrp ()

     DESCRIPTION
          This service is not implemented in MPX.  A value of zero
          is always returned.

          Setpgrp sets the process group ID of the calling process to
          the process ID of the calling process and returns the new
          process group ID.

     RETURN VALUE
          Setpgrp returns the value of the new process group ID.

     SEE ALSO
          exec.m, fork.m, getpid.m, kill.m, signal.m

          (printed 08/03/92 - J B Systems)

