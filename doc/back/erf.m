
     NAME
          erf, erfc - error function and complementary error function

     SYNTAX
          #include <math.h>

          double erf (x)
          double x;

          double erfc (x)
          double x;

     DESCRIPTION
          Erf returns the error function of x, defined as 2/sqrt(pi)*
          integral from 0 to x of exp(-t*t) dt.

          Erfc, which returns 1.0 - erf(x), is provided because of the
          extreme loss of relative accuracy if erf(x) is called for
          large x and the result subtracted from 1.0 (e.g., for x = 5,
          12 places are lost).

     SEE ALSO
          exp.m

          (printed 07/29/92 - J B Systems)

