
     NAME
          gamma - log gamma function

     SYNTAX
          #include <math.h>

          double gamma (x)
          double x;

          extern int signgam;

     DESCRIPTION
          Gamma returns ln (| GAMMA ( x ) |), where
          GAMMA ( x ) is defined as integral from 0 to inf e(-t)
          t(x-1) dt. The sign of GAMMA ( x ) is returned in the
          external integer signgam.  The argument x may not be a
          nonpositive integer.

          The following C program fragment might be used to calculate
          G:

               if ((y = gamma(x)) > LN_MAXDOUBLE)
                    error();
               y = signgam * exp(y);

          where LN_MAXDOUBLE is the least value that causes exp() to
          return a range error, and is defined in the <values.h>
          header file.

     DIAGNOSTICS
          For nonpositive integer arguments HUGE is returned, and
          errno is set to EDOM.  A message indicating SING error is
          printed on the standard error output.

          If the correct value would overflow, gamma returns HUGE and
          sets errno to ERANGE.

          These error-handling procedures may be changed with the
          function matherr().

     SEE ALSO
          exp.m, matherr.m, values.m

          (printed 07/29/92 - J B Systems)

