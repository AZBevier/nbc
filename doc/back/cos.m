
     NAME
          sin, cos, tan, asin, acos, atan, atan2 - trigonometric
          functions

     SYNTAX
          #include <math.h>

          double sin (x)
          double x;

          double cos (x)
          double x;

          double tan (x)
          double x;

          double asin (x)
          double x;

          double acos (x)
          double x;

          double atan (x)
          double x;

          double atan2 (y, x)
          double y, x;

     DESCRIPTION
          Sin, cos and tan return respectively the sine, cosine and
          tangent of their argument, x, measured in radians.

          Asin returns the arcsine of x, in the range -pi/2 to pi/2.

          Acos returns the arccosine of x, in the range 0 to pi.

          Atan returns the arctangent of x, in the range -pi/2 to pi/2.

          Atan2 returns the arctangent of y/x, in the range -pi to pi,
          using the signs of both arguments to determine the quadrant
          of the return value.

     DIAGNOSTICS
          Sin, cos, and tan lose accuracy when their argument is far
          from zero.  For arguments sufficiently large, these
          functions return zero when there would otherwise be a
          complete loss of significance.  In this case a message
          indicating TLOSS error is printed on the standard error
          output.  For less extreme arguments causing partial loss of
          significance, a PLOSS error is generated but no message is
          printed.  In both cases, errno is set to ERANGE.

          If the magnitude of the argument of asin or acos is greater
          than one, zero is returned and errno is set to EDOM.  In
          addition, a message indicating DOMAIN error is printed on
          the standard error output.

          These error-handling procedures may be changed with the
          function matherr().

     SEE ALSO
          matherr.m

     NOTE
          Standard UNIX System V treats atan2 with both arguments zero
          as an EDOM error.

          (printed 07/29/92 - J B Systems)

