/* fort.c */

/* This is a code fragment to show how to call FORTRAN
 * subroutines from C.  Your mileage may vary
 */

fortran int ABC();
fortran double DEF();

double
fort (number)
int number;
{
    int i,j;
    double bnum;

    i = number * 2;
    j = ABC(number);
    bnum = DEF(i,0,j,41);
    return bnum;
}
