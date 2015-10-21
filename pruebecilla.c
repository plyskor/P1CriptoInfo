#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "funciones.h"


int values[] = {4,8,400,28,4,444,12};



int main()
{
   int n;

   n = mcd_numeros(values,7);

   printf("\nmcd = %d \n",n);
  
  
   return(0);
}