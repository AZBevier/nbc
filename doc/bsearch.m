
     NAME
          bsearch - binary search a sorted table

     SYNTAX
          #include <search.h>

          char *bsearch ((char *) key, (char *) base, nel, sizeof
          (*key), compar)
          unsigned nel;
          int (*compar)( );

     DESCRIPTION
          Bsearch is a binary search routine generalized from Knuth
          (6.2.1) Algorithm B.  It returns a pointer into a table
          indicating where a datum may be found.  The table must be
          previously sorted in increasing order according to a
          provided comparison function.  Key points to a datum
          instance to be sought in the table.  Base points to the
          element at the base of the table.  Nel is the number of
          elements in the table.  Compar is the name of the comparison
          function, which is called with two arguments that point to
          the elements being compared.  The function must return an
          integer less than, equal to, or greater than zero as
          accordinly the first argument is to be considered less than,
          equal to, or greater than the second.

     EXAMPLE
          The example below searches a table containing pointers to
          nodes consisting of a string and its length.  The table is
          ordered alphabetically on the string in the node pointed to
          by each entry.

          This code fragment reads in strings and either finds the
          corresponding node and prints out the string and its length,
          or prints an error message.

               #include <stdio.h>
               #include <search.h>

               #define   TABSIZE   1000

               struct node {            /* these are stored in the table */
                    char *string;
                    int length;
               };
               struct node table[TABSIZE];   /* table to be searched */
                    .
                    .
                    .
               {
                    struct node *node_ptr, node;
                    int node_compare( );  /* routine to compare 2 nodes */
                    char str_space[20];   /* space to read string into */
                    .
                    .
                    .
                    node.string = str_space;
                    while (scanf("%s", node.string) != EOF) {
                         node_ptr = (struct node *)bsearch((char *)(&node),
                                 (char *)table, TABSIZE,
                                 sizeof(struct node), node_compare);
                         if (node_ptr != NULL) {
                              (void)printf("string = %20s, length = %d\n",
                                   node_ptr->string, node_ptr->length);
                         } else {
                              (void)printf("not found: %s\n", node.string);
                         }
                    }
               }
               /*
                    This routine compares two nodes based on an
                    alphabetical ordering of the string field.
               */
               int
               node_compare(node1, node2)
               struct node *node1, *node2;
               {
                    return strcmp(node1->string, node2->string);
               }

     NOTES
          The pointers to the key and the element at the base of the
          table should be of type pointer-to-element, and cast to type
          pointer-to-character.

          The comparison function need not compare every byte, so
          arbitrary data may be contained in the elements in addition
          to the values being compared.

          Although declared as type pointer-to-character, the value
          returned should be cast into type pointer-to-element.

     SEE ALSO
          hsearch.m, lsearch.m, qsort.m, tsearch.m

     DIAGNOSTICS
          A NULL pointer is returned if the key cannot be found in the
          table.

          (printed 07/29/92)

