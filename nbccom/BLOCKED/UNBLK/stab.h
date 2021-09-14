/*~!stab.h*/
 
/* for compatibility with berkeley unix, which has sdb symbols */
/* in this file.  Our sdb symbols are defined in a.out.h       */
/* Below are symbols defined in berkeley but not in v32.       */
#define N_FNAME  0x22
#define N_LCSYM  0x28
#define N_ENTRY  0xa4
#define N_BCOMM  0xe2
#define N_ECOMM  0xe4
#define N_ECOML  0xe8
