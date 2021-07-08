
     NAME
          hsearch, hcreate, hdestroy - manage hash search tables

     SYNTAX
          #include <search.h>

          ENTRY *hsearch (item, action)
          ENTRY item;
          ACTION action;

          int hcreate (nel)
          unsigned nel;

          void hdestroy ( )

     DESCRIPTION
          Hsearch is a hash-table search routine generalized from
          Knuth (6.4) Algorithm D.  It returns a pointer into a hash
          table indicating the location at which an entry can be
          found.  Item is a structure of type ENTRY (defined in the
          <search.h> header file) containing two pointers: item.key
          points to the comparison key, and item.data points to any
          other data to be associated with that key.  (Pointers to
          types other than character should be cast to pointer-to-
          character.) Action is a member of an enumeration type ACTION
          indicating the disposition of the entry if it cannot be
          found in the table.  ENTER indicates that the item should be
          inserted in the table at an appropriate point.  FIND
          indicates that no entry should be made.  Unsuccessful
          resolution is indicated by the return of a NULL pointer.

          Hcreate allocates sufficient space for the table, and must
          be called before hsearch is used.  Nel is an estimate of the
          maximum number of entries that the table will contain.  This
          number may be adjusted upward by the algorithm in order to
          obtain certain mathematically favorable circumstances.

          Hdestroy destroys the search table, and may be followed by
          another call to hcreate.

     NOTES
          Hsearch uses open addressing with a multiplicative hash
          function.  However, its source code has many other options
          available which the user may select by compiling the hsearch
          source with the following symbols defined to the
          preprocessor:

               DIV      Use the remainder modulo table size as the
                        hash function instead of the multiplicative
                        algorithm.

               USCR     Use a User Supplied Comparison Routine for
                        ascertaining table membership.  The routine
                        should be named hcompar and should behave in a
                        manner similar to strcmp (refer to string.m).

               CHAINED  Use a linked list to resolve collisions.  If
                        this option is selected, the following other
                        options become available.

                        START     Place new entries at the beginning
                                  of the linked list (default is at
                                  the end).

                        SORTUP    Keep the linked list sorted by key
                                  in ascending order.

                        SORTDOWN  Keep the linked list sorted by key
                                  in descending order.

          Additionally, there are preprocessor flags for obtaining
          debugging printout (-DDEBUG) and for including a test driver
          in the calling routine (-DDRIVER).  Consult the source code
          for further details.

     EXAMPLE
          The following example reads in strings followed by two
          numbers and stores them in a hash table, discarding
          duplicates.  It then reads in strings, finds the matching
          entry in the hash table, and prints it out.

               #include <stdio.h>
               #include <search.h>

               struct info {       /* this is the info stored in the table */
                    int age, room; /* other than the key. */
               };
               #define NUM_EMPL    5000    /* # of elements in search table */

               main( )
               {
                    /* space to store strings */
                    char string_space[NUM_EMPL*20];
                    /* space to store employee info */
                    struct info info_space[NUM_EMPL];
                    /* next avail space in string_space */
                    char *str_ptr = string_space;
                    /* next avail space in info_space */
                    struct info *info_ptr = info_space;
                    ENTRY item, *found_item, *hsearch( );
                    /* name to look for in table */
                    char name_to_find[30];
                    int i = 0;

                    /* create table */
                    (void) hcreate(NUM_EMPL);
                    while (scanf("%s%d%d", str_ptr, &info_ptr->age,
                           &info_ptr->room) != EOF && i++ < NUM_EMPL) {
                         /* put info in structure, and structure in item */
                         item.key = str_ptr;
                         item.data = (char *)info_ptr;
                         str_ptr += strlen(str_ptr) + 1;
                         info_ptr++;
                         /* put item into table */
                         (void) hsearch(item, ENTER);
                    }

                    /* access table */
                    item.key = name_to_find;
                    while (scanf("%s", item.key) != EOF) {
                        if ((found_item = hsearch(item, FIND)) != NULL) {
                         /* if item is in the table */
                         (void)printf("found %s, age = %d, room = %d\n",
                              found_item->key,
                              ((struct info *)found_item->data)->age,
                              ((struct info *)found_item->data)->room);
                        } else {
                         (void)printf("no such employee %s\n",
                              name_to_find)
                        }
                    }
               }

     SEE ALSO
          bsearch.m, lsearch.m, malloc.m, string.m, tsearch.m

     DIAGNOSTICS
          Hsearch returns a NULL pointer if either the action is FIND
          and the item could not be found or the action is ENTER and
          the table is full.

          Hcreate returns zero if it cannot allocate sufficient space
          for the table.

     WARNING
          Hsearch and hcreate use malloc() to allocate space.

     SPECIAL CONSIDERATIONS
          Only one hash search table may be active at any given time.

          (printed 07/29/92 - J B Systems)

