
     NAME
          sinh, cosh, tanh - hyperbolic functions

     SYNTAX
          #include <math.h>

          double sinh (x)
          double x;

          double cosh (x)
          double x;

          double tanh (x)
          double x;

     DESCRIPTION
          Sinh, cosh, and tanh return, respectively, the hyperbolic
          sine, cosine and tangent of their argument.

     DIAGNOSTICS
          Sinh and cosh return HUGE (and sinh may return -HUGE for
          negative x) when the correct value would overflow and set
          errno to ERANGE.

          These error-handling procedures may be changed with the
          function matherr().

     SEE ALSO
          matherr.m

          (printed 07/29/92 - J B Systems)

