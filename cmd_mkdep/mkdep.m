
     Name
          dodep - Generate makefile dependencies.

     Syntax
          dodep makefile filenames ...

     Description
          dodep adds dependencies to the specified makefile based
          on the file list.  NBCPP is called with the -M option for
          each file specified.  Any existing dependencies are
          deleted before updating the makefile.

     Notes
          Only 768 bytes of filenames can be specified.

          Only files ending in .h, .c, or .s are processed.


          printed (4/29/94 - J B Systems)

