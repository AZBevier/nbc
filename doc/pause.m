
     NAME
          pause - suspend process until signal

     SYNTAX
          pause (timeru)
          int timeru;		/* MPX timer units to wait */

     DESCRIPTION
          Pause suspends the calling process until it receives a
          signal, a message, I/O completes, or the wait time
          expires.  The signal must be one that is not currently
          set to be ignored by the calling process.  The calling
          process will be placed into the MPX ANYWAIT queue.

          If the signal causes termination of the calling process,
          pause will not return.

          If the signal is caught by the calling process and control
          is returned from the signal-catching function (see
          signal.m), the calling process resumes execution from the
          point of suspension; with a return value of -1 from pause
          and errno set to EINTR.

     SEE ALSO
          alarm.m, kill.m, signal.m, wait.m

          (printed 07/31/92 - J B Systems)

