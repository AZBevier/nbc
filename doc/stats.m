
     NAME
          stat - data returned by stat system call

     SYNTAX
          #include <sys/types.h>
          #include <sys/stat.h>

     DESCRIPTION
          The system calls stat and fstat return data whose structure
          is defined by this include file.  The encoding of the field
          st_mode is defined in this file also.

          /*
           * Structure of the result of stat
           */

          struct    stat
          {
               dev_t     st_dev;        /* ID of device containing the directory entry */
               ino_t     st_ino;        /* inode number */
               ushort    st_mode;       /* file mode */
               short     st_nlink;      /* number of links */
               ushort    st_uid;        /* user ID of the file's owner */
               ushort    st_gid;        /* group ID of the file's group */
               dev_t     st_rdev;       /* ID of device (block and char devices only) */
               off_t     st_size;       /* file size in bytes */
               time_t    st_atime;      /* time of last access */
               time_t    st_mtime;      /* time of last data modification */
               time_t    st_ctime;      /* time of last file status change */
               long      st_blksize;    /* size of the disk blocks */
               long      st_blocks;     /* number of disk blocks */
          };

          #define   S_IFMT    0170000   /* type of file */
          #define   S_IFIFO   0010000   /* fifo */
          #define   S_IFCHR   0020000   /* character special */
          #define   S_IFDIR   0040000   /* directory */
          #define   S_IFBLK   0060000   /* block special */
          #define   S_IFREG   0100000   /* regular */
          #define   S_ISUID   04000     /* set user ID on execution */
          #define   S_ISGID   02000     /* set group ID on execution */
          #define   S_ISVTX   01000     /* save swapped text even after use */
          #define   S_IREAD   00400     /* read permission, owner */
          #define   S_IWRITE  00200     /* write permission, owner */
          #define   S_IEXEC   00100     /* execute/search permission, owner */

     FILES
          <sys/types.h>
          <sys/stat.h>

     SEE ALSO
          stat.h, types.m

          (printed 07/30/92 - J B Systems)

