
     NAME
          swab - swap bytes

     SYNTAX
          void swab (from, to, nbytes)
          char *from, *to;
          int nbytes;

     DESCRIPTION
          Swab copies nbytes bytes pointed to by from to the array
          pointed to by to, exchanging adjacent even and odd bytes.
          It is useful for carrying binary data between PDP-11s and
          other machines.  Nbytes should be even and non-negative.  If
          nbytes is odd and positive swab uses nbytes-1 instead. If
          nbytes is negative, swab does nothing.

          (printed 07/29/92 - J B Systems)

