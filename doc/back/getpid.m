
     NAME
          getpid, getpgrp, getppid - get process, process group, and
          parent process IDs

     SYNTAX
          int getpid ()

          int getpgrp ()

          int getppid ()

     DESCRIPTION
          Getpid returns the process ID of the calling process.  This
          is the task number on MPX.

          Getpgrp returns the process group ID of the calling process.
          This service is not implemented on MPX.  A value of zero is
          always returned.

          Getppid returns the parent process ID of the calling process.
          This is the parents task number on MPX.

     SEE ALSO
          exec.m, fork.m, setpgrp.m, signal.m

          (printed 08/03/92 - J B Systems)

