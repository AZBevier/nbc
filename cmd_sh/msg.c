/*~!msg.c*/
/* Name:  msg.c Part No.: _______-____r
 *
 * Copyright 1994 - J B Systems, Morrison, CO
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

#ident	"$Id: msg.c,v 1.1 1995/04/04 22:25:34 jbev Exp $"

/*	$Log $
 */

#include	"defs.h"
#include	"sym.h"

/*
 * error messages
 */
char badopt[]	 = "bad option(s)";
char mailmsg[]	 = "you have mail\n";
char nospace[]	 = "no space";
char nostack[]	 = "no stack space";
char synmsg[]	 = "syntax error";

char badnum[]	 = "bad number";
char badparam[]	 = "parameter null or not set";
char unset[]	 = "parameter not set";
char badsub[]	 = "bad substitution";
char badcreate[] = "cannot create";
char nofork[]	 = "fork failed - too many processes";
char noswap[]	 = "cannot fork: no swap space";
char restricted[] = "restricted";
char piperr[]	 = "cannot make pipe";
char badopen[]	 = "cannot open";
char coredump[]	 = " - core dumped";
char arglist[]	 = "arg list too long";
char txtbsy[]	 = "text busy";
char toobig[]	 = "too big";
char badexec[]	 = "cannot execute";
char notfound[]	 = "not found";
char badfile[]	 = "bad file number";
char badshift[]	 = "cannot shift";
char baddir[]	 = "bad directory";
char badtrap[]	 = "bad trap";
char wtfailed[]	 = "is read only";
char notid[]	 = "is not an identifier";
char badulimit[] = "bad ulimit";
char badreturn[] = "cannot return when not in function";
char badexport[] = "cannot export functions";
char badunset[]  = "cannot unset";
char nohome[]	 = "no home directory";
char badperm[]	 = "execute permission denied";
char longpwd[]	 = "sh error: pwd too long";
char no11trap[]	 = "cannot trap 11";
char argcount[]	 = "argument count";
char neworsemi[] = "newline or ;";
char dotstat[]	 = "pwd: cannot stat .";
char paropen[]	 = "pwd: cannot open ..";
char parstat[]	 = "pwd: cannot stat ..";
char parread[]	 = "pwd: read error in ..";
/*
 * messages for 'builtin' functions
 */
char btest[]	 = "test";
char badop[]	 = "unknown operator ";
char argexp[]	 = "argument expected";
char parexp[]	 = ") expected";
char rbmiss[]	 = "] missing";
/*
 * built in names
 */
char pathname[]	 = "PATH";
char cdpname[]	 = "CDPATH";
char homename[]	 = "HOME";
char mailname[]	 = "MAIL";
char ifsname[]	 = "IFS";
char ps1name[]	 = "PS1";
char ps2name[]	 = "PS2";
char mchkname[]	 = "MAILCHECK";
char acctname[]  = "SHACCT";
char mailpname[] = "MAILPATH";

/*
 * string constants
 */
