#include <stdio.h>
#include <stdlib.h>
#include "Des_tables.c"
#include "funcionesDES.h"

static unsigned char Positions[8] = {1,2,4,8,16,32,64,128};





void PC1fun(unsigned char *input, unsigned char *permutation){
  /* EXPLICACION CÓDIGO:
    En newpos meto la posición del bit que quiero meter en el bit que estoy cambiando.

    Miro si ese bit es un 0 (positions[bit%8] tiene un 1 en el bit que estoy mirando).

    Si es un 0 no hago nada ya que he inicializado permutation a 0.

    Si no es un cero meto en desire bit un 1 en la posicion apropiada y hago un 
    XOR con el byte que ya hubiera en permutation, de forma que solo cambio el bit deseado
  */
/******************************¿ESTA AL REVES????****************************

 Deberia ser: 
desiredbit = input[newpos/8] & Positions[newpos%8]; 
permutation[bit/8] = desiredbit ^ permutation[bit/8];

*****************************************************************************/

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
        if(newpos>=28){
        
          newpos-=28;
        }
        desiredbit = input[bit/8] & Positions[bit%8];
        if (desiredbit != 0) {
              desiredbit = Positions[newpos%8];
              permutation[newpos/8] = desiredbit ^ permutation[newpos/8];
        }
  }


}


void cajaSfun(unsigned char *input, unsigned char *output){
  
  int caja, bit, posrow=0 , poscol=0 ,poscolaux = 0, newpos=0 , i;
  unsigned char leoAux[8];
  unsigned char desiredbit, leo, aux;
  unsigned char androw = 3;
  unsigned char andcol = 15;
  aux = 0;

  for (i = 0; i < 8; ++i)
  {
    leoAux[i] = 0;
    output[i/2] = 0;
  }

  for (i = 0; i < 48; ++i)
  {
    leo = input[i/8];
    desiredbit = leo & Positions[i%8];
        if (desiredbit != 0) {
              desiredbit = Positions[i%6];
              leoAux[i/6] = desiredbit ^ leoAux[i/6];
        }

  }

  for(caja=0;caja<8;caja++){
    leo=0;
    poscol =0;
    leo = leoAux[caja];
      for(bit = 0; bit<6;bit++){//rotamos para obtener la pos de la columna
        newpos = bit+1;
        if(newpos>=6){
          newpos-=6;
        }
        desiredbit = leo & Positions[newpos];
        //printf("BIT : %d , POSITIONS : %d , DESIREDBIT : %d, LEO : %d\n",bit , Positions[newpos] ,desiredbit, leo);
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
        if(newpos>=2){
          newpos-=2;
        }
        desiredbit = leo & Positions[newpos];
        if (desiredbit != 0) {
              desiredbit = Positions[bit];
      
              posrow = desiredbit ^ posrow;
        }
        
      }
      //printf("CAJA %d, FILA : %d , COLUMNA : %d\n", caja, posrow, poscolaux );
      if((caja%2)==0){
        aux = 0x00 ^ S_BOXES[caja][posrow][poscolaux];
       
      }else{
        output[caja/2] = S_BOXES[caja][posrow][poscolaux] << 4;
         output[caja/2] =  output[caja/2] ^ aux;
         aux = 0;
      }
    
  }
}


void DES(unsigned char *input, unsigned char *k ,unsigned char *output){
  //P1
  //Rondas(16)
    //F:
      // Expando r0 y hago XOR con la clave
      //Caja S con el resultado
      //Permutación P
    //XOR con L0

  


}

void generacionKi(unsigned char *K , unsigned char **ki){
  //Para generacion de ki:
    //Quito bits de paridad
    //Permutacion PC1
    //Desplazo (cada uno de los subloques)
    //Permutacion PC2
    //Concateno
  unsigned char permutationP1[56];
  unsigned char permutationRot[56];
  unsigned char permutationP2[48];
  unsigned char  Kaux[56];
  int i,t;
  for (i = 0; i < 56; i++)
  {
    permutationP1[i] = 0;
    permutationRot[i] = 0;
  }
  quitarParidad(K, Kaux);
  PC1fun(Kaux, permutationP1);

  for (i = 0; i < 16; i++)
  {
    for (t = 0; t < 48; t++)
    {
      permutationP2[t] =0;
    }
    //¿como separo la cadena?
    rotarVector(permutationP1, permutationRot, i);
    PC2fun(permutationRot, permutationP2);

  }


}