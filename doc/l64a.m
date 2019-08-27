
     NAME
          a64l, l64a - convert between long integer and base-64 ASCII
          string

     SYNTAX
          long a64l (s)
          char *s;

          char *l64a (l)
          long l;

     DESCRIPTION
          These functions are used to maintain numbers stored in
          base-64 ASCII characters.  This is a notation by which long
          integers can be represented by up to six characters; each
          character represents a ``digit'' in a radix-64 notation.

          The characters used to represent ``digits'' are . for 0, /
          for 1, 0 through 9 for 2-11, A through Z for 12-37, and a
          through z for 38-63.

          A64l takes a pointer to a null-terminated base-64
          representation and returns a corresponding long value.  If
          the string pointed to by s contains more than six
          characters, a64l will use the first six.

          L64a takes a long argument and returns a pointer to the
          corresponding base-64 representation.  If the argument is 0,
          l64a returns a pointer to a null string.

     SPECIAL CONSIDERATIONS
          The value returned by l64a is a pointer into a static
          buffer, the contents of which are overwritten by each call.

          (printed 07/29/92 - J B Systems)

