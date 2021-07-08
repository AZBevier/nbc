
     Name
          /system/bin/nbccom - Non-Based C Compiler
          /system/bin/nbcp1 - pass one of the two pass Non-Based C Compiler
          /system/bin/nbcp2 - pass two of the two pass Non-Based C Compiler

     Syntax
          nbccom [ -Xoptions ] [ -X2options ] file.i file.z -Xl -XF file
          or
          nbcp1 [ -Xoptions ] file.i file.a -Xl -XF file
          nbcp2 [ -X2options ] file.a file.z -X2l

     Description
          The nbcc command invokes the Non-Based C compiler.  The file
          names and options are passed to the compiler by nbcc.  Nbccom
          may optionally be involked manually.  The first file specified
          is the input file.  This is usually the output file from the
          C preprocessor.  The second file specified is the output file.
          This is the file that will be passed to the assembler.

          Options that are to be specified for pass one must be preceeded
          by a "-X" and options for pass two must be preceeded by a "-X2".
          The following options are interpreted by nbccom, nbcp1, or
          nbcp2:

          -Xl
               Keep listing information for assembler output.

          -Xr
               Display current release information.

          -XF name
               Provide file name to be used for program statement.
               If none is specified, it will default to main.

          -XH
               Compile an MPX handler, no CSECT statements will be
               generated, i.e., all DSECT.

          -XJ
               Do not prepend "_" to variable names.

          -XR
               Don't generate inline code for builtin functions for
               LCB, LCH, LCW, LCD, STCB, STCH, STCW, STCD, and LCRA.
               Allow the user to define these functions.

          -XTDnum
               Change default dimension table size to num entries.

          -XTSnum
               Change default symbol table size to num entries.

          -XTTnum
               Change default tree table size to num entries.

          -X2l
               Keep listing information for assembler output.

          -X2H
               Compile an MPX handler, no CSECT statements will be
               generated, i.e., all DSECT.

          -X2J
               Do not prepend "_" to variable names.

          -X2N
               Do not use reg-reg floating point instructions.  Use
               reg-mem floating point instructions and function calls
               for number conversions.

          -X2TTnum
               Change default tree table size to num entries.

          -X2W
               Shut up any warning messages.

          Some options are specified as lower case.  The option lower
          command to TSM must be set to pass lower case characters on
          the command line. Other arguments are taken to be input and
          output file names.

     Files
          file.a                intermediate output file
          file.c                C source file
          file.i                preprocessed C source file
          file.z                generated assembly language file
          BINDIR/nbccom         combined version of compiler
          BINDIR/nbcp1          first pass of two pass compiler
          BINDIR/nbcp2          second pass of two pass compiler

          BINDIR is usually /system/bin or @SYSTEM(BIN)

     See Also
          nbcas.m, nbcpp.m, nbcc.m, nbcat.m

     Diagnostics
          The diagnostics produced by the C compiler are sometimes
          cryptic.

     Notes
          The C language standard was extended to allow arbitrary
          length variable names.  The preprocessor and compiler are
          currently set to 128 characters maximum.  However, the
          assembler, and Encore defined object code, only recognize 
          8 characters.  All compiler variables are prepended with
          an "_" unless the -J option is specified to NBCC.  If an
          external definition is not unique in the first 7 characters,
          an assembler error will occur.  The assembler will truncate
          arbitrary length variable names.  FORTRAN function names
          are not prepended with an "_".

          Pathnames may be upper/lower case and may by specified in
          MPX format (@VOLUME(DIRECTORY)FILE) or in UNIX format
          (/volume/directory/file).  All pathnames are mapped to
          uppercase and converted to MPX pathnames by the runtime.

          (printed 03/28/95 - J B Systems)

