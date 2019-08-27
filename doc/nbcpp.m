
     Name
          nbcpp - Non-Based C Compiler preprocessor

     Syntax
          /system/bin/nbcpp [ option ... ] [ ifile [ ofile ] ]

     Description
          Nbcpp is the non-based C compiler preprocessor which is
          invoked as the first pass of any C compilation using the
          nbcc command.  The output of nbcpp is designed to be in a
          form acceptable as input to the next pass of the C compiler.
          As the C language has evolved, language specific operation
          of nbcpp has evolved.  The use of nbcpp for other purposes
          is not recommended.  The preferred way to invoke nbcpp is
          through the nbcc command.

          Nbcpp optionally accepts two file names as arguments.  Ifile
          and ofile are respectively the input and output for the
          preprocessor.  They default is to standard input and standard
          output if not supplied.

          The following options are interpreted by nbcpp:

     -C
          By default, nbcpp strips C-style comments.  If the -C
          option is specified, all comments (except those found
          on nbcpp directive lines) are passed along.

     -Dname
     -Dname=def
          Define name as if by a #define directive.  If no =def
          is given, name is defined as 1.

     -F xreffile
          Generate a variable cross reference and output to file
          "xreffile".

     -H or ?
          Print on stderr, a summary list of the options available
          from nbcpp.

     -Idir
          Change the algorithm for searching for #include files
          whose names do not begin with /, @, or ^ to look in dir
          before looking in the directories on the standard list.
          Thus, #include files whose names are enclosed in "" are
          searched for first in the directory of the ifile
          argument, then in directories named in -I options, and
          last in directories on a standard list. For #include
          files whose names are enclosed in <>, the directory of
          the ifile argument is not searched.  See Notes below.

     -M
          Print on stdout, a list of the files included for the
          program being processed.  This option is used to generate
          makefile dependencies.  The file names are output as full
          UNIX pathnames.

     -P
          Preprocess the input without producing the line control
          information used by the next pass of the C compiler.
          Such as: # 12 foo.c

     -R
          Allow macro recursion to occur.

     -T
          Truncate variable names to 8 characters.

     -Uname
          Remove any initial definition of name, where name is a
          reserved symbol that is predefined by the particular
          preprocessor.

     Two special names are understood by nbcpp.  The name __LINE__
     is defined as the current line number (as a decimal integer)
     as known by nbcpp, and __FILE__ is defined as the current file
     name (as a C string) as known by nbcpp. They can be used
     anywhere (including in macros) just as any other defined
     name.

     The following variables are predefined in nbcpp for use on MPX:
          mpx
          gould
          sel
          ON_SEL
          sysv

     All nbcpp directives start with lines begun by #.  The
     directives are:

     #define name token-string
          Replace subsequent instances of name with token-string.

     #define name( arg, ..., arg ) token-string
          Notice that there can be no space between name and the
          (.  Replace subsequent instances of name followed by a
          (, a list of comma separated tokens, and a ) by token-
          string where each occurrence of an arg in the token-
          string is replaced by the corresponding token in the
          comma separated list.

     #undef name
          Cause the definition of name (if any) to be forgotten
          from now on.

     #include ``filename''
     #include <filename>
          Include at this point the contents of filename (which
          will then be run through nbcpp).  When the <filename>
          notation is used, filename is searched for in the
          standard places only.  See the -I option above for more
          detail.

     #line integer-constant ``filename''
          Causes nbcpp to generate line control information for
          the next pass of the C compiler.  Integer-constant is
          the line number of the next line and filename is the file
          where it comes from.  If ``filename'' is not given, the
          current file name is unchanged.

     #endif
          Ends a section of lines begun by a test directive (#if,
          #ifdef, or #ifndef).  Each test directive must have a
          matching #endif.

     #ifdef name
          The following lines appear in the output if name has
          been the subject of a previous #define without being
          the subject of an intervening #undef.

     #ifndef name
          The following lines will not appear in the output if
          name has been the subject of a previous #define without
          being the subject of an intervening #undef.

     #if defined identifier
          May be used in place of the #if directive. If the
          identifier is defined, the directive has a value of 1,
          otherwise 0. This is frequently used for conditional
          environment-specific text.

     #elif constant-expression
          Allows for the conditional compilation of portions of
          the text.  The constant-expression is evaluated and if
          it is not zero, the text immediately following (until
          the next elif, else, endif) is passed to the compiler.

     #if constant-expression
          The following lines appear in the output if constant-
          expression evaluates to non-zero.  All binary non-
          assignment C operators, the ?: operator, the unary -,
          !, and ~ operators are all legal in constant-
          expression.  The precedence of the operators is the
          same as defined by the C language.  There is also a
          unary operator defined, which can be used in constant-
          expression in these two forms: defined ( name ) or
          defined name.  This allows the utility of #ifdef and
          #ifndef in a #if directive.  Only these operators,
          integer constants, and names which are known by nbcpp
          should be used in constant-expression.  In particular,
          the sizeof operator is not available.

     #else
          Reverses the notion of the test directive which matches
          this directive. So if lines previous to this directive
          are ignored, the following lines appear in the output.
          And vice versa.

     The test directives and the possible #else directives can be
     nested.

     Files
          file.c                C source file
          file.i                preprocessed C source file
          BINDIR/nbcpp          preprocessor

          BINDIR is usually /system/bin or @SYSTEM(BIN)

          /system/nbinclude     standard directory for #include files
          /system/cinclude      alternate directory for #include files

     See Also
          nbcas.m, nbcc.m, nbccom.m, nbcat.m

     Diagnostics
          The error messages produced by nbcpp are intended to be self-
          explanatory. The line number and filename where the error
          occurred are printed along with the diagnostic.

     Notes
          When newline characters were found in argument lists for
          macros to be expanded, previous versions of cpp put out the
          newlines as they were found and expanded.  The current
          version of cpp replaces these newlines with blanks to
          alleviate problems that the previous versions had when this
          occurred.

          The C language standard was extended to allow arbitrary
          length variable names.  The preprocessor and compiler are
          currently set to 128 characters maximum.  However, the
          assembler, and Encore defined object code, only recognize 
          the first 8 characters.  The -T option will cause nbcpp to
          recognize the first 8 characters of variables.

          Pathnames may be upper/lower case and may by specified in
          MPX format (@VOLUME(DIRECTORY)FILE) or in UNIX format
          (/volume/directory/file).  All pathnames are mapped to
          uppercase and converted to MPX pathnames by the runtime.

          Include directives of the form <sys/inc.h> normally would
          not be valid in MPX.  This directive has been enhanced to
          drop the "sys/" from the file name and proceed with the
          search for the filename.  This is to allow programs being
          ported from UNIX to be compiled with a minimum of changes.

          (printed 05/31/94 - J B Systems)

