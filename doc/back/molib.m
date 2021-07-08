
     Name
          molib/modir - Mapped out library for MPX

     Syntax
          -K/system/bin/mo option to nbcc

     Description
          The mapped out library for MPX contain modified versions of
          those provided with the non-based C compiler.  By using
          the -Kmo option to nbcc when building a C task, the mapped
          out versions will be selected before the standard versions.
          Using this library allows a C task to be built that will
          run in unmapped mode.  The ENVIRONMENT directive for nbcat
          must specify the MAPOUT keyword to direct NBCAT to build
          a mapped out task.  A sample directives file, modirs, is
          provided, which is a modified version of cdirs.

          If c.srt.o or c.srte.o are included explicitly as part of
          the file list to NBCC, these must be changed to reflect
          usage of the mapped out versions.  Change the normal pathname
          of "/system/bin/c.srte.o" to "/system/molib/c.srte.o".

     Files
          c.srt.s               Non extended startup code.
          c.srte.s              Extended startup code.
          ctscan.c              Command line scanner.
          exec.c                Functions for parameter task activation.
          getcwvd.c             Get current working volume and directory.
          getpid.c              Get process I.D..
          makefile              Makefile for making molib/modir.
          modir                 Mapped out MPX directory file.
          modirs                Catalog directives for mapped out tasks.
          molib                 Mapped out MPX library file.
          mpxini.c              C environment initialization code.
          pnpars.s              Parse command line parameters into RRS's.
          prefile               Prefile for assembling .s files.
          unixio.c              Unix I/O emulation functions for MPX.
          unixio.h              Header file for unixio.c

     See Also
          nbcas.m, nbcat.m, nbcc.m, nbccom.m

     Notes
          The functions defined in the molib can replace the standard
          versions in clb/cdr.  The functions will operate equally
          well in mapped out and non-mapped out modes.

          (printed 05/03/95 - J B Systems)
