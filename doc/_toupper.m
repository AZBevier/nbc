
     NAME
          toupper, tolower, _toupper, _tolower, toascii - translate
          characters

     SYNTAX
          #include <ctype.h>

          int toupper (c)
          int c;

          int tolower (c)
          int c;

          int _toupper (c)
          int c;

          int _tolower (c)
          int c;

          int toascii (c)
          int c;

     DESCRIPTION
          Toupper and tolower have as domain the range of getc():
          the integers from -1 through 255.  If the argument of
          toupper represents a lower-case letter, the result is the
          corresponding upper-case letter.  If the argument of tolower
          represents an upper-case letter, the result is the
          corresponding lower-case letter.  All other arguments in the
          domain are returned unchanged.

          The macros _toupper and _tolower, are macros that accomplish
          the same thing as toupper and tolower but have restricted
          domains and are faster.  _toupper requires a lower-case
          letter as its argument; its result is the corresponding
          upper-case letter.  The macro _tolower requires an upper-
          case letter as its argument; its result is the corresponding
          lower-case letter.  Arguments outside the domain cause
          undefined results.

          Toascii yields its argument with all bits turned off that
          are not part of a standard ASCII character; it is intended
          for compatibility with other systems.

     SEE ALSO
          ctype.m, getc.m

          (printed 07/29/92 - J B Systems)

