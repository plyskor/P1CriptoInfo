#include <stdio.h>
#include <stdlib.h>
#include "Des_tables.c"

static unsigned char Positions[8] = {1,2,4,8,16,32,64,128};

int main()
{
  /*unsigned char input[8] = {'a','b','c','d','e','f','g','h'};
  unsigned char permutation[8];
  unsigned char inverse[8];
  int i;
  for (i = 0; i < 8; i++) {
        permutation[i] = 0;
        inverse[i] = 0;
  }

 

  int IPinverse[8][8] ={{40,8,48,16,56,24,64,32},
                                      {39,7,47,15,55,23,63,31},
                                      {38,6,46,14,54,22,62,30},
                                      {37,5,45,13,53,21,61,29},
                                      {36,4,44,12,52,20,60,28},
                                      {35,3,43,11,51,19,59,27},
                                      {34,2,42,10,50,18,58,26},
                                      {33, 1,41, 9,49,17,57,25}};

  printf("\n Before: \n");
  for (i = 0; i < 8; i++) {
        printf(" %c", input[i]);
  }

  // Initial permutation
  int bit, newpos;
  unsigned char desiredbit;
  for (bit = 0; bit < 64; bit++) {
        // Get the location for where the bit will be sent and translate it to array index
        newpos = ((int)IP[bit])-1;
        // examine the bit we're currently considering
        desiredbit = input[bit/8] & Positions[bit%8];
        // if equal to zero that means no change necessary
        if (desiredbit != 0) {
              // else it was a 1 and we need to set the appropriate bit to 1
              desiredbit = Positions[newpos%8];
              permutation[newpos/8] = desiredbit ^ permutation[newpos/8];
             
        }
  }

  printf("\n Permutation: \n");
  for (i = 0; i < 8; i++) {
        printf(" %c", permutation[i]);
  }

  // Perform swap
 /* unsigned char tempcopy[4] = {0,0,0,0};
  int j;
  for (j = 0; j < 4; j++) {
        tempcopy[j] = permutation[j+4];
  }
  for (j = 0; j < 4; j++) {
        permutation[j+4] = permutation[j];
        permutation[j] = tempcopy[j];
  }

  // Reverse Permutation, remember to swap left side with right
  for (bit = 0; bit < 64; bit++) {
        newpos = ((int)IPinverse[bit/8][bit%8])-1;
        desiredbit = permutation[bit/8] & Positions[bit%8];
        if (desiredbit != 0) {
              desiredbit = Positions[newpos%8];
              inverse[newpos/8] = desiredbit ^ inverse[newpos/8];
        }
  }

 printf("\n Reverse Permutation: \n");
  for (i = 0; i < 8; i++) {
        printf(" %c", inverse[i]);
  }*/

  unsigned char input[6] = {'a','b','c','d','e','f'};
  unsigned char output[6];
  int caja, bit, posrow=0 , poscol=0 ,poscolaux, newpos=0;
  unsigned char desiredbit, leo;
  unsigned char androw = 3;
  unsigned char andcol = 15;
int aux; 

  for(caja=0;caja<8;caja++){
    leo = input[caja];
    printf("leo : %d\n", leo );
      for(bit = 0; bit<6;bit++){//rotamos para obtener la pos de la columna
        newpos = bit+1;
        if(newpos>=6){
          newpos-=6;
        }
        desiredbit = leo & Positions[newpos];
        if (desiredbit != 0) {
              desiredbit = Positions[bit];
              poscol = desiredbit ^ poscol;
        }
      }
      poscolaux = poscol & andcol;
      printf("COLUMNA : %d\n",poscolaux );

      leo = poscol;
      poscol=0;
       for(bit = 0; bit<6;bit++){//rotamos para obtener la pos de la fila
        newpos = bit+4;
        if(newpos>=6){
          newpos-=6;
        }
        desiredbit = leo & Positions[newpos];
        if (desiredbit != 0) {
              desiredbit = Positions[bit];
              poscol = desiredbit ^ poscol;
        }
         
      }

      poscol = poscol & androw;
      leo = poscol;
      posrow=0;
      for(bit = 0; bit<2;bit++){//rotamos para hacer swap de los dos ultimos bits
        newpos = bit+1;
        if(newpos>=1){
          newpos-=1;
        }
        desiredbit = leo & Positions[newpos];
        if (desiredbit != 0) {
              desiredbit = Positions[bit];
              posrow = desiredbit ^ posrow;
        }

      }
      printf("FILA : %d\n",posrow);

      aux = S_BOXES[caja][posrow][poscolaux];
      printf("%d\n",aux);
    }
       

  return 0;
}