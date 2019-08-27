
     NAME
          lsearch - linear search

     SYNTAX
          #include <stdio.h>
          #include <search.h>

          char *lsearch ((char *)key, (char *)base, nelp,
          sizeof(*key), compar)
          unsigned *nelp;
          int (*compar)( );

     DESCRIPTION
          Lsearch is a linear search routine generalized from Knuth
          (6.1) Algorithm S.  It returns a pointer into a table
          indicating where a datum may be found.  If the datum does
          not occur, it is added at the end of the table.  key points
          to the datum to be sought in the table.  base points to the
          first element in the table.  nelp points to an integer
          containing the current number of elements in the table.  The
          integer is incremented if the datum is added to the table.
          compar is the name of the comparison function which the user
          must supply (strcmp, for example).  It is called with two
          arguments that point to the elements being compared.  The
          function must return zero if the elements are equal and
          non-zero otherwise.

     NOTES
          The pointers to the key and the element at the base of the
          table should be of type pointer-to-element, and cast to type
          pointer-to-character.

          The comparison function need not compare every byte, so
          arbitrary data may be contained in the elements in addition
          to the values being compared.

          Although declared as type pointer-to-character, the value
          returned should be cast into type pointer-to-element.

     EXAMPLE
          This fragment will read in < TABSIZE strings of length <
          ELSIZE and store them in a table, eliminating duplicates.

               #include <stdio.h>
               #include <search.h>

               #define TABSIZE 50
               #define ELSIZE 120

                    char line[ELSIZE], tab[TABSIZE][ELSIZE], *lsearch( );
                    unsigned nel = 0;
                    int strcmp( );
                    . . .
                    while (fgets(line, ELSIZE, stdin) != NULL &&
                       nel < TABSIZE)
                         (void) lsearch(line, (char *)tab, &nel,
                                ELSIZE, strcmp);
                    . . .

     SEE ALSO
          bsearch.m, hsearch.m, tsearch.m.

     DIAGNOSTICS
          If the searched for datum is found, lsearch returns a
          pointer to it.  Otherwise, lsearch returns a pointer to
          the newly added element.

     SPECIAL CONSIDERATIONS
          Undefined results can occur if there is not enough room in
          the table to add a new item.

          (printed 07/29/92 - J B Systems)

