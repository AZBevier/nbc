
     NAME
          sleep - suspend execution for interval

     SYNTAX
          sleep (tunits)
          int tunits;

     DESCRIPTION
          The current process is suspended from execution for the
          number of timer units specified by the argument.  The MPX
          service m.susp is called to suspend the current task.

          The suspension time may be longer or shorter than requested
          by an arbitrary amount due to the scheduling of other
          activity in the system.  The value returned by sleep will be the
          ``unslept'' amount (the requested time minus the time
          actually slept).  This will always be zero for MPX.

     SEE ALSO
          pause.m

          (printed 07/29/92 - J B Systems)

