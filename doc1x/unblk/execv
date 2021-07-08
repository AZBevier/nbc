
     NAME
          execl, execv, execle, execve, execlp, execvp, vexecv,
          vexecl - execute a file

     SYNTAX
          int vexecl (path, arg0, arg1, ..., argn, 0)
          char *path, *arg0, *arg1, ..., *argn;

          int vexecv (path, argv)
          char *path, *argv[ ];

          int execl (path, arg0, arg1, ..., argn, 0)
          char *path, *arg0, *arg1, ..., *argn;

          int execv (path, argv)
          char *path, *argv[ ];

          int execle (path, arg0, arg1, ..., argn, 0, envp)
          char *path, *arg0, *arg1, ..., *argn, *envp[ ];

          int execve (path, argv, envp)
          char *path, *argv[ ], *envp[ ];

          int execlp (file, arg0, arg1, ..., argn, 0)
          char *file, *arg0, *arg1, ..., *argn;

          int execvp (file, argv)
          char *file, *argv[ ];

     DESCRIPTION
          Exec in all its forms is not supported by MPX.  Errno is
          set to EFAULT and a -1 is returned.  

          MPX supports two new services vexecl and vexecv to emulate
          the UNIX execl and execv services.  The run request MPX
          service is used.  These new services are like the BSD vfork
          services.  An environment is passed to the run requested
          task to define the default TTY assignment and the TZ
          variable.  If specified, a command line buffer is also
          passed to the requested task.  The run request is issued
          in wait mode.  The calling task must wait for completion
          of the called task.

          When a C program is executed, it is called as follows:

               main (argc, argv, envp)
               int argc;
               char **argv, **envp;

          where argc is the argument count and argv is an array of
          character pointers to the arguments themselves.  As
          indicated, argc is conventionally at least one and the first
          member of the array points to a string containing the name
          of the file.

          Path points to a path name that identifies the new process
          file.

          Arg0, arg1, ..., argn are pointers to null-terminated
          character strings.  These strings constitute the argument
          list available to the new process.  By convention, at least
          arg0 must be present and point to a string that is the same
          as path (or its last component).

          Argv is an array of character pointers to null-terminated
          strings.  These strings constitute the argument list
          available to the new process.  By convention, argv must have
          at least one member, and it must point to a string that is
          the same as path (or its last component).  Argv is
          terminated by a null pointer.

          Envp is an array of character pointers to null-terminated
          strings.  These strings constitute the environment for the
          new process.  Envp is terminated by a null pointer.  For
          vexecl and vexecv, the C run-time start-off routine places
          a pointer to the environment of the calling process in the
          global cell:
               extern char **environ;
          and it is used to pass the environment of the calling
          process to the new process.

          Exec will fail and return to the calling process if one or
          more of the following are true:

          [ENOENT]       One or more components of the new process
                         path name of the file do not exist.

          [ENOTDIR]      A component of the new process path of the
                         file prefix is not a directory.

          [EACCES]       Search permission is denied for a directory
                         listed in the new process file's path prefix.

          [EACCES]       The new process file is not an ordinary file.

          [EACCES]       The new process file mode denies execution
                         permission.

          [ENOEXEC]      The requested environment and parameters 
                         exceed 768 characters or the requested file
                         is not an executable load module.

          [ENOMEM]       The new process requires more memory than is
                         allowed by the system-imposed maximum.

          [EFAULT]       The new process file is not as long as
                         indicated by the size values in its header.

          [EFAULT]       Path, argv, or envp point to an illegal
                         address.

     RETURN VALUE
          Exec returns to the calling program upon completion of the
          service, the requested task aborts, or there is an error.
          A zero is returned for sucessful completion of the requested
          task.  A one is returned if the requested tasks aborts.  If
          any other error occurs, the return value will be -1 and errno
          will be set to indicate the error.

     SEE ALSO
          alarm.m, exit.m, fork.m, nice.m, signal.m

          (printed 08/03/92 - J B Systems)

