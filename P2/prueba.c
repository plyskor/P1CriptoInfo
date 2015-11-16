#include <stdio.h>
#include <stdlib.h>
#include "Des_tables.c"
#include "funcionesDES.h"

static unsigned char Positions[8] = {1,2,4,8,16,32,64,128};

int main()
{
 unsigned char input[8] = {'a','b','c','d','e','f','g','h'};
  unsigned char **output;
  int i,j;

  output = (unsigned char**)malloc((sizeof(unsigned char*)) * 16);
  for(i = 0; i<16; i++){
      output[i] = (unsigned char*)malloc((sizeof(unsigned char))*6);
  }
  

     for(i=0;i<16;i++){
      for(j=0;j<6;j++){
        output[i][j] = 0;
      }
     }
  generacionKi(input, output);

  for(i=0;i<16;i++){
    for(j=0;j<6;j++){
      printf("k_i= %d , i = %d\n",output[i][j],i);
    }
  }

  for(i = 0; i<16; i++){
    free(output[i]);
  }
  free(output);
  return 0;
}