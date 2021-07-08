
     NAME
          strtod, atof - convert string to double-precision number

     SYNTAX
          double strtod (str, ptr)
          char *str, **ptr;

          double atof (str)
          char *str;

     DESCRIPTION
          Strtod returns as a double-precision floating-point number
          the value represented by the character string pointed to by
          str.  The string is scanned up to the first unrecognized
          character.

          Strtod recognizes an optional string of ``white-space''
          characters (as defined by isspace in <ctype.h>), then an
          optional sign, then a string of digits optionally containing
          a decimal point, then an optional e or E followed by an
          optional sign or space, followed by an integer.

          If the value of ptr is not (char **)NULL, a pointer to the
          character terminating the scan is returned in the location
          pointed to by ptr.  If no number can be formed, *ptr is set
          to str, and zero is returned.

          Atof(str) is equivalent to strtod(str, (char **)NULL).

     SEE ALSO
          ctype.m, scanf.m, strtol.m

     DIAGNOSTICS
          If the correct value would cause overflow, +HUGE is returned
          (according to the sign of the value), and errno is set to
          ERANGE.

          If the correct value would cause underflow, zero is returned
          and errno is set to ERANGE.

          (printed 07/29/92 - J B Systems)

