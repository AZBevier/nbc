   00001                                * "SPR13.c" @(#)J B Systems Non-Base C Compiler - Wed Jun 1 17:45:40 MDT 1994   
   00002                                *                                                                               
   00003                                           program    SPR13                                                     
   00004                                           list       mac,nong,nodata                                           
   00005                                *                                                                               
   00006    00000                       r0         equ        0                                                         
   00007    00001                       r1         equ        1                                                         
   00008    00002                       r2         equ        2                                                         
   00009    00003                       r3         equ        3                                                         
   00010    00004                       r4         equ        4                                                         
   00011    00005                       r5         equ        5                                                         
   00012    00006                       r6         equ        6                                                         
   00013    00007                       r7         equ        7                                                         
   00014    00003                       sp         equ        3                                                         
   00015                                *                                                                               
   00016  *P00000                                  csect                                                                
   00017  *P00000  2243223A                        dataw      x'2243223a'                                               
   00018                                 .src s.1 /*                                                                    
   00019   P00000                                  dsect                                                                
   00020                                 .src s.2 When we compile the attached program and trace through it,            
   00021                                 .src s.2 statements s.13                                                       
   00022                                 .src s.3 through s.22 are traced oaky, but as soon as you try and tr           
   00023                                 .src s.3 ace from s.23                                                         
   00024                                 .src s.4 on (without any breaks set) it immediately executes all rem           
   00025                                 .src s.4 aining code and                                                       
   00026                                 .src s.5 tracing is terminated and the program exits. If we set a br           
   00027                                 .src s.5 eak on s.34 for                                                       
   00028                                 .src s.6 example and go there tracing is okay, but if you set a brea           
   00029                                 .src s.6 k on s.33 you                                                         
   00030                                 .src s.7 have the same problem.                                                
   00031                                 .src s.8 */                                                                    
   00032                                 .src s.9                                                                       
   00033                                 .src s.10                                                                      
   00034                                 .com s.10 /*~!stdio.h*/                                                        
   00035                                 .com s.10 /* Name:  stdio.h Part No.: _______-____r                            
   00036                                 .com s.10  *                                                                   
   00037                                 .com s.10  * Copyright 1990 - J B Systems, Morrison, CO                        
   00038                                 .com s.10  *                                                                   
   00039                                 .com s.10  * The recipient of this product specifically agrees not to          
   00040                                 .com s.10  distribute,                                                         
   00041                                 .com s.10  * disclose, or disseminate in any way, to any one, nor use          
   00042                                 .com s.10  for its own                                                         
   00043                                 .com s.10  * benefit, or the benefit of others, any information conta          
   00044                                 .com s.10 ined  herein                                                         
   00045                                 .com s.10  * without the expressed written consent of J B Systems.             
   00046                                 .com s.10  *                                                                   
   00047                                 .com s.10  *                     RESTRICTED RIGHTS LEGEND                      
   00048                                 .com s.10  *                                                                   
   00049                                 .com s.10  * Use, duplication, or disclosure by the Government is  su          
   00050                                 .com s.10 bject  to                                                            
   00051                                 .com s.10  * restriction  as  set forth in paragraph (b) (3) (B) of t          
   00052                                 .com s.10 he Rights                                                            
   00053                                 .com s.10  * in Technical Data and Computer Software  Clause  in  DAR          
   00054                                 .com s.10   7-104.9                                                            
   00055                                 .com s.10  * (a).                                                              
   00056                                 .com s.10  */                                                                  
   00057                                 .com s.10                                                                      
   00058                                 .com s.10                                                                      
   00059                                 .com s.10                                                                      
   00060                                 .com s.10                                                                      
   00061                                 .com s.10                                                                      
   00062                                 .com s.10                                                                      
   00063                                 .com s.10                                                                      
   00064                                 .com s.10                                                                      
   00065                                 .com s.10                                                                      
   00066                                 .com s.10                                                                      
   00067                                 .com s.10                                                                      
   00068                                 .com s.10                                                                      
   00069                                 .com s.10                                                                      
   00070                                 .com s.10                                                                      
   00071                                 .com s.10 /* buffer size for multi-character output to unbuffered fil          
   00072                                 .com s.10 es */                                                                
   00073                                 .com s.10                                                                      
   00074                                 .com s.10                                                                      
   00075                                 .com s.10 typedef struct {                                                     
   00076                                 .com s.10   int  _cnt;                                                         
   00077                                 .com s.10   unsigned char    *_ptr;                                            
   00078                                 .com s.10   unsigned char    *_base;                                           
   00079                                 .com s.10   short    _flag;    /* expanded to short for mpx */                 
   00080                                 .com s.10   char _file;                                                        
   00081                                 .com s.10 } FILE;                                                              
   00082                                *.stabs _FILE struct _FILE SNAM 16                                              
   00083                                *.stabc __cnt int off:0 siz:32;                                                 
   00084                                *.stabc __ptr PTR uchar off:32 siz:32;                                          
   00085                                *.stabc __base PTR uchar off:64 siz:32;                                         
   00086                                *.stabc __flag short off:96 siz:16;                                             
   00087                                *.stabc __file char off:112 siz:8;                                              
   00088                                *.stabe _FILE struct _FILE SNAM 16                                              
   00089                                 .com s.10                                                                      
   00090                                 .com s.10 /*                                                                   
   00091                                 .com s.10  * _IOLBF means that a file's output will be buffered line           
   00092                                 .com s.10 by line                                                              
   00093                                 .com s.10  * In addition to being flags, _IONBF, _IOLBF and _IOFBF ar          
   00094                                 .com s.10 e possible                                                           
   00095                                 .com s.10  * values for "type" in setvbuf.                                     
   00096                                 .com s.10  */                                                                  
   00097                                 .com s.10                                                                      
   00098                                 .com s.10                                                                      
   00099                                 .com s.10                                                                      
   00100                                 .com s.10                                                                      
   00101                                 .com s.10                                                                      
   00102                                 .com s.10                                                                      
   00103                                 .com s.10                                                                      
   00104                                 .com s.10                                                                      
   00105                                 .com s.10                                                                      
   00106                                 .com s.10                                                                      
   00107                                 .com s.10                                                                      
   00108                                 .com s.10                                                                      
   00109                                 .com s.10                                                                      
   00110                                 .com s.10                                                                      
   00111                                 .com s.10                                                                      
   00112                                 .com s.10                                                                      
   00113                                 .com s.10                                                                      
   00114                                 .com s.10                                                                      
   00115                                 .com s.10                                                                      
   00116                                 .com s.10                                                                      
   00117                                 .com s.10                                                                      
   00118                                 .com s.10                                                                      
   00119                                 .com s.10                                                                      
   00120                                 .com s.10                                                                      
   00121                                 .com s.10                                                                      
   00122                                 .com s.10                                                                      
   00123                                 .com s.10                                                                      
   00124                                 .com s.10                                                                      
   00125                                 .com s.10                                                                      
   00126                                 .com s.10                                                                      
   00127                                 .com s.10                                                                      
   00128                                 .com s.10                                                                      
   00129                                 .com s.10                                                                      
   00130                                 .com s.10                                                                      
   00131                                 .com s.10                                                                      
   00132                                 .com s.10                                                                      
   00133                                 .com s.10                                                                      
   00134                                 .com s.10                                                                      
   00135                                 .com s.10                                                                      
   00136                                 .com s.10                                                                      
   00137                                 .com s.10                                                                      
   00138                                 .com s.10                                                                      
   00139                                 .com s.10                                                                      
   00140                                 .com s.10                                                                      
   00141                                 .com s.10 extern FILE   _iob[20];                                              
   00142                                 .sym __iob ARY 0 19 struct _FILE ESYM 16                                       
   00143                                 .com s.10 extern FILE   *fopen(), *fdopen(), *freopen(), *tmpfile();           
   00144                                 .com s.10 extern long   ftell();                                               
   00145                                 .com s.10 extern void   rewind(), setbuf();                                    
   00146                                 .com s.10 extern char   *fgets(), *gets(), *tempnam(), *tmpnam();              
   00147                                 .com s.10 extern int    fclose(), fflush(), fread(), fwrite(), fseek(),        
   00148                                 .com s.10 fgetc(),                                                             
   00149                                 .com s.10    getw(), printf(), fprintf(), sprintf(),                           
   00150                                 .com s.10    vprintf(), vfprintf(), vsprintf(), fputc(), putw(),               
   00151                                 .com s.10    puts(), fputs(), scanf(), fscanf(), sscanf(),                     
   00152                                 .com s.10    setvbuf(), ungetc();                                              
   00153                                 .com s.10 extern unsigned char *_bufendtab[];                                  
   00154                                 .sym __bufend ARY 0 -1 PTR uchar ESYM 1                                        
   00155                                 .com s.10                                                                      
   00156                                 .com s.10                                                                      
   00157                                 .com s.10                                                                      
   00158                                 .com s.10                                                                      
   00159                                 .com s.10                                                                      
   00160                                 .com s.10                                                                      
   00161                                 .com s.10                                                                      
   00162                                 .com s.10 extern struct _myidbl {                                              
   00163                                 .com s.10   int _taskno;                                                       
   00164                                 .com s.10   char _lm [8];                                                      
   00165                                 .com s.10   char _on [8];                                                      
   00166                                 .com s.10   char _pn [8];                                                      
   00167                                 .com s.10   char _cd [8];                                                      
   00168                                 .com s.10   short _dummy;                                                      
   00169                                 .com s.10   short _key;                                                        
   00170                                 .com s.10   int _flags;                                                        
   00171                                 .com s.10 }                                                                    
   00172                                *.stabs __myidbl struct __myidbl SNAM 44                                        
   00173                                *.stabc __taskno int off:0 siz:32;                                              
   00174                                *.stabc __lm ARY 0 7 char off:32 siz:64;                                        
   00175                                *.stabc __on ARY 0 7 char off:96 siz:64;                                        
   00176                                *.stabc __pn ARY 0 7 char off:160 siz:64;                                       
   00177                                *.stabc __cd ARY 0 7 char off:224 siz:64;                                       
   00178                                *.stabc __dummy short off:288 siz:16;                                           
   00179                                *.stabc __key short off:304 siz:16;                                             
   00180                                *.stabc __flags int off:320 siz:32;                                             
   00181                                *.stabe __myidbl struct __myidbl SNAM 44                                        
   00182                                 .com s.10 _myid;                                                               
   00183                                 .sym __myid struct __myidbl ESYM 44                                            
   00184                                 .com s.10                                                                      
   00185                                 .com s.10                                                                      
   00186                                 .com s.10                                                                      
   00187                                 .com s.10                                                                      
   00188                                 .src s.11                                                                      
   00189                                 .src s.12 /*                                                                   
   00190                                 .src s.13  a test on structures and variables.                                 
   00191                                 .src s.14 */                                                                   
   00192                                 .src s.15                                                                      
   00193                                 .src s.16 main()                                                               
   00194                                 .src s.17 {                                                                    
   00195   P00000                        .sym _main int GFTN 4                                                          
   00196  *P00004                                  csect                                                                
   00197  *P00004                                  bound      1w                                                        
   00198                                *    .ebf #1 _main                                                              
   00199  *P00004                       _main equ  $                                                                    
   00200  *P00004  2CB0                            trr        sp,r1                                                     
   00201  *P00008  BD800108  *P00108               sumw       sp,SLA1                                                   
   00202  *P0000C  D460000A    00008               std        r0,2w,sp                                                  
   00203  *P00010  DE600010    00010               stf        r4,4w,sp                                                  
   00204  *P00014                        .xeq s.18 static struct  un1                                                   
   00205  *P00014                        .xeq s.19        {                                                             
   00206  *P00014                        .xeq s.20        int int1;                                                     
   00207  *P00014                        .xeq s.21        unsigned int  unsign1;                                        
   00208  *P00014                        .xeq s.22        unsigned int  unsign2;                                        
   00209  *P00014                        .xeq s.23        int int2;                                                     
   00210  *P00014                        .xeq s.24        }  dummy=                                                     
   00211                                *.stabs _un1 struct _un1 SNAM 16                                                
   00212                                *.stabc _int1 int off:0 siz:32;                                                 
   00213                                *.stabc _unsign1 uint off:32 siz:32;                                            
   00214                                *.stabc _unsign2 uint off:64 siz:32;                                            
   00215                                *.stabc _int2 int off:96 siz:32;                                                
   00216                                *.stabe _un1 struct _un1 SNAM 16                                                
   00217  *P00014                        .sym _dummy struct _un1 HSYM 16 L49                                            
   00218   P00000                                  dsect                                                                
   00219   P00000                                  bound      4                                                         
   00220   P00000                       L49        equ        $                                                         
   00221   P00000                        .xeq s.25        {                                                             
   00222   P00000                        .xeq s.26        1,  2,  3,  4                                                 
   00223   P00000  00000001                        dataw      1                                                         
   00224   P00004  00000002                        dataw      2                                                         
   00225   P00008  00000003                        dataw      3                                                         
   00226   P0000C                        .xeq s.27        };                                                            
   00227   P0000C  00000004                        dataw      4                                                         
   00228  *P00014                                  csect                                                                
   00229  *P00014                        .xeq s.28                                                                      
   00230  *P00014                        .xeq s.29 static struct  un2                                                   
   00231  *P00014                        .xeq s.30        {                                                             
   00232  *P00014                        .xeq s.31        int int3;                                                     
   00233  *P00014                        .xeq s.32        unsigned int  unsign3;                                        
   00234  *P00014                        .xeq s.33        unsigned int  unsign4;                                        
   00235  *P00014                        .xeq s.34        int int4;                                                     
   00236  *P00014                        .xeq s.35        } dummy2 = {1, 2, 3, 4};                                      
   00237                                *.stabs _un2 struct _un2 SNAM 16                                                
   00238                                *.stabc _int3 int off:0 siz:32;                                                 
   00239                                *.stabc _unsign3 uint off:32 siz:32;                                            
   00240                                *.stabc _unsign4 uint off:64 siz:32;                                            
   00241                                *.stabc _int4 int off:96 siz:32;                                                
   00242                                *.stabe _un2 struct _un2 SNAM 16                                                
   00243  *P00014                        .sym _dummy2 struct _un2 HSYM 16 L50                                           
   00244   P00010                                  dsect                                                                
   00245   P00010                                  bound      4                                                         
   00246   P00010                       L50        equ        $                                                         
   00247   P00010  00000001                        dataw      1                                                         
   00248   P00014  00000002                        dataw      2                                                         
   00249   P00018  00000003                        dataw      3                                                         
   00250   P0001C  00000004                        dataw      4                                                         
   00251  *P00014                                  csect                                                                
   00252  *P00014                        .xeq s.36                                                                      
   00253  *P00014                        .xeq s.37    int *add0,  *add1,  *add2,  *add3,  *add4;                        
   00254  *P00014                        .sym _add0 PTR int AUTO 4 LOC1+32                                              
   00255  *P00014                        .sym _add1 PTR int AUTO 4 LOC1+36                                              
   00256  *P00014                        .sym _add2 PTR int AUTO 4 LOC1+40                                              
   00257  *P00014                        .sym _add3 PTR int AUTO 4 LOC1+44                                              
   00258  *P00014                        .sym _add4 PTR int AUTO 4 LOC1+48                                              
   00259  *P00014                        .xeq s.38    int con0,  con1, con2, con3, con4;                                
   00260  *P00014                        .sym _con0 int AUTO 4 LOC1+52                                                  
   00261  *P00014                        .sym _con1 int AUTO 4 LOC1+56                                                  
   00262  *P00014                        .sym _con2 int AUTO 4 LOC1+60                                                  
   00263  *P00014                        .sym _con3 int AUTO 4 LOC1+64                                                  
   00264  *P00014                        .sym _con4 int AUTO 4 LOC1+68                                                  
   00265  *P00014                        .xeq s.39                                                                      
   00266  *P00014                        .xeq s.40    add0 = (int*)&dummy;                                              
   00267  *P00014  35000000   P00000               la         r2,L49                                                    
   00268  *P00018  D5600040    00040               stw        r2,8w+LOC1,sp                                             
   00269  *P0001C                        .xeq s.41    add1 = &dummy.int1;                                               
   00270  *P0001C  35000000   P00000               la         r2,L49                                                    
   00271  *P00020  D5600044    00044               stw        r2,9w+LOC1,sp                                             
   00272  *P00024                        .xeq s.42    con1 = dummy.int1;                                                
   00273  *P00024  AD000000   P00000               lw         r2,L49                                                    
   00274  *P00028  D5600058    00058               stw        r2,14w+LOC1,sp                                            
   00275  *P0002C                        .xeq s.43    add2 = (int*)&dummy.unsign1;                                      
   00276  *P0002C  35000000   P00000               la         r2,L49                                                    
   00277  *P00030  22A3                            abr        r2,29                                                     
   00278  *P00034  D5600048    00048               stw        r2,10w+LOC1,sp                                            
   00279  *P00038                        .xeq s.44    con2 = dummy.unsign1;                                             
   00280  *P00038  35000000   P00000               la         r2,L49                                                    
   00281  *P0003C  AD400004    00004               lw         r2,1w,r2                                                  
   00282  *P00040  D560005C    0005C               stw        r2,15w+LOC1,sp                                            
   00283  *P00044                        .xeq s.45    add3 = (int*)&dummy.unsign2;                                      
   00284  *P00044  35000000   P00000               la         r2,L49                                                    
   00285  *P00048  2223                            abr        r2,28                                                     
   00286  *P0004C  D560004C    0004C               stw        r2,11w+LOC1,sp                                            
   00287  *P00050                        .xeq s.46    con3 = dummy.unsign2;                                             
   00288  *P00050  35000000   P00000               la         r2,L49                                                    
   00289  *P00054  AD400008    00008               lw         r2,2w,r2                                                  
   00290  *P00058  D5600060    00060               stw        r2,16w+LOC1,sp                                            
   00291  *P0005C                        .xeq s.47    add4 = &dummy.int2;                                               
   00292  *P0005C  35000000   P00000               la         r2,L49                                                    
   00293  *P00060  C901000C                        adi        r2,x'c'                                                   
   00294  *P00064  D5600050    00050               stw        r2,12w+LOC1,sp                                            
   00295  *P00068                        .xeq s.48    con4 = dummy.int2;                                                
   00296  *P00068  35000000   P00000               la         r2,L49                                                    
   00297  *P0006C  AD40000C    0000C               lw         r2,3w,r2                                                  
   00298  *P00070  D5600064    00064               stw        r2,17w+LOC1,sp                                            
   00299  *P00074                        .xeq s.49    printf("add0=%X dummy=%X,%X,%X,%X add1=%X con1=%X\n",add          
   00300  *P00074                        .xeq s.49 0,dummy,add1,con1);                                                  
   00301  *P00074  35000020   P00020               la         r2,L51                                                    
   00302  *P00078  D5600020    00020               stw        r2,8w+CALL1,sp                                            
   00303  *P0007C  AD600040    00040               lw         r2,8w+LOC1,sp                                             
   00304  *P00080  D5600024    00024               stw        r2,9w+CALL1,sp                                            
   00305  *P00084  AC00000C   P0000C               lw         r0,L49+3w                                                 
   00306  *P00088  D4600034    00034               stw        r0,13w+CALL1,sp                                           
   00307  *P0008C  AC000008   P00008               lw         r0,L49+2w                                                 
   00308  *P00090  D4600030    00030               stw        r0,12w+CALL1,sp                                           
   00309  *P00094  AC000004   P00004               lw         r0,L49+1w                                                 
   00310  *P00098  D460002C    0002C               stw        r0,11w+CALL1,sp                                           
   00311  *P0009C  AC000000   P00000               lw         r0,L49                                                    
   00312  *P000A0  D4600028    00028               stw        r0,10w+CALL1,sp                                           
   00313  *P000A4  AD600044    00044               lw         r2,9w+LOC1,sp                                             
   00314  *P000A8  D5600038    00038               stw        r2,14w+CALL1,sp                                           
   00315  *P000AC  AD600058    00058               lw         r2,14w+LOC1,sp                                            
   00316  *P000B0  D560003C    0003C               stw        r2,15w+CALL1,sp                                           
   00317  *P000B4  F8800001   X00000               bl         _printf                                                   
   00318  *P000B8                        .xeq s.50    printf("add2=%X con2=%X add3=%X con3=%X\n",add2,con2,add          
   00319  *P000B8                        .xeq s.50 3,con3);                                                             
   00320  *P000B8  3500004B   P0004B               la         r2,L52                                                    
   00321  *P000BC  D5600020    00020               stw        r2,8w+CALL1,sp                                            
   00322  *P000C0  AD600048    00048               lw         r2,10w+LOC1,sp                                            
   00323  *P000C4  D5600024    00024               stw        r2,9w+CALL1,sp                                            
   00324  *P000C8  AD60005C    0005C               lw         r2,15w+LOC1,sp                                            
   00325  *P000CC  D5600028    00028               stw        r2,10w+CALL1,sp                                           
   00326  *P000D0  AD60004C    0004C               lw         r2,11w+LOC1,sp                                            
   00327  *P000D4  D560002C    0002C               stw        r2,11w+CALL1,sp                                           
   00328  *P000D8  AD600060    00060               lw         r2,16w+LOC1,sp                                            
   00329  *P000DC  D5600030    00030               stw        r2,12w+CALL1,sp                                           
   00330  *P000E0  F88000B5  *Y000B4               bl         _printf                                                   
   00331  *P000E4                        .xeq s.51    printf("add4=%X con4=%X\n",add4,con4);                            
   00332  *P000E4  3500006C   P0006C               la         r2,L53                                                    
   00333  *P000E8  D5600020    00020               stw        r2,8w+CALL1,sp                                            
   00334  *P000EC  AD600050    00050               lw         r2,12w+LOC1,sp                                            
   00335  *P000F0  D5600024    00024               stw        r2,9w+CALL1,sp                                            
   00336  *P000F4  AD600064    00064               lw         r2,17w+LOC1,sp                                            
   00337  *P000F8  D5600028    00028               stw        r2,10w+CALL1,sp                                           
   00338  *P000FC  F88000E1  *Y000E0               bl         _printf                                                   
   00339  *P00100                        .xeq s.52                                                                      
   00340  *P00100                        .xeq s.53 }                                                                    
   00341  *P00100                       L48        equ        $                                                         
   00342  *P00100  CD600008    00008               lf         r2,2w,sp                                                  
   00343  *P00104  2900                            trsw       r2                                                        
   00344   P00020                                  dsect                                                                
   00345   P00020                       L51        equ        $                                                         
   00346   P00020  61646430                        datab      c'add0="%X dummy="%X,"%X,"%X,"%X '                        
   00347   P0003A      6164                        datab      c'add1="%X con1="%X"J"@'                                  
   00348   P0004B                       L52        equ        $                                                         
   00349   P0004B        61                        datab      c'add2="%X con2="%X add3="%X con3'                        
   00350   P00067        3D                        datab      c'="%X"J"@'                                               
   00351   P0006C                       L53        equ        $                                                         
   00352   P0006C  61646434                        datab      c'add4="%X con4="%X"J"@'                                  
   00353  *P00106                                  csect                                                                
   00354    00000                       CALL1      equ        0w                                                        
   00355    00020                       LOC1       equ        8w                                                        
   00356    00048                       L_TMP1     equ        18w                                                       
   00357    00080                       LA1        equ        32w                                                       
   00358  *P00108  00000080             SLA1       dataw      LA1                                                       
   00359                                *    .ef #1 _main                                                               
   00360   P0007D                                  dsect                                                                
