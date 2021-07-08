
     NAME
          qsort - quicker sort

     SYNTAX
          void qsort ((char *) base, nel, sizeof (*base), compar)
          unsigned nel;
          int (*compar)( );

     DESCRIPTION
          Qsort is an implementation of the quicker-sort algorithm.
          It sorts a table of data in place.

          Base points to the element at the base of the table.  Nel is
          the number of elements in the table.  Compar is the name of
          the comparison function, which is called with two arguments
          that point to the elements being compared.  As the function
          must return an integer less than, equal to, or greater than
          zero, so must the first argument to be considered be less
          than, equal to, or greater than the second.

     NOTES
          The pointer to the base of the table should be of type
          pointer-to-element, and cast to type pointer-to-character.
          The comparison function need not compare every byte, so
          arbitrary data may be contained in the elements in addition
          to the values being compared.

          The order in the output of two items which compare as equal
          is unpredictable.

     SEE ALSO
          sort.m, bsearch.m, lsearch.m, string.m

          (printed 07/29/92)

