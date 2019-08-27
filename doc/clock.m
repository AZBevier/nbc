
     NAME
          clock - report CPU time used

     SYNTAX
          long clock ( )

     DESCRIPTION
          Clock returns the amount of CPU time (in microseconds) used
          since the first call to clock.  The time reported is the sum
          of the user and system times of the calling process and its
          terminated child processes.  Only the user time is reported
          by times().

          The resolution of the clock is 16.6 milliseconds on the Encore
          (Gould) processors.

     SEE ALSO
          times.m

     SPECIAL CONSIDERATIONS
          The value returned by clock is defined in microseconds for
          compatibility with systems that have CPU clocks with much
          higher resolution.  Because of this, the value returned will
          wrap around after accumulating only 2147 seconds of CPU time
          (about 36 minutes).

          (printed 07/29/92 - J B Systems)

