
     NAME
          j0, j1, jn, y0, y1, yn - Bessel functions

     SYNTAX
          #include <math.h>

          double j0 (x)
          double x;

          double j1 (x)
          double x;

          double jn (n, x)
          int n;
          double x;

          double y0 (x)
          double x;

          double y1 (x)
          double x;

          double yn (n, x)
          int n;
          double x;

     DESCRIPTION
          J0 and j1 return Bessel functions of x of the first kind of
          orders 0 and 1 respectively.  Jn returns the Bessel function
          of x of the first kind of order n.

          Y0 and y1 return Bessel functions of x of the second kind of
          orders 0 and 1 respectively.  Yn returns the Bessel function
          of x of the second kind of order n.  The value of x must be
          positive.

     DIAGNOSTICS
          Non-positive arguments cause y0, y1 and yn to return the
          value -HUGE and to set errno to EDOM.  In addition, a
          message indicating DOMAIN error is printed on the standard
          error output.

          Arguments too large in magnitude cause j0, j1, y0 and y1 to
          return zero and to set errno to ERANGE.  In addition, a
          message indicating TLOSS error is printed on the standard
          error output.

          These error-handling procedures may be changed with the
          function matherr().

     SEE ALSO
          matherr.m

          (printed 07/29/92 - J B Systems)

