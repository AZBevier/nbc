
     NAME
          floor, ceil, fmod, fabs - floor, ceiling, remainder,
          absolute value functions

     SYNTAX
          #include <math.h>

          double floor (x)
          double x;

          double ceil (x)
          double x;

          double fmod (x, y)
          double x, y;

          double fabs (x)
          double x;

     DESCRIPTION
          Floor returns the largest integer (as a double-precision
          number) not greater than x.

          Ceil returns the smallest integer not less than x.

          Fmod returns the floating-point remainder of the division of
          x by y: zero if y is zero or if x/y would overflow;
          otherwise the number f with the same sign as x, such that x
          = iy + f for some integer i, and |f| < |y|.

          Fabs returns the absolute value of x, |x|.

     SEE ALSO
          abs.m

          (printed 07/29/92 - J B Systems)

