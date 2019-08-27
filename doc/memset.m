
     NAME
          memccpy, memchr, memcmp, memcpy, memset - memory operations

     SYNTAX
          #include <memory.h>

          char *memccpy (s1, s2, c, n)
          char *s1, *s2;
          int c, n;

          char *memchr (s, c, n)
          char *s;
          int c, n;

          int memcmp (s1, s2, n)
          char *s1, *s2;
          int n;

          char *memcpy (s1, s2, n)
          char *s1, *s2;
          int n;

          char *memset (s, c, n)
          char *s;
          int c, n;

     DESCRIPTION
          These functions operate as efficiently as possible on memory
          areas (arrays of characters bounded by a count, not
          terminated by a null character).  They do not check for the
          overflow of any receiving memory area.

          Memccpy copies characters from memory area s2 into s1,
          stopping after the first occurrence of character c has been
          copied, or after n characters have been copied, whichever
          comes first.  It returns a pointer to the character after
          the copy of c in s1, or a NULL pointer if c was not found in
          the first n characters of s2.

          Memchr returns a pointer to the first occurrence of
          character c in the first n characters of memory area s, or a
          NULL pointer if c does not occur.

          Memcmp compares its arguments, looking at the first n
          characters only, and returns an integer less than, equal to,
          or greater than 0, according as s1 is lexicographically less
          than, equal to, or greater than s2.

          Memcpy copies n characters from memory area s2 to s1.  It
          returns s1.

          Memset sets the first n characters in memory area s to the
          value of character c.  It returns s.

     NOTE
          For user convenience, all these functions are declared in
          the <string.h> header file.

     SPECIAL CONSIDERATIONS
          Memcmp uses native character comparison, which is signed on
          some systems, and unsigned on others.  Thus the sign of the
          value returned when one of the characters has its high-order
          bit set is implementation-dependent.

          Character movement is performed differently in different
          implementations.  Thus overlapping moves may yield
          surprises.

          (printed 07/29/92 - J B Systems)

