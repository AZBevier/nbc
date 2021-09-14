/*
When we compile the attached program and trace through it, statements s.13
through s.22 are traced oaky, but as soon as you try and trace from s.23
on (without any breaks set) it immediately executes all remaining code and
tracing is terminated and the program exits. If we set a break on s.34 for
example and go there tracing is okay, but if you set a break on s.33 you
have the same problem.
*/
 
#include <stdio.h>
 
/*
 a test on structures and variables.
*/
 
main()
{
static struct  un1
       {
       int int1;
       unsigned int  unsign1;
       unsigned int  unsign2;
       int int2;
       }  dummy=
       {
       1,  2,  3,  4
       };
 
static struct  un2
       {
       int int3;
       unsigned int  unsign3;
       unsigned int  unsign4;
       int int4;
       } dummy2 = {1, 2, 3, 4};
 
   int *add0,  *add1,  *add2,  *add3,  *add4;
   int con0,  con1, con2, con3, con4;
 
   add0 = (int*)&dummy;
   add1 = &dummy.int1;
   con1 = dummy.int1;
   add2 = (int*)&dummy.unsign1;
   con2 = dummy.unsign1;
   add3 = (int*)&dummy.unsign2;
   con3 = dummy.unsign2;
   add4 = &dummy.int2;
   con4 = dummy.int2;
   printf("add0=%X dummy=%X,%X,%X,%X add1=%X con1=%X\n",add0,dummy,add1,con1);
   printf("add2=%X con2=%X add3=%X con3=%X\n",add2,con2,add3,con3);
   printf("add4=%X con4=%X\n",add4,con4);
 
}
 
/*
Just an update on the previous problem I sent you (which I didn't discover
by the way) I modified the structure initialization code to read as
follows and it works fine (I know, so whats the problem??).
*/
 
/*
static struct  un1
       {
       int int1;
       unsigned int  unsign1;
       unsigned int  unsign2;
       int int2;
       } dummy = {1, 2, 3, 4};
*/
 
/*
shoved everything on the same line and inserted a blank between 'dummy='.
*/
 
