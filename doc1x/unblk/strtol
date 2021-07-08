
     NAME
          strtol, atol, atoi - convert string to integer

     SYNTAX
          long strtol (str, ptr, base)
          char *str, **ptr;
          int base;

          long atol (str)
          char *str;

          int atoi (str)
          char *str;

     DESCRIPTION
          Strtol returns as a long integer the value represented by
          the character string pointed to by str.  The string is
          scanned up to the first character inconsistent with the
          base.  Leading ``white-space'' characters (as defined by
          isspace in <ctype.h>) are ignored.

          If the value of ptr is not (char **)NULL, a pointer to the
          character terminating the scan is returned in the location
          pointed to by ptr.  If no integer can be formed, that
          location is set to str, and zero is returned.

          If base is positive (and not greater than 36), it is used as
          the base for conversion.  After an optional leading sign,
          leading zeros are ignored, and ``0x'' or ``0X'' is ignored
          if base is 16.

          If base is zero, the string itself determines the base
          thusly: After an optional leading sign a leading zero
          indicates octal conversion, and a leading ``0x'' or ``0X''
          hexadecimal conversion.  Otherwise, decimal conversion is
          used.

          Truncation from long to int can, of course, take place upon
          assignment or by an explicit cast.

          Atol(str) is equivalent to strtol(str, (char **)NULL, 10).

          Atoi(str) is equivalent to (int) strtol(str, (char **)NULL, 10).

     SEE ALSO
          ctype.m, scanf.m, strtod.m

     SPECIAL CONSIDERATIONS
          Overflow conditions are ignored.

          (printed 07/29/92 - J B Systems)

