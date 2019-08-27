
     NAME
          bcopy, bcmp - memory operations

     SYNTAX
          #include <string.h>
          #include <sys/types.h>

          void bcopy (src, dst, n)
          char *src, *dst;
          size_t n;

          int bcmp (s1, s2, n)
          char *s1, *s2;
          size_t n;

     DESCRIPTION
          The bcopy() function copies n bytes from string src to
          string dst.  The two strings may overlap.  If n is 0,
          no bytes are copied.

          The bcmp() function compares byte string s1 against byte
          string s2, returning zero if they are identical, non-zero
          otherwise.  Both strings are assumed to be n bytes long.
          Zero-length strings are always identical.  The strings
          may overlap.

     NOTE
          For user convenience, all these functions are declared in
          the <string.h> header file.

     SEE ALSO
          memcmp.m, memccpy.m, memcpy.m, strcpy.m, strncpy.m,
          strcasecmp.m, strcmp.m

          (printed 07/29/92 - J B Systems)

