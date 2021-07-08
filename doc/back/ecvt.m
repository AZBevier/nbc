
     NAME
          ecvt, fcvt, gcvt - convert floating-point number to string

     SYNTAX
          char *ecvt (value, ndigit, decpt, sign)
          double value;
          int ndigit, *decpt, *sign;

          char *fcvt (value, ndigit, decpt, sign)
          double value;
          int ndigit, *decpt, *sign;

          char *gcvt (value, ndigit, buf)
          double value;
          int ndigit;
          char *buf;

     DESCRIPTION
          Ecvt converts value to a null-terminated string of ndigit
          digits and returns a pointer thereto.  The high-order digit
          is non-zero, unless the value is zero.  The low-order digit
          is rounded.  The position of the decimal point relative to
          the beginning of the string is stored indirectly through
          decpt (negative means to the left of the returned digits).
          The decimal point is not included in the returned string.
          If the sign of the result is negative, the word pointed to
          by sign is non-zero, otherwise it is zero.

          Fcvt is identical to ecvt, except that the correct digit has
          been rounded for printf ``%f'' (FORTRAN F-format) output of
          the number of digits specified by ndigit.

          Gcvt converts the value to a null-terminated string in the
          array pointed to by buf and returns buf.  It attempts to
          produce ndigit significant digits in FORTRAN F-format if
          possible, otherwise E-format, ready for printing. A minus
          sign, if there is one, or a decimal point will be included
          as part of the returned string.  Trailing zeros are
          suppressed.

     SEE ALSO
          printf.m

     SPECIAL CONSIDERATIONS
          The values returned by ecvt and fcvt point to a single
          static data array whose content is overwritten by each call.

          (printed 07/29/92 - J B Systems)

