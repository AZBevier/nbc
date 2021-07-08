
     NAME
          exp, log, log10, pow, sqrt - exponential, logarithm, power,
          square root functions

     SYNTAX
          #include <math.h>

          double exp (x)
          double x;

          double log (x)
          double x;

          double log10 (x)
          double x;

          double pow (x, y)
          double x, y;

          double sqrt (x)
          double x;

     DESCRIPTION
          Exp returns e**x.

          Log returns the natural logarithm of x.  The value of x must
          be positive.

          Log10 returns the logarithm base ten of x.  The value of x
          must be positive.

          Pow returns x**y.  If x is zero, y must be positive.  If x is
          negative, y must be an integer.

          Sqrt returns the non-negative square root of x.  The value
          of x may not be negative.

     DIAGNOSTICS
          Exp returns HUGE when the correct value would overflow, or 0
          when the correct value would underflow, and sets errno to
          ERANGE.

          Log and log10 return -HUGE and set errno to EDOM when x is
          non-positive.  A message indicating DOMAIN error (or SING
          error when x is 0) is printed on the standard error output.

          Pow returns 0 and sets errno to EDOM when x is 0 and y is
          non-positive, or when x is negative and y is not an integer.
          In these cases a message indicating DOMAIN error is printed
          on the standard error output.  When the correct value for
          pow would overflow or underflow, pow returns +HUGE or 0
          respectively, and sets errno to ERANGE.

          Sqrt returns 0 and sets errno to EDOM when x is negative.  A
          message indicating DOMAIN error is printed on the standard
          error output.

          These error-handling procedures may be changed with the
          function matherr().

     SEE ALSO
          hypot.m, matherr.m, sinh.m

          (printed 07/29/92 - J B Systems)

