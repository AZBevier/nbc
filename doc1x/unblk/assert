
     NAME
          assert - verify program assertion

     SYNTAX
          #include <assert.h>

          assert (expression)
          int expression;

     DESCRIPTION
          This macro is useful for putting diagnostics into programs.
          When it is executed, if expression is false (zero), assert
          prints

               ``Assertion failed: expression, file xyz, line nnn''

          on the standard error output and aborts.  In the error
          message, xyz is the name of the source file and nnn the
          source line number of the assert statement.

          Compiling with the preprocessor option -DNDEBUG (see
          nbcpp.m), or with the preprocessor control statement
          ``#define NDEBUG'' ahead of the ``#include <assert.h>''
          statement, will stop assertions from being compiled into the
          program.

     SEE ALSO
          nbcc.m, nbcpp.m, abort.m

          (printed 07/30/92 - J B Systems)