char nullstr[]	 = "";
char sptbnl[]	 = " \t\n";
#ifdef smpx
char defpath[]	 = ":.:/system/bin:/system/system";
#else
char defpath[]	 = ":/bin:/usr/bin";
#endif
char colon[]	 = ": ";
char minus[]	 = "-";
char endoffile[] = "end of file";
char unexpected[] = " unexpected";
char atline[]	 = " at line ";
#ifdef smpx
char devnull[]	 = "DEV=NULL";
#else
char devnull[]	 = "/dev/null";
#endif
char execpmsg[]	 = "+ ";
char readmsg[]	 = "> ";
char stdprompt[] = "$ ";
char supprompt[] = "# ";
char profile[]	 = ".profile";
char sysprofile[] = "/etc/profile";
char setstr[]	 = "set";
char sicrstr[]	 = "sicr";
char bang[]	 = "!";
char pdstr[]	 = ".";
char dotdot[]	 = "..";
char slstr[]	 = "/";
char eqlstr[]	 = "=";
char neqstr[]	 = "!=";
char lbstr[]	 = "[";
char lpstr[]	 = "(";
char rbstr[]	 = "]";
char rpstr[]	 = ")";
char dasheq[]	 = "-eq";
char dashne[]	 = "-ne";
char dashgt[]	 = "-gt";
char dashlt[]	 = "-lt";
char dashge[]	 = "-ge";
char dashle[]	 = "-le";
char dasha[]	 = "-a";
char dashb[]	 = "-b";
char dashc[]	 = "-c";
char dashd[]	 = "-d";
char dashf[]	 = "-f";
char dashg[]	 = "-g";
char dashk[]	 = "-k";
char dashn[]	 = "-n";
char dasho[]	 = "-o";
char dashp[]	 = "-p";
char dashr[]	 = "-r";
char dashs[]	 = "-s";
char dasht[]	 = "-t";
char dashu[]	 = "-u";
char dashw[]	 = "-w";
char dashx[]	 = "-x";
char dashz[]	 = "-z";
char ptrcolon[]	 = "ptrace: ";
char shell[]	 = "SHELL";
char sfuncstr[]	 = "(){\n";
char efuncstr[]	 = "\n}";
char amperstr[]	 = " &";
char lparstr[]	 = "( ";
char rparstr[]	 = " )";
char pipestr[]	 = " | ";
char andstr[]	 = " && ";
char orstr[]	 = " || ";
char forstr[]	 = "for ";
char instr[]	 = " in";
char dostr[]	 = "\ndo\n";
char donestr[]	 = "\ndone";
char whilestr[]	 = "while ";
char untilstr[]	 = "until ";
char ifstr[]	 = "if ";
char thenstr[]	 = "\nthen\n";
char elsestr[]	 = "\nelse\n";
char fistr[]	 = "\nfi";
char casestr[]	 = "case ";
char dsemistr[]	 = ";;";
char esacstr[]	 = "\nesac";
char fromstr[]	 = "<<";
char toastr[]	 = ">&";
char fromastr[]	 = "<&";
char ontostr[]	 = ">>";
char hashhdr[]	 = "hits\tcost\tcommand\n";
char isbuiltin[] = " is a shell builtin\n";
char isfunct[]	 = " is a function\n";
char efnlstr[]	 = "\n}\n";
char nfstr[]	 = " not found\n";
char ishashed[]	 = " is hashed (";
char rpnlstr[]	 = ")\n";
char isstr[]	 = " is ";
char rdwstr[]	 = "<> ";
char hangup[]	 = "hangup";
char logout[]	 = "logout";
char terminate[] = "terminate";
char timout[]	 = "timeout";

/*
 * tables
 */

struct sysnod reserved[] = 
{
    { "case", 	CASYM	 },
    { "do", 	DOSYM	 },
    { "done", 	ODSYM	 },
    { "elif", 	EFSYM	 },
    { "else", 	ELSYM	 },
    { "esac", 	ESSYM	 },
    { "fi", 	FISYM	 },
    { "for", 	FORSYM	 },
    { "if", 	IFSYM	 },
    { "in", 	INSYM	 },
    { "then", 	THSYM	 },
    { "until", 	UNSYM	 },
    { "while", 	WHSYM	 },
    { "{", 	BRSYM	 },
    { "}", 	KTSYM	 }
};


int no_reserved = 15;

char *sysmsg[] = 
{
    0,
    "Hangup",
    0, 	/* Interrupt */
    "Quit",
    "Illegal instruction",
    "Trace/BPT trap",
    "abort",
    "EMT trap",
    "Floating exception",
    "Killed",
    "Bus error",
    "Memory fault",
    "Bad system call",
    0, 	/* Broken pipe */
    "Alarm call",
    "Terminated",
    "Signal 16",
    "Signal 17",
    "Child death",
    "Power Fail"
};


char export[] = "export";
char duperr[] = "cannot dup";
char readonly[] = "readonly";


struct sysnod commands[] = 
{
    { pdstr, 	SYSDOT	 },
    { ":", 	SYSNULL	 },
    { lbstr, 	SYSTST },
    { "break", 	SYSBREAK },
    { "cd", 	SYSCD	 },
    { "continue", SYSCONT },
    { "echo", 	SYSECHO },
    { "eval", 	SYSEVAL	 },
    { "exec", 	SYSEXEC	 },
    { "exit", 	SYSEXIT	 },
    { export, 	SYSXPORT },
    { "hash", 	SYSHASH	 },
    { "newgrp", SYSNEWGRP },
    { "pwd", 	SYSPWD },
    { "read", 	SYSREAD	 },
    { readonly, SYSRDONLY },
    { "return", SYSRETURN },
    { setstr, 	SYSSET	 },
    { "shift", 	SYSSHFT	 },
    { "test", 	SYSTST },
    { "times", 	SYSTIMES },
    { "trap", 	SYSTRAP	 },
    { "type", 	SYSTYPE },
    { "ulimit", SYSULIMIT },
    { "umask", 	SYSUMASK },
    { "unset", 	SYSUNS },
    { "wait", 	SYSWAIT	 }
};


int no_commands = sizeof commands / sizeof(struct sysnod );

