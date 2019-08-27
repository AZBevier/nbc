
     NAME
          brk, sbrk - change data segment space allocation

     SYNTAX
          int brk (endds)
          char *endds;

          char *sbrk (incr)
          int incr;

     DESCRIPTION
          Brk and sbrk are used to change dynamically the amount of
          space allocated for the calling process's data segment.
          The change is made by resetting the process's break value
          and allocating the appropriate amount of space. The break
          value is the address of the first location beyond the end
          of the data segment or if in extended memory, the first
          location in extended memory.  The amount of allocated space
          increases as the break value increases.  The newly allocated
          space is set to zero.

          Brk sets the break value to endds and changes the allocated
          space accordingly.

          Sbrk adds incr bytes to the break value and changes the
          allocated space accordingly.  Incr can be negative, in which
          case the amount of allocated space is decreased.

          Brk and sbrk will fail without making any change in the
          allocated space if one or more of the following are true:

               Such a change would result in more space being
               allocated than is allowed by a system-imposed maximum
               [ENOMEM]

     RETURN VALUE
          Upon successful completion, brk returns a value of 0 and
          sbrk returns the old break value.  Otherwise, a value of -1
          is returned and errno is set to indicate the error.

     SPECIAL CONSIDERATIONS
          Map blocks are allocated in the address space of the stack.
          If the stack is in extended memory, extended map blocks are
          allocated (deallocated).  If the stack is in non-extended
          memory, non-extended map blocks are allocated (deallocated).

          (printed 07/30/92 - J B Systems)

