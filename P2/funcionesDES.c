#include <stdio.h>
#include <stdlib.h>
#include "Des_tables.c"

static unsigned char Positions[8] = {1,2,4,8,16,32,64,128};





void PC1fun(unsigned char *input, unsigned char *permutation){
  /* EXPLICACION CÓDIGO:
    En newpos meto la posición del bit que quiero meter en el bit que estoy cambiando.

    Miro si ese bit es un 0 (positions[bit%8] tiene un 1 en el bit que estoy mirando).

    Si es un 0 no hago nada ya que he inicializado permutation a 0.

    Si no es un cero meto en desire bit un 1 en la posicion apropiada y hago un 
    XOR con el byte que ya hubiera en permutation, de forma que solo cambio el bit deseado
  */

  //permutation debe estar inicializada a 0
  int bit, newpos;
  unsigned char desiredbit;
  for (bit = 0; bit < 56; bit++) {
       
        newpos = ((int)PC1[bit])-1;
        desiredbit = input[bit/8] & Positions[bit%8];
        if (desiredbit != 0) {
              desiredbit = Positions[newpos%8];
              permutation[newpos/8] = desiredbit ^ permutation[newpos/8];
        }
  }


}

void quitarParidad(unsigned char *input, unsigned char *output){
  int bit, outbit = 0;
  for (bit = 0; bit < 64; bit++)
  {
    if(((bit+1)%8)!=0){
      output[outbit/8] = input[bit/8];
      outbit++; 
    }
    
  }
}

void PC2fun(unsigned char *input, unsigned char *permutation){
//permutation debe estar inicializada a 0
  int bit, newpos;
  unsigned char desiredbit;
  for (bit = 0; bit < 48; bit++) {
        newpos = ((int)PC2[bit])-1;
        desiredbit = input[bit/8] & Positions[bit%8];
        if (desiredbit != 0) {
              desiredbit = Positions[newpos%8];
              permutation[newpos/8] = desiredbit ^ permutation[newpos/8];
        }
  }


}

void rotarVector(unsigned char *input, unsigned char *permutation, int round){
  //permutation debe estar inicializada a 0
  int rot = ROUND_SHIFTS[round], bit , newpos;

  unsigned char desiredbit;
  for (bit = 0; bit < 56; bit++) {
       
        newpos = bit+rot;
        if(newpos>=56){
          newpos-=56;
        }
        desiredbit = input[bit/8] & Positions[bit%8];
        if (desiredbit != 0) {
              desiredbit = Positions[newpos%8];
              permutation[newpos/8] = desiredbit ^ permutation[newpos/8];
        }
  }


}


void cajaSfun(unsigned char *input, unsigned char *output){
  
  int caja, bit, posrow=0 , poscol=0 ,poscolaux, newpos=0;
  unsigned char desiredbit, leo, aux;
  unsigned char androw = 3;
  unsigned char andcol = 15;
  aux = 0;

  for(caja=0;caja<8;caja++){
    leo = input[caja];
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
      if((caja%2)==1){
        aux = 0x00 ^ S_BOXES[caja][posrow][poscolaux];
       
      }else{
        output[caja/2] = S_BOXES[caja][posrow][poscolaux] << 4;
         output[caja/2] =  output[caja/2] ^ aux;
         aux = 0;
      }
// me falta ver como lo cojo de 6 en 6 en vez de de 8 en 8.
    
  }
}