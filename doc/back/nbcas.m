
     Name
          nbcas - Non-Based C Compiler assembler

     Syntax
          nbcas [ options ] file [file] [file] [file]

     Description
          The non-based C compiler assembler (nbcas) is a modified
          version of the MPX assembler.  It processes files output
          by nbccom and generates object files with a .o suffix.

          Since nbcas usually creates files in the current directory
          during the assemble process, it is necessary to run nbcas 
          in a directory in which a file can be created.

          The following options are interpreted by nbcc:

          -A   Produce an object file with auto-sectioning.  This is
               for use with mapped-out MPX 3.5 programs.

          -D   Convert all csect directives to dsect directives.  This
               option is used to produce an output file that is pure 
               dsect.  This is the handler option for producing MPX 
               resident code.

          -E   Generate IEEE instructions.  This is only for RSX machines.

          -G   Generate symbol attribute information for the C source
               level debugger (AID for C).  New pseudo directives are
               processed from the C compiler (NBCCOM).  They are .SRC,
               .XEQ, .SYM, .COM, .STAB, .STABC, .END, and .ARG. 

          -L[file]
               Pass the specified "file" to the assembler as the file
               to use for the listing output.  If no file is specified,
               a file with a .l suffix will be used.  This may be
               required if the assembler generated listing file can
               not be extend enough to hold the listing output. 

          -M'library bloc=no'
               Pass the specified "library" to the assembler as the
               file to search for macros.  Usually m.mpxmac.

          -O[file]
               Produce an object file into the file "file".  This file
               usually has an .o suffix, but can be anything.  If this
               option is not specified, the assembler will not produce
               an object file.

          -Ttempfile
               Pass the specified "tempfile" to the assembler to be
               used as the intermediate temporary file.  This may be
               required if the assembler generated temporary file can
               not be extend enough to hold the intermediate output.

          -X   Generate cross reference file when doing a listing.

          -1   Generate MPX 1.x object code.  This inhibits output
               of date and time information as well as program
               information.

          Other arguments must follow and are taken to be file names.
          Each file name specified will be processed in order and
	  concatinated, generating only one object file.

     Examples
          nbcas -L -O file.s will produce an object file file.o in the
          current directory along with a listing.

          nbcas -L -X /system/mpxpre file.s will produce a listing
          file file.l in the current directory.  No object file will be
          produced.  The prefile, mpxpre in the system directory, will 
          be used during the assemble process.

     Files
          file.l                assembly listing file
          file.o                object file
          file.s                assembly language file
          TMPDIR/*              temporary files
          BINDIR/nbcas          assembler

          BINDIR is usually /system/bin or @SYSTEM(BIN)
          TMPDIR is the current working directory

     See Also
          nbcc.m, nbcpp.m, nbccom.m, nbcat.m

     Diagnostics
          The diagnostics produced by the assembler are sometimes
          cryptic.

     Notes
          The C language standard was extended to allow arbitrary
          length variable names.  The preprocessor and compiler are
          currently set to 128 characters maximum.  However, the
          assembler, and Encore defined object code, only recognize 
          8 characters.  All compiler variables are prepended with
          an "_".  If an external definition is not unique in the 
          first 7 characters, an assembler error will occur.  The
          assembler will truncate arbitrary length variable names.

          Pathnames may be upper/lower case and may by specified in
          MPX format (@VOLUME(DIRECTORY)FILE) or in UNIX format
          (/volume/directory/file).  All pathnames are mapped to
          uppercase and converted to MPX pathnames by the runtime.

          Nbcas now generates the maximum floating point number for
          overflows and zero for underflows instead of giving a
          number error.

          (printed 03/28/95 - J B Systems)

