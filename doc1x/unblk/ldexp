
     NAME
          frexp, ldexp, modf - manipulate parts of floating-point
          numbers

     SYNTAX
          double frexp (value, eptr)
          double value;
          int *eptr;

          double ldexp (value, exp)
          double value;
          int exp;

          double modf (value, iptr)
          double value, *iptr;

     DESCRIPTION
          Every non-zero number can be written uniquely as x * 2^n,
          where the ``mantissa'' (fraction) x is in the range 0.5 <
          |x| < 1.0, and the ``exponent'' n is an integer.  Frexp
          returns the mantissa of a double value, and stores the
          exponent indirectly in the location pointed to by eptr.  If
          value is zero, both results returned by frexp are zero.

          Ldexp returns the quantity value * 2^exp.

          Modf returns the signed fractional part of value and stores
          the integral part indirectly in the location pointed to by
          iptr.

     DIAGNOSTICS
          If ldexp would cause overflow, +HUGE is returned (according
          to the sign of value), and errno is set to ERANGE.

          If ldexp would cause underflow, zero is returned and errno
          is set to ERANGE.

          (printed 07/29/92 - J B Systems)

