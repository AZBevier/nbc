
     NAME
          drand48, erand48, lrand48, nrand48, mrand48, jrand48,
          srand48, seed48, lcong48 - generate uniformly distributed
          pseudo-random numbers

     SYNTAX
          double drand48 ( )

          double erand48 (xsubi)
          unsigned short xsubi[3];

          long lrand48 ( )

          long nrand48 (xsubi)
          unsigned short xsubi[3];

          long mrand48 ( )

          long jrand48 (xsubi)
          unsigned short xsubi[3];

          void srand48 (seedval)
          long seedval;

          unsigned short *seed48 (seed16v)
          unsigned short seed16v[3];

          void lcong48 (param)
          unsigned short param[7];

     DESCRIPTION
          This family of functions generates pseudo-random numbers
          using the well-known linear congruential algorithm and 48-
          bit integer arithmetic.

          Functions drand48 and erand48 return non-negative double-
          precision floating-point values uniformly distributed over
          the interval [0.0, 1.0].

          Functions lrand48 and nrand48 return non-negative long
          integers uniformly distributed over the interval [0, 2].

          Functions mrand48 and jrand48 return signed long integers
          uniformly distributed over the interval [-2, 2].

          Functions srand48, seed48 and lcong48 are initialization
          entry points, one of which should be invoked before either
          drand48, lrand48 or mrand48 is called.  (Although it is not
          recommended practice, constant default initializer values
          will be supplied automatically if drand48, lrand48 or
          mrand48 is called without a prior call to an initialization
          entry point.) Functions erand48, nrand48 and jrand48 do not
          require an initialization entry point to be called first.

          All the routines work by generating a sequence of 48-bit
          integer values, Xi, according to the linear congruential
          formula

           Xn+1 = (aXn+c)mod m       for n >= 0.

          The parameter m = 2^48; hence 48-bit integer arithmetic is
          performed.  Unless lcong48 has been invoked, the multiplier
          value a and the addend value c are given by

                a = 5DEECE66D base 16 = 273673163155 base 8
                c = B base 16 = 13 base 8.

          The value returned by any of the functions drand48, erand48,
          lrand48, nrand48, mrand48 or jrand48 is computed by first
          generating the next 48-bit Xi in the sequence.  Then
          the appropriate number of bits, according to the type of
          data item to be returned, are copied from the high-order
          (leftmost) bits of Xi and transformed into the returned value.

          The functions drand48, lrand48 and mrand48 store the last
          48-bit Xi generated in an internal buffer; that is
          why they must be initialized prior to being invoked.  The
          functions erand48, nrand48 and jrand48 require the calling
          program to provide storage for the successive Xi
          values in the array specified as an argument when the
          functions are invoked.  That is why these routines do not
          have to be initialized; the calling program merely has to
          place the desired initial value of Xi into the array
          and pass it as an argument.  By using different arguments,
          functions erand48, nrand48 and jrand48 allow separate
          modules of a large program to generate several independent
          streams of pseudo-random numbers, i.e., the sequence of
          numbers in each stream will not depend upon how many times
          the routines have been called to generate numbers for the
          other streams.

          The initializer function srand48 sets the high-order 32 bits
          of Xi to the 32 bits contained in its argument.  The
          low-order 16 bits of Xi are set to the arbitrary
          value 330E base 16.

          The initializer function seed48 sets the value of Xi
          to the 48-bit value specified in the argument array.  In
          addition, the previous value of Xi is copied into a
          48-bit internal buffer, used only by seed48, and a pointer
          to this buffer is the value returned by seed48. This
          returned pointer, which can just be ignored if not needed,
          is useful if a program is to be restarted from a given point
          at some future time - use the pointer to get at and store
          the last Xi value, and then use this value to
          reinitialize via seed48 when the program is restarted.

          The initialization function lcong48 allows the user to
          specify the initial Xi, the multiplier value a,
          and the addend value c. Argument array elements param[0-2]
          specify Xi, param[3-5] specify the multiplier a,
          and param[6] specifies the 16-bit addend c. After lcong48
          has been called, a subsequent call to either srand48 or
          seed48 will restore the ``standard'' multiplier and addend
          values, a and c, specified on the previous page.

     NOTES
          These routines are coded in portable C.  The source code for
          the portable version can even be used on computers which do
          not have floating-point arithmetic.  In such a situation,
          functions drand48 and erand48 do not exist; instead, they
          are replaced by the two new functions below.

          long irand48 (m)
          unsigned short m;

          long krand48 (xsubi, m)
          unsigned short xsubi[3], m;

          Functions irand48 and krand48 return non-negative long
          integers uniformly distributed over the interval [0, m-1].

     SEE ALSO
          rand.m

          (printed 07/29/92 - J B Systems)

