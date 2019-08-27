
     Name
          moelib/moedir - Mapped out/ieee/sectioned library for MPX

     Syntax
          -K/system/bin/moe option to nbcc
          -K/system/bin/e option to nbcc for rest of library

     Description
          The mapped out/ieee library for MPX contains modified
          versions of those provided with the non-based C compiler.
          By using the -Kmoe option to nbcc when building a C task,
          the mapped out/ieee versions will be selected before the
          standard versions.  Using this library allows a C task to
          be built that will run in unmapped mode, be sectioned, and
          use ieee floating point.  The ENVIRONMENT directive for nbcat
          must specify the MAPOUT keyword to direct NBCAT to build
          a mapped out task.  A sample directives file, modirs, is
          provided, which is a modified version of cdirs.

          If c.srt.o or c.srte.o are included explicitly as part of
          the file list to NBCC, these must be changed to reflect
          usage of the mapped out versions.  Change the normal pathname
          of "/system/bin/c.srte.o" to "/system/moelib/c.srte.o".

     Files
          c.srt.s               Non extended startup code.
          c.srte.s              Extended startup code.
          ctscan.c              Command line scanner.
          exec.c                Functions for parameter task activation.
          getcwvd.c             Get current working volume and directory.
          getpid.c              Get process I.D..
          makefile.moe          Makefile for making moelib/moedir.
          moedir                Mapped out/ieee MPX directory file.
          modirs                Catalog directives for mapped out tasks.
          moelib                Mapped out/ieee MPX library file.
          mpxini.c              C environment initialization code.
          pnpars.s              Parse command line parameters into RRS's.
          prefile               Prefile for assembling .s files.
          unixio.c              Unix I/O emulation functions for MPX.
          unixio.h              Header file for unixio.c

     See Also
          nbcas.m, nbcat.m, nbcc.m, nbccom.m, molib.m, ieeelib.m

     Notes
          The functions defined in the moelib cannot replace the standard
          versions in clb/cdr.  The functions are a different object type,
          and nbcat with abort with an error saying that sectioned and
          non-sectioned object code is being mixed.

          (printed 05/03/95 - J B Systems)
