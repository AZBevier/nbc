
     NAME
          setjmp, longjmp - non-local goto

     SYNTAX
          #include <setjmp.h>

          int setjmp (env)
          jmp_buf env;

          void longjmp (env, val)
          jmp_buf env;
          int val;

     DESCRIPTION
          These functions are useful for dealing with errors and
          interrupts encountered in a low-level subroutine of a
          program.

          Setjmp saves its stack environment in env (whose type,
          jmp_buf, is defined in the <setjmp.h> header file) for later
          use by longjmp.  It returns the value 0.

          Longjmp restores the environment saved by the last call of
          setjmp with the corresponding env argument.  After longjmp
          is completed, program execution continues as if the
          corresponding call of setjmp (which must not itself have
          returned in the interim) had just returned the value val.
          Longjmp cannot cause setjmp to return the value 0.  If
          longjmp is invoked with a second argument of 0, setjmp will
          return 1.  All accessible data had values as of the time
          longjmp was called.

     SEE ALSO
          signal.m

     WARNING
          If longjmp is called even though env was never primed by a
          call to setjmp, or when the last such call was in a function
          which has since returned, absolute chaos is guaranteed.

          (printed 07/29/92 - J B Systems)

