/*~!gmatch.c*/
/* Name:  gmatch.c Part No.: _______-____r
 *
 * Copyright 1992 - J B Systems, Morrison, CO
 *
 * The recipient of this product specifically agrees not to distribute,
 * disclose, or disseminate in any way, to any one, nor use for its own
 * benefit, or the benefit of others, any information contained  herein
 * without the expressed written consent of J B Systems.
 *
 *                     RESTRICTED RIGHTS LEGEND
 *
 * Use, duplication, or disclosure by the Government is  subject  to
 * restriction  as  set forth in paragraph (b) (3) (B) of the Rights
 * in Technical Data and Computer Software  Clause  in  DAR  7-104.9
 * (a).
 */

#ident	"@(#)nbclib:gmatch.c	1.1"

gmatch(s, p)
register char	*s, *p;
{
	register char scc;
	char c;

	scc = *s++;
	switch (c = *p++)
	{
	case '[':
		{
			int ok;
			int lc = -1;
			int notflag = 0;

			ok = 0;
			if (*p == '!')
			{
				notflag = 1;
				p++;
			}
			while (c = *p++)
			{
				if (c == ']')
					return(ok ? gmatch(s, p) : 0);
				else if (c == '-' && lc > 0 && *p!= ']')
				{
					if (notflag)
					{
						if ((unsigned char)scc < lc || scc > *(p++))
							ok++;
						else
							return(0);
					}
					else
					{
						if (lc <= (unsigned char)scc && scc <= (*p++))
							ok++;
					}
				}
				else
				{
					if(c == '\\') /* skip to quoted character */
						c = *p++;
					lc = (unsigned char)c;
					if (notflag)
					{
						if (scc && (unsigned char)scc != lc)
							ok++;
						else
							return(0);
					}
					else
					{
						if ((unsigned char)scc == lc)
							ok++;
					}
				}
			}
			return(0);
		}

	case '\\':	
		c = *p++; /* skip to quoted character and see if it matches */
	default:
		if (c != scc)
			return(0);

	case '?':
		return(scc ? gmatch(s, p) : 0);

	case '*':
		while (*p == '*')
			p++;

		if (*p == 0)
			return(1);
		--s;
		while (*s)
		{
			if (gmatch(s++, p))
				return(1);
		}
		return(0);

	case 0:
		return(scc == 0);
	}
}
