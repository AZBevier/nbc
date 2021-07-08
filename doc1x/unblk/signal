
     NAME
          signal - specify what to do upon receipt of a signal

     SYNTAX
          #include <signal.h>

          void (*signal (sig, func))()
          int sig;
          void (*func)();

     DESCRIPTION
          Signal allows the calling process to choose one of three
          ways in which it is possible to handle the receipt of a
          specific signal.  Sig specifies the signal and func
          specifies the choice.

          Sig can be assigned any one of the following except SIGKILL:

              SIGHUP    01   hangup
              SIGINT    02   interrupt
              SIGQUIT   03*  quit
              SIGILL    04*  illegal instruction (not reset when caught)
              SIGTRAP   05*  trace trap (not reset when caught)
              SIGABRT   06*  abort
              SIGEMT    07*  EMT instruction
              SIGFPE    08*  floating point exception 
              SIGKILL   09   kill (cannot be caught or ignored)
              SIGBUS    10*  bus error
              SIGSEGV   11*  segmentation violation
              SIGSYS    12*  bad argument to system call
              SIGPIPE   13   write on a pipe with no one to read it
              SIGALRM   14   alarm clock
              SIGTERM   15   software termination signal
              SIGUSR1   30   user-defined signal 1
              SIGUSR2   31   user-defined signal 2
              SIGCLD    18   death of a child (see WARNING below)
              SIGPWR    19   power fail (see WARNING below)

          See below for the significance of the asterisk (*) in the
          above list.

          Func is assigned one of three values: SIG_DFL, SIG_IGN, or a
          function address.  The actions prescribed by these values
          are as follows:

          SIG_DFL - terminate process upon receipt of a signal
                  Upon receipt of the signal sig, the receiving
                  process is to be terminated with all of the
                  consequences outlined in exit.m.

          SIG_IGN - ignore signal
                  The signal sig is to be ignored.

                  Note: the signal SIGKILL cannot be ignored.

          function address -  catch signal
                  Upon receipt of the signal sig, the receiving
                  process is to execute the signal-catching function
                  pointed to by func.  The signal number sig will be
                  passed as the only argument to the signal-catching
                  function.  Additional arguments are passed to the
                  signal-catching function for hardware-generated
                  signals.  Before entering the signal-catching
                  function, the value of func for the caught signal
                  will be set to SIG_DFL unless the signal is SIGILL,
                  SIGTRAP, or SIGPWR.

                  Upon return from the signal-catching function, the
                  receiving process will resume execution at the point
                  it was interrupted.

                  When a signal that is to be caught occurs during a
                  read, a write, or an open system call on a
                  slow device (like a terminal; but not a file),
                  during a pause system call, or during a wait system
                  call that does not return immediately due to the
                  existence of a previously stopped process,
                  the signal catching function will be executed and
                  then the interrupted system call may return a -1 to
                  the calling process with errno set to EINTR.

                  Note: The signal SIGKILL cannot be caught.

          A call to signal cancels a pending signal sig except for a
          pending SIGKILL signal.

          Signal will fail if sig is an illegal signal number,
          including SIGKILL.  [EINVAL]

     RETURN VALUE
          Upon successful completion, signal returns the previous
          value of func for the specified signal sig.  Otherwise, a
          value of -1 is returned and errno is set to indicate the
          error.

     SEE ALSO
          kill.m, pause.m. wait.m, setjmp.m

     WARNING
          Two other signals that behave differently than the signals
          described above exist in this release of the system; they
          are:

                  SIGCLD  18   death of a child (reset when caught)
                  SIGPWR  19   power fail (not reset when caught)

          There is no guarantee that, in future releases of the UNIX
          system, these signals will continue to behave as described
          below; they are included only for compatibility with other
          versions of the UNIX system.  Their use in new programs is
          strongly discouraged.

          For these signals, func is assigned one of three values:
          SIG_DFL, SIG_IGN, or a function address.  The actions
          prescribed by these values are as follows:

            SIG_DFL - ignore signal
                    The signal is to be ignored.

            SIG_IGN - ignore signal
                    The signal is to be ignored.

            function address - catch signal
                    If the signal is SIGPWR, the action to be taken is
                    the same as that described above for func equal to
                    function address.  The same is true if the signal
                    is SIGCLD except, that while the process is
                    executing the signal-catching function, any
                    received SIGCLD signals will be queued and the
                    signal-catching function will be continually
                    reentered until the queue is empty.

            (printed 08/01/92 - J B Systems)

