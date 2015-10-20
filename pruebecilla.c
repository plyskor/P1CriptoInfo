#include <stdio.h>

void main(void){
   long num, divi[10];
   int i, tam= 0, j;
   
   printf("Introduzca el número cuyos divisores quiere hallar: ");
   scanf("%ld", &num);
   
   i= 2;
   
   while( i <= num ){
      if( (num%i) == 0 ){    
         printf("%d ",i);
         /*divi[tam++] = i;*/
         num= num/i;
      }
      else
         i++;
   }
   return;
   
 /*  for( j= 0; j < tam; j++)
      printf("%ld  ",divi[j]);*/
}