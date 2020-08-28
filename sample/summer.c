#include <stdio.h>

int main () {
/*  This program sums five numbers input by the user  */
   int indx_i, inputs [5];
   float average, fl;

   printf ("Input five integers, separated by commas\n");
   scanf ("%d %d %d %d %d",
     &inputs [0], &inputs [1], &inputs [2],
     &inputs [3], &inputs [4]);

   printf ("%d, %d, %d, %d, %d\n",
     inputs [0], inputs [1], inputs [2],
     inputs [3], inputs [4]);

   for (indx_i=0; indx_i < 5; indx_i++)
      inputs [4] += inputs [indx_i];

   average = inputs [4] / 5.0;
   printf ("Sum is %d; average is %f\n", inputs [4], average);
}
