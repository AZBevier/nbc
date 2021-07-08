
     NAME
          malloc, free, realloc, calloc - main memory allocator

     SYNTAX
          char *malloc (size)
          unsigned size;

          void free (ptr)
          char *ptr;

          char *realloc (ptr, size)
          char *ptr;
          unsigned size;

          char *calloc (nelem, elsize)
          unsigned nelem, elsize;

     DESCRIPTION
          Malloc and free provide a simple general-purpose memory
          allocation package.  Malloc returns a pointer to a block of
          at least size bytes that is doubleword aligned for any use.

          The argument to free is a pointer to a block previously
          allocated by malloc; after free is performed this space is
          made available for further allocation, but its contents are
          left undisturbed.

          Undefined results will occur if the space assigned by malloc
          is overrun or if some random number is handed to free.

          Malloc allocates the first big enough contiguous reach of
          free space found in a circular search from the last block
          allocated or freed, coalescing adjacent free blocks as it
          searches.  It calls sbrk (see brk.m) to get more memory
          from the system when there is no suitable space already
          free.

          Realloc changes the size of the block pointed to by ptr to
          size bytes and returns a pointer to the (possibly moved)
          block.  The contents will be unchanged up to the lesser of
          the new and old sizes.  If no free block of size bytes is
          available in the storage arena, then realloc will ask malloc
          to enlarge the arena by size bytes and will then move the
          data to the new space.

          Realloc also works if ptr points to a block freed since the
          last call of malloc, realloc, or calloc; thus sequences of
          free, malloc and realloc can exploit the search strategy of
          malloc to do storage compaction.

          Calloc allocates space for an array of nelem elements of
          size elsize.  The space is initialized to zeros.

          Each of the allocation routines returns a pointer to space
          suitably aligned (after possible pointer coercion) for
          storage of any type of object.

     SEE ALSO
          brk.m, malloc.m

     DIAGNOSTICS
          Malloc, realloc and calloc return a NULL pointer if there is
          no available memory or if the arena has been detectably
          corrupted by storing outside the bounds of a block.  When
          this happens the block pointed to by ptr may be destroyed.

     NOTE
          Search time increases when many objects have been allocated;
          that is, if a program allocates but never frees, then each
          successive allocation takes longer.

          Space obtained from the system is allocated one map block at
          a time.  If the callers stack is in extended memory, extended
          map blocks are obtained.  If the stack is in non-extended
          memory, non-extended map blocks are obtained.

          MPX-32 1.X allocates map blocks at the end of the currently
          allocated memory.  If the user allocates a memory partition
          in extended memory, the next map block requested by malloc
          will be allocated following the memory partition and not
          contiguous with the previously allocated memory.  This will
          cause malloc to fail.  The user should preallocate and then
          free memory of the anticipated size before including any
          memory partitions.  This will insure contiguous map blocks
          for malloced memory.

          (printed 07/29/92 - J B Systems)

