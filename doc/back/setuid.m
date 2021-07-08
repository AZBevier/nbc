
     NAME
          setuid, setgid - set user and group IDs

     SYNTAX
          int setuid (uid)
          int uid;

          int setgid (gid)
          int gid;

     DESCRIPTION
          These services are not supported by MPX.  They will always
          return a value of zero.

          Setuid (setgid) is used to set the real user (group) ID and
          effective user (group) ID of the calling process.

          If the effective user ID of the calling process is super-
          user, the real user (group) ID , effective user (group) ID
          and the saved set-user ID are set to uid (gid).

          If the effective user ID of the calling process is not
          super-user, but its real user (group) ID is equal to uid
          (gid), the effective user (group) ID is set to uid (gid).

          If the effective user ID of the calling process is not
          super-user, but the saved set-user (group) ID from exec(2)
          is equal to uid (gid), the effective user (group) ID is set
          to uid (gid).

          Setuid (setgid) will fail if the real user (group) ID of the
          calling process is not equal to uid (gid) and its effective
          user ID is not super-user.  [EPERM]

          The uid is out of range.  [EINVAL]

     RETURN VALUE
          Upon successful completion, a value of 0 is returned.
          Otherwise, a value of -1 is returned and errno is set to
          indicate the error.

     SEE ALSO
          getuid.m

          (printed 07/30/92 - J B Systems)

