* "oscode.c" @(#)J B Systems Non-Base C Compiler - Fri Aug 13 15:57:52 MDT 1993
*	
	program	oscode
	list	mac,nong,nodata
*
r0	equ	0
r1	equ	1
r2	equ	2
r3	equ	3
r4	equ	4
r5	equ	5
r6	equ	6
r7	equ	7
sp	equ	3
*
	dsect
	dsect
	dsect
* asm ("hat dataw 1");
hat dataw 1
* asm (" acw sg.ini");
 acw sg.ini
* struct  hc {
*     struct  hc*     sf;
*     struct  hc*     sb;
*     char    pri;
*     char    cnt;
*     short   fill;
* };
* struct c {
*     char    date[8];
*     char    cent;
*     char    year;
*     char    month;
*     char    day;
*     int     intc;
*     int     time[2];
*     char    lodc[8];
*     char    symtab[8];
*     char    podc[8];
*     int     sbuf[2];
*     char    sidv[8];
*     short   tmac;
*     short   emac;
*     short   hmac;
*     short   smac;
*     short   tmcc;
*     short   emcc;
*     short   hmcc;
*     short   smcc;
*     char    system[8];
*     char    sypath[16];
*     char    pchfle[8];
*     int     trace[2];
*     char    dbglm[8];
*     int     sprdw[6];
*     char    hlpvol[16];
*     char    hlpdir[16];
*     struct hc cipu;
*     struct hc ripu;
*     struct hc free;
*     struct hc prea;
*     struct hc curr;
*     struct hc sqrt;
*     struct hc sq55;
*     struct hc sq56;
*     struct hc sq57;
*     struct hc sq58;
*     struct hc sq59;
*     struct hc sq60;
*     struct hc sq61;
*     struct hc sq62;
*     struct hc sq63;
*     struct hc sq64;
*     struct hc swti;
*     struct hc swio;
*     struct hc swsm;
*     struct hc swsr;
*     struct hc swlo;
*     struct hc susp;
*     struct hc runw;
*     struct hc hold;
*     struct hc anyw;
*     struct hc swdc;
*     struct hc swdv;
*     struct hc swfi;
*     struct hc mrq;
*     struct hc swmp;
*     struct hc swgq;
*     int     spch[21];
*     int*    tsad;
*     int     actseq;
*     int*    adat;
*     int     bit[2];
*     int*    cdta;
*     char    cup;
*     char    bup;
*     char    iop;
*     char    us;
*     int*    dque;
*     int*    dtta;
*     int     fadr;
*     int     fgonr;
*     int     gint;
*     int     idla;
*     int     idlc;
*     int*    itlt;
*     int     batseq;
*     int     jobn;
*     int     mgran;
*     short*  midl;
*     int*    miop;
*     int**   modd;
*     int*    mpl;
*     char    msd;
*     unsigned midla:24;
*     int     mtim;
*     int     ntim;
*     int*    patch;
*     int*    pool;
*     int     sgos;
*     int*    sictd;
*     int*    smta;
*     int*    arta;
*     int*    spad;
*     int*    svta;
*     int*    svta2;
*     int     swap;
*     int     sycs;
*     int     tskn;
*     int*    tsmdqa;
*     int     ttbt[8];
*     int*    udta;
*     int*    ttab;
*     int*    mata;
*     int*    mpaa;
*     int*    mpac;
*     int*    mpah;
*     int*    rmta;
*     int*    emta;
*     int     rev;
*     int*    debug;
*     int     tdq1;
*     int     tdq2;
*     int     tdq3;
*     int*    regs;
*     int*    mvta;
*     int*    acta;
*     int*    seqa;
*     int*    scdipu;
*     int*    chta;
*     int*    etloc;
*     int     admask;
*     int     idla1;
*     int     idlc1;
*     int*    ipuit1;
*     int*    ipuit2;
*     int     btime;
*     int     bdate;
*     int     tcorr;
*     int*    fssp;
*     int     dptimo;
*     int*    mdta;
*     int*    mdte;
*     int     swplim;
*     int*    pdqe;
*     int     mpxbr[8];
*     int     mpxbrd;
*     int*    ip00;
*     int     psdbre[2];
*     int     psdbrx[2];
*     int     psdmse[2];
*     int     psdmsx[2];
*     int     psdeae[2];
*     int     psdeax[2];
*     int*    dsect;
*     int*    adapt;
*     int*    tdefa;
*     int*    swiocl;
*     int*    crdump;
*     int*    hstadr;
*     short   cdtn;
*     short   itrs;
*     short   smvti;
*     short   svtn;
*     short   udtn;
*     short   rmtm;
*     short   emtm;
*     short   nos;
*     short   nrst;
*     short   mvtn;
*     short   artn;
*     short   chtn;
*     short   himap;
*     short   svct2;
*     short   mdtn;
*     short   mdtav;
*     int     rms[2];
*     int     gslemc;
*     int*    ptrint;
*     char    bdbug[8];
*     int*    pet;
*     struct hc tsmir;
*     struct hc tsmia;
*     int     sbufa[2];
*     int     sbufb[2];
*     int*    ipuae;
*     int*    hlpdqa;
*     short   sprh[8];
*     short   dptry;
*     short   smaps;
*     char    bpri;
*     char    dttn;
*     char    fsflgs;
*     char    modn;
*     char    niti;
*     char    nque;
*     char    rrun;
*     char    smtn;
*     char    tsmcnt;
*     char    tsmpri;
*     char    tsmtot;
*     char    tent;
*     char    rmtl;
*     char    emtl;
*     char    conf;
*     char    mach;
*     char    actn;
*     char    dbtlc;
*     char    smts;
*     char    seqn;
*     int*    ipuhis;
*     int     shrhi;
*     char    maxswp;
*     char    nload2;
*     char    pdpend;
*     char    spb1[9];
*     char    mmsg;
*     char    mrun;
*     char    mnwi;
*     char    gslegi;
*     char    gslepr;
*     char    adafl;
*     char    tkill;
*     char    delta;
*     char    mpxbrn;
*     char    dbmaps;
*     short   swapsz;
*     int     dtsave;
*     int     shcpu;
*     int     shipu;
*     int     updt;
*     int     swpbuf;
*     int     mrqtmr;
*     int     spare;
*     int*    tables;
*     int*    user;
* };
* struct adat {
*     struct dqe ** dqe;
* };
* struct  dqe {
*         struct dqe* sf;
*         struct dqe* sb;
*         char    cup;
*         char    bup;
*         char    iop;
*         char    us;
*         int     tan;
*         union   {
*         double  on;
*         char    onb[8];
*         }onu;
*         double  lmn;
*         double  psn;
*         int     usw;
*         int     ushf;
*         int*    msd;
*         int     dctr;
*         char    mmsg;
*         char    mrun;
*         char    mnwi;
*         char    cqfn;
*         char    uf2;
*         char    ipuf;
*         char    nwio;
*         char    sopo;
*         int     cqc;
*         char    sh;
*         char    shf;
*         char    tifc;
*         char    rilt;
*         int     uts1;
*         int     uts2;
*         int     dsw;
*         int     prs;
*         int     prm;
*         char    freeb1;
*         char    tskf;
*         char    mspn;
*         char    mst;
*         int*    pssf;
*         int*    pssb;
*         char    pspr;
*         char    psct;
*         char    iln;
*         char    resu;
*         int*    tisf;
*         int*    tisb;
*         char    tipr;
*         char    tict;
*         char    swif;
*         char    ubio;
*         int*    rrsf;
*         int*    rrsb;
*         char    rrpr;
*         char    rrct;
*         short   nsct;
*         int*    mrsf;
*         int*    mrsb;
*         char    mrpr;
*         char    mrct;
*         char    nwrr;
*         char    nwmr;
*         char    rti;
*         char    nwlm;
*         char    ati;
*         char    freeb2;
*         int     tad;
*         int     abc[3];
*         int     tsap;
*         int     srid[2];
*         int     cdir[8];
*         char    gid;
*         char    fb3[3];
*         int     acx2;
*         char    mrq;
*         char    mem;
*         short   memr;
*         char    mrt;
*         char    fb4;
*         short   rmmr;
*         short   mapn;
*         short   cme;
*         short   cmh;
*         short   cms;
*  };
* struct stkfrm {
*     int     reg[8];
*     int     psd[2];
*     int     scrpas[22];
* };
* struct cxtfrm {
*     int     reg[8];
*     int     psd[2];
* };
* struct tsa {
*     struct stkfrm stf[11];
*     struct cxtfrm cxf;
*     char    prjct[8];
*     int     pgow;
*     int     parent;
*     struct stkfrm* regp;
*     int     *fssp;
*     int     contxt[18];
*     int     free[4];
*     int     used[4];
*     int*    first;
*     int*    last;
*     int     itac;
*     int*    basep;
*     int     bfcb[16];
*     int     prot[8];
*     int     bregs[8];
*     int     mpp[8];
*     int*    dbhat;
*     struct dqe *prno;
*     int*    abrta;
*     int*    bbufa;
*     int*    vata;
*     char    vatn;
*     char    wscr;
*     char    segn;
*     char    bit3;
*     int*    fata;
*     int*    fpta;
*     int*    sega;
*     int*    brka;
*     int*    msgr;
*     int*    bias;
*     int*    tend;
*     int*    end;
*     int*    trad;
*     short   linno;
*     short   ukey;
*     char    bit1;
*     char    bit2;
*     char    bbufn;
*     char    files;
*     short   dsor;
*     short   dssz;
*     short   csor;
*     short   cssz;
*     short   meml1;
*     short   meml2;
*     short   midl1;
*     short   midl2;
*     short   eaor;
*     short   easz;
*     int     access[2];
*     int*    linbuf;
*     int     filler;
*     int     sgos[8];
*     int     slos[8];
*     int     sbos[8];
*     char    cdir[16];
*     char    cvol[32];
*     int     ipuac;
*     int     curh;
*     int     crhx;
*     int*    sycf;
*     int*    sgof;
*     int*    slof;
*     int*    sbof;
*     char    cpush;
*     char    ldattr;
*     short   dbor;
*     short   dpinfo;
*     char    taskk;
*     char    bit4;
*     int*    rdbufa;
*     int*    excpad;
*     int*    rorg;
*     int*    rworg;
*     int     dbstat;
*     short*  midla;
*     short*  memla;
*     int     memlo;
*     int     stksz;
*     char    dbname[16];
*     int     expsd[2];
*     int     idxa;
*     short   work;
*     short   nsi;
*     int*    shimda;
*     int     prel;
*     int     dbstw2;
*     int*    bbhca;
*     int     bit5;
*     int*    shtbl;
*     int     smtmlt;
*     int*    sigstk;
*     int     mpxbr[8];
*     int     mpxlm;
*     short   nstat;
*     short   sparhw;
*     int     spares[25];
*     int*    stbrga;
*     int*    pioqa;
*     int*    tiqa;
*     int     ldbss;
*     int     ptrmp;
*     int*    wkadr;
*     int     abpsd;
*     short   midl[4096];
* };
* struct smt {
*     int	    rid[8];	
*     int     name[2];	
*     int	    tnum[2];	
*     int     ownr[2];	
*     int	    proj[2];	
*     int	    srid[2];	
*     int     comp;
*     int     pnid;
*     int     arta;
*     int     flags;
*     short   page;
*     short   ptot;
*     short   maps;
*     short   mapn;
*     short   dses;
*     short   dsen;
*     short   cses;
*     short   csen;
*     char    mty;
*     char    ucnt;
*     short   pool;
*     short   wbks;
*     short   notu;
*     short*  midl;
*     int     wbkn;
*     short   cme;
*     short   cmh;
*     short   cms;
*     short   otsw;
*     int     time[2];
*     int     date[2];
*     char    spbt[3];
*     char    tuc;
*     int     bias;
*     int	    resd[2];	
* };
* static int *xlear();
* static int *lear();
* static void goumap();
* static void gomap();
* struct client {
*     int taskNum;	
*     int nodeNum;	
*     int Status;		
*     int ReqCode;	
*     unsigned int TaskNo;
*     int LogAddr;	
*     int Len;		
*     int Data[8];	
* };
* struct node {
*     int	NodeNum;	
*     int Flag;		
*     int Active;		
*     struct client client[8];	
* };
* static  int     initDone = 0;
	bound	4
_initDone equ  $
	dataw	0
* static  int     nodenum = 0;
	bound	4
_nodenum equ  $
	dataw	0
* static  int     ticksx1;
	bound	4
_ticksx1 equ  $
	rez	4
* static  int     ticksx5;
	bound	4
_ticksx5 equ  $
	rez	4
* static  int     ticksday;
	bound	4
_ticksday equ  $
	rez	4
* static  int     strtclk = 0;
	bound	4
_strtclk equ  $
	dataw	0
* static  int     spsave;
	bound	4
_spsave equ  $
	rez	4
* static  int*    realpadr;
	bound	4
_realpadr equ  $
	rez	4
* static  struct node *laddr = (struct node *)0xc0000;
	bound	4
_laddr equ  $
	dataw	x'c0000'
* static	struct node *nodep;
	bound	4
_nodep equ  $
	rez	4
* static	struct client *clp;
	bound	4
_clp equ  $
	rez	4
* static  struct dqe * dqeptr;
	bound	4
_dqeptr equ  $
	rez	4
* static  int     dqen;
	bound	4
_dqen equ  $
	rez	4
* static  struct tsa * tsaptr;
	bound	4
_tsaptr equ  $
	rez	4
* static  struct smt * smtptr;
	bound	4
_smtptr equ  $
	rez	4
* rtclk()
* {
	dsect
	bound	1w
*	.ebf #1 _rtclk
_rtclk equ  $
	trr	sp,r1
	sumw	sp,SLA1
	std	r0,2w,sp
	stf	r4,4w,sp
*   int     progn;
*   int     index;
*   if (!initDone)return;
	lw	r2,_initDone
	bne	L28
	bu	L27
*   if (nodep->Flag & 1) {
L28 	equ 	$
	lw	r2,_nodep
	lw	r2,1w,r2
	tbr	r2,31
	bns	L29
*     nodep->Active = 0;	
	lw	r2,_nodep
	zmw	2w,r2
*     nodep->Flag &= !1;		
	lw	r2,_nodep
	lw	r1,1w,r2
	anmw	r1,=0
	stw	r1,1w,r2
*     for (progn = 0; progn < 8; progn++) {
	zmw	8w+LOC1,sp
L32 	equ 	$
	lw	r2,8w+LOC1,sp
	ci	r2,8
	bge	L31
*       clp = &nodep->client[progn];	
	lw	r1,8w+LOC1,sp
	mpi	r0,x'3c'
	lw	r2,_nodep
	adi	r2,x'c'
	adr	r1,r2
	stw	r2,_clp
*       if ((clp->nodeNum == nodenum) && clp->taskNum) {
	lw	r2,_clp
	lw	r2,1w,r2
	camw	r2,_nodenum
	bne	L33
	lw	r2,_clp
	lw	r2,0,r2
	beq	L33
*         dqeptr = (((struct adat *)0xa88)->dqe[clp->taskNum 
* >> 24]);
	lw	r2,_clp
	lw	r2,0,r2
	sra	r2,x'18'
	sla	r2,2
	admw	r2,674w
	lw	r2,0,r2
	stw	r2,_dqeptr
*         if (dqeptr->us >= 0x02) {
	lw	r2,_dqeptr
	lb	r2,11,r2
	ci	r2,2
	blt	L34
*           asm (" stw  sp,_spsave");	
 stw  sp,_spsave
*           asm (" ext  S.EXEC18");	
 ext  S.EXEC18
*           asm (" lw   r1,_dqeptr");	
 lw   r1,_dqeptr
*           asm (" lw   r5,=C'OSCO'");
 lw   r5,=C'OSCO'
*           asm (" lw   r6,=C'DEXI'");
 lw   r6,=C'DEXI'
*           asm (" lw   r7,=C'TING'");
 lw   r7,=C'TING'
*           asm (" bl   S.EXEC18");	
 bl   S.EXEC18
*           asm (" lw   sp,_spsave");	
 lw   sp,_spsave
*         }
*       }
L34 	equ 	$
*     }
L33 	equ 	$
L30 	equ 	$
	abm	31,8w+LOC1,sp
	bu 	L32
L31 	equ 	$
*     initDone = 0;
	zmw	_initDone
*     return;
	bu	L27
*   }
*   for (progn = 0; progn < 8; progn++) {
L29 	equ 	$
	zmw	8w+LOC1,sp
L37 	equ 	$
	lw	r2,8w+LOC1,sp
	ci	r2,8
	bge	L36
*     clp = &nodep->client[progn];		
	lw	r1,8w+LOC1,sp
	mpi	r0,x'3c'
	lw	r2,_nodep
	adi	r2,x'c'
	adr	r1,r2
	stw	r2,_clp
*     if ((clp->nodeNum == nodenum) && clp->taskNum) {
	lw	r2,_clp
	lw	r2,1w,r2
	camw	r2,_nodenum
	bne	L38
	lw	r2,_clp
	lw	r2,0,r2
	beq	L38
*       dqeptr = (((struct adat *)0xa88)->dqe[clp->taskNum >>
*  24]);
	lw	r2,_clp
	lw	r2,0,r2
	sra	r2,x'18'
	sla	r2,2
	admw	r2,674w
	lw	r2,0,r2
	stw	r2,_dqeptr
*       if ((dqeptr->tan != clp->taskNum) || (dqeptr->us < 0x
* 02)) {
	lw	r2,_dqeptr
	lw	r2,3w,r2
	lw	r1,_clp
	camw	r2,0,r1
	bne	L999999
	lw	r2,_dqeptr
	lb	r2,11,r2
	ci	r2,2
	bge	L39
L999999	equ	$
*         clp->taskNum = 0;
	lw	r2,_clp
	zmw	0,r2
*       }
*     }
L39 	equ 	$
*   }
L38 	equ 	$
L35 	equ 	$
	abm	31,8w+LOC1,sp
	bu 	L37
L36 	equ 	$
*   for (progn = 0; progn < 8; progn++) {
	zmw	8w+LOC1,sp
L42 	equ 	$
	lw	r2,8w+LOC1,sp
	ci	r2,8
	bge	L41
*     clp = &nodep->client[progn];		
	lw	r1,8w+LOC1,sp
	mpi	r0,x'3c'
	lw	r2,_nodep
	adi	r2,x'c'
	adr	r1,r2
	stw	r2,_clp
*     if ((clp->Status == 1) ||
*       (clp->Status == 2)) {
	lw	r2,_clp
	lw	r2,2w,r2
	ci	r2,1
	beq	L999998
	lw	r2,_clp
	lw	r2,2w,r2
	ci	r2,2
	bne	L43
L999998	equ	$
*           if(clp->nodeNum == nodenum) {
	lw	r2,_clp
	lw	r2,1w,r2
	camw	r2,_nodenum
	bne	L44
*             int getput = 0;
	zmw	10w+LOC1,sp
*             switch (clp->ReqCode) {
	lw	r2,_clp
	lw	r0,3w,r2
	bu 	L46
*               case 1:
L47 	equ 	$
*                 getput = 1;
	li	r2,1
	stw	r2,10w+LOC1,sp
*               case 2:
L48 	equ 	$
*                 if (dqen = (clp->TaskNo >> 24)) {
	lw	r2,_clp
	lw	r2,4w,r2
	srl	r2,x'18'
	stw	r2,_dqen
	trr	r2,r2
	beq	L49
*                     int das = (int)clp->LogAddr;
	lw	r2,_clp
	lw	r2,5w,r2
	stw	r2,11w+LOC1,sp
*                     int dae = das + clp->Len - 1;
	lw	r2,_clp
	lw	r2,6w,r2
	admw	r2,11w+LOC1,sp
	sui	r2,1
	stw	r2,12w+LOC1,sp
*                     int cntr;
*                     dqeptr = (((struct adat *)0xa88)->dqe[d
* qen]);
	lw	r2,_dqen
	sla	r2,2
	admw	r2,674w
	lw	r2,0,r2
	stw	r2,_dqeptr
*                     if (dqeptr->us < 0x02)continue;
	lw	r2,_dqeptr
	lb	r2,11,r2
	ci	r2,2
	bge	L50
	bu 	L40
*                     tsaptr = (struct tsa *)(((int)(dqeptr->
L50 	equ 	$
* msd)) & 0xffe000);
	lw	r2,_dqeptr
	lw	r2,12w,r2
	anmw	r2,=x'ffe000'
	stw	r2,_tsaptr
*                     for (cntr=0; cntr < clp->Len; cntr++) {
	zmw	13w+LOC1,sp
L53 	equ 	$
	lw	r2,_clp
	lw	r2,6w,r2
	camw	r2,13w+LOC1,sp
	ble	L52
*                       int curlmap = ((das + cntr) >> 13) - 
* ((struct c *)0x800)->msd;
	lw	r2,11w+LOC1,sp
	admw	r2,13w+LOC1,sp
	sra	r2,x'd'
	sumb	r2,694w
	stw	r2,14w+LOC1,sp
*                       short * midlptr = (short *)dqeptr->ms
* d;
	lw	r2,_dqeptr
	lw	r2,12w,r2
	stw	r2,15w+LOC1,sp
*                       int phyadr = (((int)(midlptr[curlmap]
* ) << 13) &
*                          0xffe000) | ((das + cntr) & 0x1fff
* );
	lw	r2,14w+LOC1,sp
	sla	r2,1
	admw	r2,15w+LOC1,sp
	lh	r2,0,r2
	sll	r2,x'd'
	anmw	r2,=x'ffe000'
	lw	r1,11w+LOC1,sp
	admw	r1,13w+LOC1,sp
	anmw	r1,=x'1fff'
	orr	r1,r2
	stw	r2,16w+LOC1,sp
*                       if (getput)
	lw	r2,10w+LOC1,sp
	beq	L54
*                         clp->Data[cntr] = (*(char *)phyadr)
* ;
	lw	r2,_clp
	adi	r2,x'1c'
	lw	r1,13w+LOC1,sp
	sla	r1,2
	adr	r1,r2
	lw	r1,16w+LOC1,sp
	lb	r1,0,r1
	stw	r1,0,r2
*                       else
	bu 	L55
L54 	equ 	$
*                         *(char *)phyadr = clp->Data[cntr];
	lw	r2,16w+LOC1,sp
	lw	r1,_clp
	adi	r1,x'1c'
	stw	r1,17w+LOC1,sp
	lw	r1,13w+LOC1,sp
	sla	r1,2
	admw	r1,17w+LOC1,sp
	lw	r1,0,r1
	stb	r1,0,r2
L55 	equ 	$
*                     }
L51 	equ 	$
	abm	31,13w+LOC1,sp
	bu 	L53
L52 	equ 	$
*                 } else {
	bu 	L56
L49 	equ 	$
*                     int das = (int)clp->LogAddr;
	lw	r2,_clp
	lw	r2,5w,r2
	stw	r2,11w+LOC1,sp
*                     int dae = das + clp->Len - 1;
	lw	r2,_clp
	lw	r2,6w,r2
	admw	r2,11w+LOC1,sp
	sui	r2,1
	stw	r2,12w+LOC1,sp
*                     int cntr;
*                     int psla;
*                     smtptr = (struct smt *)((int)(*(struct 
* smt **)0xaf4) +
*                       ((*(char *)0xcc2) * clp->TaskNo));
	lw	r2,_clp
	lw	r1,4w,r2
	mpmb	r0,3266
	lw	r2,701w
	adr	r2,r1
	stw	r1,_smtptr
*                     psla = smtptr->page << 11;
	lw	r2,_smtptr
	lh	r2,22w,r2
	sll	r2,x'b'
	stw	r2,14w+LOC1,sp
*                     for (cntr=0; cntr < clp->Len; cntr++) {
	zmw	13w+LOC1,sp
L59 	equ 	$
	lw	r2,_clp
	lw	r2,6w,r2
	camw	r2,13w+LOC1,sp
	ble	L58
*                       int mapoff = (das - psla + cntr) >> 1
* 3;
	lw	r2,11w+LOC1,sp
	sumw	r2,14w+LOC1,sp
	admw	r2,13w+LOC1,sp
	sra	r2,x'd'
	stw	r2,15w+LOC1,sp
*                       int phyadr = (((int)(smtptr->midl[map
* off]) << 13) &
*                          0xffe000) | ((das - psla + cntr) &
*  0x1fff);
	lw	r2,_smtptr
	lw	r2,28w,r2
	lw	r1,15w+LOC1,sp
	sla	r1,1
	adr	r1,r2
	lh	r2,0,r2
	sll	r2,x'd'
	anmw	r2,=x'ffe000'
	lw	r1,11w+LOC1,sp
	sumw	r1,14w+LOC1,sp
	admw	r1,13w+LOC1,sp
	anmw	r1,=x'1fff'
	orr	r1,r2
	stw	r2,16w+LOC1,sp
*                       if (getput)
	lw	r2,10w+LOC1,sp
	beq	L60
*                         clp->Data[cntr] = (*(char *)phyadr)
* ;
	lw	r2,_clp
	adi	r2,x'1c'
	lw	r1,13w+LOC1,sp
	sla	r1,2
	adr	r1,r2
	lw	r1,16w+LOC1,sp
	lb	r1,0,r1
	stw	r1,0,r2
*                       else
	bu 	L61
L60 	equ 	$
*                         *(char *)phyadr = clp->Data[cntr];
	lw	r2,16w+LOC1,sp
	lw	r1,_clp
	adi	r1,x'1c'
	stw	r1,17w+LOC1,sp
	lw	r1,13w+LOC1,sp
	sla	r1,2
	admw	r1,17w+LOC1,sp
	lw	r1,0,r1
	stb	r1,0,r2
L61 	equ 	$
*                     }
L57 	equ 	$
	abm	31,13w+LOC1,sp
	bu 	L59
L58 	equ 	$
*                 }
L56 	equ 	$
*                 clp->Status = 4;
	lw	r2,_clp
	li	r1,4
	stw	r1,2w,r2
*                 break;
	bu 	L45
*     	
*               case 3:
L62 	equ 	$
*                 dqeptr = (((struct adat *)0xa88)->dqe[clp->
* TaskNo >> 24]);
	lw	r2,_clp
	lw	r2,4w,r2
	srl	r2,x'18'
	sla	r2,2
	admw	r2,674w
	lw	r2,0,r2
	stw	r2,_dqeptr
*                 if (dqeptr->us == 0x13) {
	lw	r2,_dqeptr
	lb	r2,11,r2
	ci	r2,x'13'
	bne	L63
*                   asm (" stw  sp,_spsave");	
 stw  sp,_spsave
*                   asm (" ext  S.EXEC14");	
 ext  S.EXEC14
*                   asm (" lw   r2,_dqeptr");	
 lw   r2,_dqeptr
*                   asm (" bl   S.EXEC14");	
 bl   S.EXEC14
*                   asm (" lw   sp,_spsave");	
 lw   sp,_spsave
*                   clp->Status = 4;	
	lw	r2,_clp
	li	r1,4
	stw	r1,2w,r2
*                 }
*                 break;
L63 	equ 	$
	bu 	L45
*     	
*               case 4:
L64 	equ 	$
*                 dqeptr = (((struct adat *)0xa88)->dqe[clp->
* TaskNo >> 24]);
	lw	r2,_clp
	lw	r2,4w,r2
	srl	r2,x'18'
	sla	r2,2
	admw	r2,674w
	lw	r2,0,r2
	stw	r2,_dqeptr
*                 asm (" stw  sp,_spsave");	
 stw  sp,_spsave
*                 asm (" ext  S.EXEC13");		
 ext  S.EXEC13
*                 asm (" lw   r2,_dqeptr");	
 lw   r2,_dqeptr
*                 asm (" bl   S.EXEC13");		
 bl   S.EXEC13
*                 asm (" lw   sp,_spsave");	
 lw   sp,_spsave
*                 clp->Status = 4;	
	lw	r2,_clp
	li	r1,4
	stw	r1,2w,r2
*                 break;
	bu 	L45
*               default:
L65 	equ 	$
*                 break;
	bu 	L45
*             }
L46 	equ 	$
	sll	r0,2
	sui	r0,4
	blt	L65
	ci	r0,12
	bgt	L65
	trr	r0,r1
	bu	*L999997,r1
L999997	equ	$
	dataw	L47
	dataw	L48
	dataw	L62
	dataw	L64
	dataw	L65
L45 	equ 	$
*           }
*       }
L44 	equ 	$
*   }
L43 	equ 	$
L40 	equ 	$
	abm	31,8w+LOC1,sp
	bu 	L42
L41 	equ 	$
* }
L27 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL1	equ	0w
LOC1	equ	0w
L_TMP1	equ	10w
LA1	equ	24w
SLA1	dataw	LA1
*	.ef #1 _rtclk
	dsect
* instrt()
* {
	dsect
	bound	1w
*	.ebf #2 _instrt
_instrt equ  $
	trr	sp,r1
	sumw	sp,SLA2
	std	r0,2w,sp
	stf	r4,4w,sp
*     nodenum = (*(struct tsa **)0x0a80)->regp->reg[7];
	lw	r2,672w
	lw	r2,366w,r2
	lw	r2,7w,r2
	stw	r2,_nodenum
*     initDone = 0;
	zmw	_initDone
* }
L67 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL2	equ	0w
LOC2	equ	0w
L_TMP2	equ	0w
LA2	equ	8w
SLA2	dataw	LA2
*	.ef #2 _instrt
	dsect
* indone()
* {
	dsect
	bound	1w
*	.ebf #3 _indone
_indone equ  $
	trr	sp,r1
	sumw	sp,SLA3
	std	r0,2w,sp
	stf	r4,4w,sp
*     if (initDone == 0)
	lw	r2,_initDone
	bne	L70
*         initDone = 1;		
	li	r2,1
	stw	r2,_initDone
*     (*(struct tsa **)0x0a80)->regp->reg[7] = initDone;	
L70 	equ 	$
	lw	r2,672w
	lw	r2,366w,r2
	lw	r1,_initDone
	stw	r1,7w,r2
*     strtclk = ((struct c *)0x800)->intc;		
	lw	r2,515w
	stw	r2,_strtclk
*     realpadr = lear(laddr);		
	lw	r2,_laddr
	stw	r2,8w+CALL3,sp
	bl	_lear
	stw	r0,_realpadr
*     nodep = (struct node *)realpadr;	
	lw	r2,_realpadr
	stw	r2,_nodep
*     laddr->Active = 1;		
	lw	r2,_laddr
	li	r1,1
	stw	r1,2w,r2
*     laddr->Flag &= !1;		
	lw	r2,_laddr
	lw	r1,1w,r2
	anmw	r1,=0
	stw	r1,1w,r2
* }
L69 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL3	equ	0w
LOC3	equ	2w
L_TMP3	equ	2w
LA3	equ	16w
SLA3	dataw	LA3
*	.ef #3 _indone
	dsect
* intask()
* {
	dsect
	bound	1w
*	.ebf #4 _intask
_intask equ  $
	trr	sp,r1
	sumw	sp,SLA4
	std	r0,2w,sp
	stf	r4,4w,sp
*     if (initDone) {
	lw	r2,_initDone
	beq	L73
*         (*(struct tsa **)0x0a80)->regp->reg[6] = ticksx1;  
	lw	r2,672w
	lw	r2,366w,r2
	lw	r1,_ticksx1
	stw	r1,6w,r2
*         (*(struct tsa **)0x0a80)->regp->reg[7] = nodenum;  
	lw	r2,672w
	lw	r2,366w,r2
	lw	r1,_nodenum
	stw	r1,7w,r2
*     } else {
	bu 	L74
L73 	equ 	$
*         (*(struct tsa **)0x0a80)->regp->reg[6] = ticksx1;  
	lw	r2,672w
	lw	r2,366w,r2
	lw	r1,_ticksx1
	stw	r1,6w,r2
*         (*(struct tsa **)0x0a80)->regp->reg[7] = 0;
	lw	r2,672w
	lw	r2,366w,r2
	zmw	7w,r2
*     }
L74 	equ 	$
* }
L72 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL4	equ	0w
LOC4	equ	0w
L_TMP4	equ	0w
LA4	equ	8w
SLA4	dataw	LA4
*	.ef #4 _intask
	dsect
* static int *xlear(addr)
* int *addr;
* {
	dsect
	bound	1w
*	.sbf #5 _xlear
_xlear equ  $
	trr	sp,r1
	sumw	sp,SLA5
	std	r0,2w,sp
	stf	r4,4w,sp
*     int     mapnum;
*     mapnum = (((int)addr & 0xffffff) >> 13) - ((struct c *)
* 0x800)->msd;
	lw	r2,8w+LA5,sp
	anmw	r2,=x'ffffff'
	sra	r2,x'd'
	sumb	r2,694w
	stw	r2,8w+LOC5,sp
*     return ((int *)((((*(struct tsa **)0x0a80)->midla[mapnu
* m] << 13)
*         | ((int)addr & 0x1fff)) & 0xffffff));
	lw	r2,672w
	lw	r2,514w,r2
	lw	r1,8w+LOC5,sp
	sla	r1,1
	adr	r1,r2
	lh	r0,0,r2
	sll	r0,x'd'
	lw	r2,8w+LA5,sp
	anmw	r2,=x'1fff'
	orr	r2,r0
	anmw	r0,=x'ffffff'
	bu	L75
* }
L75 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL5	equ	0w
LOC5	equ	0w
L_TMP5	equ	2w
LA5	equ	16w
SLA5	dataw	LA5
*	.ef #5 _xlear
	dsect
* static int *lear(addr)
* int *addr;
* {
	dsect
	bound	1w
*	.sbf #6 _lear
_lear equ  $
	trr	sp,r1
	sumw	sp,SLA6
	std	r0,2w,sp
	stf	r4,4w,sp
*     asm (" lw   r1,8W,sp");
 lw   r1,8W,sp
*     asm (" lear r0,0w,r1");
 lear r0,0w,r1
* }
L76 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL6	equ	0w
LOC6	equ	0w
L_TMP6	equ	0w
LA6	equ	8w
SLA6	dataw	LA6
*	.ef #6 _lear
	dsect
* static void goumap()
* {
	dsect
	bound	1w
*	.sbf #7 _goumap
_goumap equ  $
	trr	sp,r1
	sumw	sp,SLA7
	std	r0,2w,sp
	stf	r4,4w,sp
*     asm ("     lpsd  psd1");
     lpsd  psd1
*     asm ("     bound 1d");
     bound 1d
*     asm ("psd1 gen   8/x'84',24/goon");
psd1 gen   8/x'84',24/goon
*     asm ("     dataw x'00018000'");
     dataw x'00018000'
*     asm ("goon equ   $");
goon equ   $
* }
L77 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL7	equ	0w
LOC7	equ	0w
L_TMP7	equ	0w
LA7	equ	8w
SLA7	dataw	LA7
*	.ef #7 _goumap
	dsect
* static void gomap()
* {
	dsect
	bound	1w
*	.sbf #8 _gomap
_gomap equ  $
	trr	sp,r1
	sumw	sp,SLA8
	std	r0,2w,sp
	stf	r4,4w,sp
*     asm ("      lpsd  psd2");
      lpsd  psd2
*     asm ("      bound 1d");
      bound 1d
*     asm ("psd2  gen   8/x'84',24/gmon");
psd2  gen   8/x'84',24/gmon
*     asm ("      dataw x'80018000'");
      dataw x'80018000'
*     asm ("gmon  equ   $");
gmon  equ   $
* }
L78 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL8	equ	0w
LOC8	equ	0w
L_TMP8	equ	0w
LA8	equ	8w
SLA8	dataw	LA8
*	.ef #8 _gomap
	dsect
*     asm (" bound 1w");
 bound 1w
*     asm ("clki  equ $");
clki  equ $
*     asm (" stf  r0,lclstk");
 stf  r0,lclstk
*     asm (" la   sp,lclstk");
 la   sp,lclstk
*     asm (" bl   _rtclk");
 bl   _rtclk
*     asm (" lf   r0,0w,sp");
 lf   r0,0w,sp
*     asm ("rtci  nop");
rtci  nop
*     asm ("reti  bu $-$");
reti  bu $-$
*     asm (" res  8f");
 res  8f
*     asm ("lclstk res 1f");
lclstk res 1f
*     asm (" bound 1w");
 bound 1w
*     asm ("svc1_6 equ $");
svc1_6 equ $
*     asm (" lw   r3,x'a80'");
 lw   r3,x'a80'
*     asm (" lw   sp,x'5bc',r3");
 lw   sp,x'5bc',r3
*     asm (" bl   _instrt");
 bl   _instrt
*     asm (" ext  S.EXEC20");
 ext  S.EXEC20
*     asm (" bu   S.EXEC20");
 bu   S.EXEC20
*     asm (" bound 1w");
 bound 1w
*     asm ("svc1_7 equ $");
svc1_7 equ $
*     asm (" lw   r3,x'a80'");
 lw   r3,x'a80'
*     asm (" lw   sp,x'5bc',r3");
 lw   sp,x'5bc',r3
*     asm (" bl   _indone");
 bl   _indone
*     asm (" ext  S.EXEC20");
 ext  S.EXEC20
*     asm (" bu   S.EXEC20");
 bu   S.EXEC20
*     asm (" bound 1w");
 bound 1w
*     asm ("svc1_8 equ $");
svc1_8 equ $
*     asm (" lw   r3,x'a80'");
 lw   r3,x'a80'
*     asm (" lw   sp,x'5bc',r3");
 lw   sp,x'5bc',r3
*     asm (" bl   _intask");
 bl   _intask
*     asm (" ext  S.EXEC20");
 ext  S.EXEC20
*     asm (" bu   S.EXEC20");
 bu   S.EXEC20
* static int tcpb[3] = {0,0,0};
	dsect
	bound	4
_tcpb equ  $
	dataw	0
	dataw	0
	dataw	0
* static void typ(str)
* char *str;
* {
	dsect
	bound	1w
*	.sbf #9 _typ
_typ equ  $
	trr	sp,r1
	sumw	sp,SLA9
	std	r0,2w,sp
	stf	r4,4w,sp
*     int i;
*     for(i = 1; str[i] != 0; i++);
	li	r2,1
	stw	r2,8w+LOC9,sp
L84 	equ 	$
	lw	r2,8w+LA9,sp
	admw	r2,8w+LOC9,sp
	lb	r2,0,r2
	beq	L83
L82 	equ 	$
	abm	31,8w+LOC9,sp
	bu 	L84
L83 	equ 	$
*         tcpb[0] = i << 20 | 0x00080000 | (int)str;
	lw	r2,8w+LOC9,sp
	sll	r2,x'14'
	ormw	r2,=x'80000'
	lw	r1,8w+LA9,sp
	orr	r1,r2
	stw	r2,_tcpb
*     asm(" la  r1,_tcpb");
 la  r1,_tcpb
*     asm(" svc 1,x'3f'");
 svc 1,x'3f'
* }
L81 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL9	equ	0w
LOC9	equ	0w
L_TMP9	equ	2w
LA9	equ	16w
SLA9	dataw	LA9
*	.ef #9 _typ
	dsect
*     asm (" lpool");
 lpool
*     asm ("sg.ini stf r0,stack-1f");
sg.ini stf r0,stack-1f
*     asm (" la sp,stack-2f");
 la sp,stack-2f
*     asm (" bl _sgent");
 bl _sgent
*     asm (" lf r0,stack-1f");
 lf r0,stack-1f
*     asm (" trsw r0");
 trsw r0
*     asm (" res 12f");
 res 12f
*     asm ("stack equ $");
stack equ $
*     asm ("bri bu clki");
bri bu clki
* sgent(reg0,reg1,reg2,reg3,reg4,reg5,reg6,reg7)
* int reg0, reg1, reg2, reg3, reg4, reg5, reg6, reg7;
* {
	dsect
	bound	1w
*	.ebf #10 _sgent
_sgent equ  $
	trr	sp,r1
	sumw	sp,SLA10
	std	r0,2w,sp
	stf	r4,4w,sp
*     asm (" ext  IPCL.ICB");
 ext  IPCL.ICB
*     asm (" la   r1,IPCL.ICB");
 la   r1,IPCL.ICB
*     asm (" lw   r1,2w,r1");
 lw   r1,2w,r1
*     asm (" adi  r1,2w");
 adi  r1,2w
*     asm (" anmw r1,=x'ffffff'");
 anmw r1,=x'ffffff'
*     asm (" lw   r0,=x'ec000000'");
 lw   r0,=x'ec000000'
*     asm (" orr  r1,r0");
 orr  r1,r0
*     asm (" adi  r0,1w");
 adi  r0,1w
*     asm (" stw  r0,reti");
 stw  r0,reti
*     asm (" lw   r0,0w,r1");
 lw   r0,0w,r1
*     asm (" stw  r0,rtci");
 stw  r0,rtci
*     asm (" lw   r0,bri");
 lw   r0,bri
*     asm (" stw  r0,0w,r1");
 stw  r0,0w,r1
*     asm (" lw   r1,x'b00'");
 lw   r1,x'b00'
*     asm (" la   r0,svc1_6");
 la   r0,svc1_6
*     asm (" stw  r0,6w,r1");
 stw  r0,6w,r1
*     asm (" la   r0,svc1_7");
 la   r0,svc1_7
*     asm (" stw  r0,7w,r1");
 stw  r0,7w,r1
*     asm (" la   r0,svc1_8");
 la   r0,svc1_8
*     asm (" stw  r0,8w,r1");
 stw  r0,8w,r1
*     asm (" li   r7,1");
 li   r7,1
*     asm (" mpmw r6,x'adc'");
 mpmw r6,x'adc'
*     asm (" dvmw r6,x'ae0'");
 dvmw r6,x'ae0'
*     asm (" stw  r7,_ticksx1");
 stw  r7,_ticksx1
*     asm (" li   r7,5");
 li   r7,5
*     asm (" mpmw r6,x'adc'");
 mpmw r6,x'adc'
*     asm (" dvmw r6,x'ae0'");
 dvmw r6,x'ae0'
*     asm (" stw  r7,_ticksx5");
 stw  r7,_ticksx5
*     asm (" lw   r7,=86400");
 lw   r7,=86400
*     asm (" mpmw r6,x'adc'");
 mpmw r6,x'adc'
*     asm (" dvmw r6,x'ae0'");
 dvmw r6,x'ae0'
*     asm (" stw  r7,_ticksday");
 stw  r7,_ticksday
*         return;
	bu	L86
* }
L86 	equ 	$
	lf	r2,2w,sp
	trsw	r2
CALL10	equ	0w
LOC10	equ	0w
L_TMP10	equ	0w
LA10	equ	8w
SLA10	dataw	LA10
*	.ef #10 _sgent
	dsect
	def	_rtclk
	def	_instrt
	def	_indone
	def	_intask
	def	_sgent
	dsect
	end
