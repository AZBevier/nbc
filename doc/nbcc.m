
     Name
          nbcc - Non-Based C Compiler driver

     Syntax
          nbcc [ options ] file [file] [file] [file]

     Description
          The nbcc command invokes the Non-Based C compiler or the
          Fortran compiler.  The compilation tools consist of a
          preprocessor (nbcpp), C compiler (nbccom - C 1 pass version
          or nbcp1/nbcp2 - C 2 pass version), Fortran compiler (fort77),
          assembler (nbcas), and cataloger (nbcat).  The nbcc command
          processes the supplied options and then executes the various
          tools with the proper arguments.  The nbcc command accepts
          several types of files as arguments.

          Files whose names end with .c are taken to be C source programs
          and may be preprocessed, compiled, assembled, and cataloged.
          The compilation process may be stopped after the completion of any
          pass if the appropriate options are supplied.  If the compilation
          process runs through the assembler, then an object program is
          produced and is left in the file whose name is that of the 
          source with .o substituted for .c.  In the same way, files
          whose names end in .s are taken to be assembly source programs
          and may be assembled; files whose names end in .f are taken to
          be Fortran source programs and may be compiler; and files whose
          names end in .i are taken to be preprocessed C source programs
          and may be compiled and assembled.  Files whose names do not
          end in .c, .f, .s, or .i are flagged as errors, and will not
          be processed.

          Since the nbcc command usually creates files in the current
          directory during the compilation process, it is necessary to
          run the nbcc command in a directory in which a file can be
          created.

          If fortran programs are specified (.f files) and the -O option
          is specified, the program "catalog" will be run instead of
          "nbcat" to catalog the specified task.  Normally, catalog can
          just be a copy of nbcat, but may be required to be different.

          The following options are interpreted by nbcc:

          -A[options]
               Pass the specified options to nbcas for processing.
               See the nbcas.m page for available options.

          -BBINDIR
               Pass the "BINDIR" path to nbcc to be used as the
               base directory for the NBC processor files.

          -C   Produce an object file with a .o suffix.  If this
               option is not specified, the assembler or Fortran
               compiler will not produce an object file.

          -Dsymbol
               Pass the defined "symbol" to the C preprocessor.

          -E   Run only nbcpp on the named C programs, and send the
               result to a file with the .i suffix.

          -F   Use IEEE 754 floating point instructions in the assembler
               or Fortran compiler.

          -G   Generate symbol attribute information for the symbolic
               debugger (AID).

          -H   Produce an output file that is pure dsect only.  This is
               the handler option for producing MPX resident code.  Non-
               sectioned code is produced (C only).

          -Idirectory
               Pass the "directory" path to the preprocessor to be
               scanned for include files.

          -J   Delete underscore (_) from being prepended to symbol
               names (C only).

          -Kprefix
               Use the "prefix" to prepend to "lib" and "dir" to
               specify a library and directory file to nbcat.  If
               -Kuser is specified, then "userlib" and "userdir"
               will be search by the nbcat before CLD and CDR.
               Prefix must also specify a pathname if the library
               and directry are not in the current working directory.
               All Fortran libraries must be specified.  There are
               none searched by default.  Multiple libraries can be
               specified, and they will be searched in the order
               specified.  A "prefix" must be specified for this
               option.

          -L[file]
               Pass the specified "file" to the assembler or Fortran
               compiler as the file to use for the listing output.
               If no file is specified, a file with a .l suffix will
               be used.  This may be required if the assembler or
               Fortran compiler generated listing file can not be
               extend enough to hold the listing output.  This option
               is also passed to the C compiler so C source code will
               be passed to the assembler as comment statements.  This
               option also passes a -C to the preprocess so source
               comments are not deleted, and will be passed on to the
               C compiler.

          -Mlibrary
               Pass the specified "library" to the assembler as the
               file to search for macros.  Usually m.mpxmac.

          -N   Do not generate reg-reg floating point instructions.
               This option is for 32/77 and 32/27 machines which only
               have reg-mem floating point instructions.

          -O loadmodule
          -OF loadmodule (fort77 loadmodule)
               Pass the specified "loadmodule" name to nbcat as the
               name of the load module to be built.  Nbcat uses the
               default directives in the file /system/bin/cdirs (C)
               or /system/bin/fdirs (Fortran) to catalog the task.
               The loadmodule name specified on the build or catalog
               directive line will be replaced by the "loadmodule"
               name.  The -R option can be specified to allow use of
               a user defined directive file.  Any .o files specified
               on the command line will be compressed into a temporary
               file to be passed onto nbcat.  Also, any .f, .s or .c
               files specified will first be assembled or compiled
               before compressing into the temporary file.  If a .f
               file is specified, the default directives file is
               changed to fdirs from cdirs.  Also, the program "catalog"
               is used instead of "nbcat" to catalog the task.  If no .f
               file appears on the command line, the 'OF' option can be
               specified to force usage of the fdirs catalog directives
               file and the "catalog" program.  The -T option can be
               used to specify a user defined temporary file to be
               used for the compression if the default file generated
               by nbcc can not be extended enough to hold all of the
               specified object files.

          -Pprefile
               Pass the specified "prefile" to the assembler as the
               first file to be processed.  If multiple source files
               are specified, the "prefile" will be specified for
               each nbcas request.

          -Q[options]
               Pass the specified options to nbcpp for processing.
               See the nbcpp.m man page for available options.

          -Rdirectives
               Pass the specified directives file to nbcat during the
               cataloging process.  The loadmodule name specified on
               build or catalog directive line will be replaced by the
               loadmodule name specified by the -O option. If this option
               is not specified, the default directives in the cdirs
               file will be used.

          -S   Compile, but do not assemble the named C programs, and
               leave the assembler-language output in corresponding
               files suffixed with .z.

          -Ttempfile
               Pass the specified "tempfile" name to nbcas and/or nbcc
               to be used as a temporary file.  Nbcas will use the file
               as the intermediate file during assemble.  Nbcc will use
               the file for the -O option when compressing the specified
               object files for nbcat.  This option may be required if
               the default temporary file can not be extend enough to
               hold the intermediate output or object code.

          -Usymbol
               Pass the undefined "symbol" to the preprocessor.

          -V   Operate nbcc in the verbose mode, echoing commands passed
               to the preprocessor, compiler, and assembler.  Also, the
               current version of nbccom is output.

          -W   Pass the option to the compiler to indicate supression
               of warning messages.

          -X[options]
               Pass the specified options to nbccom for processing.
               See the nbccom.m page for available options.

          -Youtput
               Pass the file name "output" to nbcat to be used as the
               SLO output file.  If the file is not present, it will
               be created.

          -Zcobj
               Pass the file "cobj" that contains compressed object
               code to nbcat during the cataloging process.  If other
               object files are specified with the -O option, "cobj" and
               the specified object files will be compressed together
               into a new temporary file and passed to nbcat.  Care
               must be taken to not specify duplicate object files.

          -1   Have the assembler generate MPX.1X object code.
               No date and time records or program information records
               will be output.

          -2   Invoke the two pass version of the compiler.  Nbcp1 and
               nbcp2 are used instead of nbccom.  This option is used
               when nbccom cannot execute due to limited task space
               or the nbccom runs out of internal table space.

          Other arguments are taken to be program names.  Each program
          name specified will be processed in order, using the options
          specified.  A single nbcc command will process as many files
          as there is room on the command line to specify them.  Usually
          limited to 80 characters unless the TSM "line" command is used
          to set a larger value.  If MAKE4MPX is used, up to 750 chars
          can be passed to nbcc.

     Examples
          nbcc -L -C file.c will produce an object file, file.o and a
          listing file, file.l in the current directory.

          nbcc -L -C file.c -O program -Yfile.map -Rmydirs will produce
          an object file file.o in the current directory and then build
          the loadmodule program using the directives in the mydirs file
          and output the loadmap to file file.map.

          nbcc file.o -O program -Yfile.map -Rmydirs -Kmy will use the
          object file file.o in the current directory to build the
          loadmodule program using the directives in the mydirs file
          and output the loadmap to file file.map.  Mylib and mydir
          will be searched before searching CLB and CDR.

          nbcc -G -C file1.f file2.f -O program -Yfile.map -K^(system)mpx
          will produce object files file1.o and file2.o in the current
          directory and then build the loadmodule program using the default
          directives in the /system/bin/fdirs file and output the loadmap
          to file file.map.  Mpxlib and mpxdir in the system directry on
          the current volume will be searched before searching CLB and CDR.

          nbcc /system/bin/c.srte.o -O program -Yfile.map -Rmydirs
          -Kmy will use the object file c.srte.o in the bin directory
          to build the loadmodule program using the directives in the
          mydirs file and output the loadmap to file file.map.  Mylib
          and mydir will be searched for the main program before searching
          CLB and CDR to resolve other externals.

          nbcc -E -QM file.c file2.c will produce a list of the include
          files used by the programs file.c and file2.c on the standard
          output file.

          nbcc -S file.c will produce an assembler source file file.s in
          the current working directory.

          nbcc -L -P/system/system/mpxpre file.s will produce a listing
          file file.l in the current directory.  No object file will be
          produced.  The prefile, mpxpre in the system directory, will 
          be used during the assemble process.  The prefile could also
          be specified as -P@system(system)mpxpre.

     Files
          file.c                C source file
          file.f                Fortran source file
          file.i                preprocessed C source file
          file.l                Fortran/assembly listing file
          file.o                object file
          file.s                assembly language file
          file.z                generated assembly language file from .c
          TMPDIR/*              temporary files
          BINDIR/catalog        Fortran cataloger
          BINDIR/cdirs          nbcat C task default directives
          BINDIR/fdirs          nbcat Fortran task default directives
          BINDIR/nbcpp          preprocessor
          BINDIR/nbccom         compiler
          BINDIR/nbcp1          first pass of two pass compiler
          BINDIR/nbcp2          second pass of two pass compiler
          BINDIR/nbcas          assembler
          BINDIR/nbcat          C cataloger
          BINDIR/fort77         Fortran compiler

          BINDIR is usually /system/bin or @SYSTEM(BIN)
          TMPDIR is the current working directory

     See Also
          nbcas.m, nbcpp.m, nbccom.m, nbcat.m

     Diagnostics
          The diagnostics produced by the C compiler are sometimes
          cryptic.

     Notes
          The C language standard was extended to allow arbitrary
          length variable names.  The preprocessor and compiler are
          currently set to 128 characters maximum.  However, the
          assembler, and Encore defined object code, only recognize 
          8 characters.  All compiler variables are prepended with
          an "_" if the -J option is not used.  If an external
          definition is not unique in the first 7 (or 8) characters,
          an assembler error will occur.  The assembler will truncate
          arbitrary length variable names.  FORTRAN function names
          are not prepended with an "_".

          Pathnames may be upper/lower case and may by specified in
          MPX format (@VOLUME(DIRECTORY)FILE) or in UNIX format
          (/volume/directory/file).  All pathnames are mapped to
          uppercase and converted to MPX pathnames by the runtime.

          This implementation of the C language uses arithmetic shifts
          when working with variables.  Logical shifts are used for
          unsigned variables.  Many compilers use logical shifts only.
          The user should exercise care when porting code developed
          on other systems.

          (printed 05/03/95 - J B Systems)

