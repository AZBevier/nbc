
     NAME
          mktemp - make a unique file name

     SYNTAX
          char *mktemp (template)
          char *template;

     DESCRIPTION
          Mktemp replaces the contents of the string pointed to by
          template by a unique file name, and returns the address of
          template.  The string in template should look like a file
          name with six trailing Xs; mktemp will replace the Xs with a
          letter and the current task number.  The letter will be
          chosen so that the resulting name does not duplicate an
          existing file.

     SEE ALSO
          getpid.m, tmpfile.m, tmpnam.m

     SPECIAL CONSIDERATIONS
          It is possible to run out of letters.

          (printed 07/29/92 - J B Systems)

