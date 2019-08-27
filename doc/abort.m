
     NAME
          abort - generate an abnormal task termination

     SYNTAX
          int abort ( )

     DESCRIPTION
          Abort first closes all open files if possible, then calls
          exit () with an abort code of 10.  This usually results
          in a termination with an error code of CC10.

     SEE ALSO
          exit.m

          (printed 07/29/92 - J B Systems)

