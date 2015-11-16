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
        desiredbit = input[newpos/8] & Positions[newpos%8]; 
        if (desiredbit != 0) {
              desiredbit = Positions[bit%8];
              permutation[bit/8] = desiredbit ^ permutation[bit/8];
        }
  }
}

void quitarParidad(unsigned char *input, unsigned char *output){
  int i;
  int bit, outbit = 0;
  char desiredbit;
  i=0;
  for (bit = 0; bit < 64; bit++)
  {
    if(((bit+1)%8)!=0){
      desiredbit = input[bit/8] & Positions[(bit)%8];

      if(desiredbit!=0){
        output[outbit/8] = Positions[(bit-i)%8] ^ output[outbit/8];
      }
       outbit++;
    }else{
      i++;
    }
    
  }
}


/*void ponerParidad(unsigned char *input, unsigned char *output){
  //?¿??¿?¿?¿¿?¿?¿?¿¿
  //hacemos paridad impar
  int byte, bit , i ,contparidad = 0;
  char outbit = 0;
  for (i = 0; i < 56; i++)
  {
    output[i] = 0;
  }
  for (byte = 0; byte < 7; byte++)
  {
    for(bit =0 ; bit < 7 ; bit++){
      outbit = input[byte/7] && Positions[bit];
      if(outbit!=0){
        output[byte] = outbit ^ output[byte];
        contparidad ++;
      } 
    }
    if((contparidad%2)==1){
      output[byte] = Positions[7] ^ output[byte];
    }    
  }
}*/

void PC2fun(unsigned char *input, unsigned char *permutation){
//permutation debe estar inicializada a 0
  int bit, newpos;
  /*for (bit=0; bit < 7; bit++){
    printf("input[%d] = %d\n",bit , input[bit]);
  }*/
  unsigned char desiredbit;
  for (bit = 0; bit < 48; bit++) {
       
        newpos = ((int)PC2[bit])-1;
        desiredbit = input[newpos/8] & Positions[newpos%8]; 
        if (desiredbit != 0) {
              desiredbit = Positions[bit%8];
              permutation[bit/8] = desiredbit ^ permutation[bit/8];
             // printf("permutation[%d] = %d, newpos = %d , desiredbit =%d\n",bit/8 , permutation[bit/8], newpos, desiredbit);
        }
  }
  
}

void rotarVector(unsigned char *input, unsigned char *permutation, int round){
  //permutation debe estar inicializada a 0
  int rot = ROUND_SHIFTS[round], bit , newpos;
 /* for (bit=0; bit < 7; bit++){
    printf("inputRot[%d] = %d\n",bit , input[bit]);
  }*/
  unsigned char desiredbit;
  for (bit = 0; bit < 56; bit++) {
       
        newpos = bit+rot;
        if(rot ==1){
          if(newpos==28 || newpos == 56){
           newpos-=28;
          }
        }

        if(rot ==2){
          if(newpos==28 || newpos==29 || newpos >= 56){
           newpos-=28;
          }
        }
        
        desiredbit = input[newpos/8] & Positions[newpos%8]; 
        if (desiredbit != 0) {
              desiredbit = Positions[bit%8];
              permutation[bit/8] = desiredbit ^ permutation[bit/8];
              //printf("permutationRot[%d] = %d, newpos = %d , desiredbit =%d\n",bit/8 , permutation[bit/8], newpos, desiredbit);
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
 unsigned char **ki;
  int i,j;

  ki = (unsigned char**)malloc((sizeof(unsigned char*)) * 16);
  for(i = 0; i<16; i++){
      ki[i] = (unsigned char*)malloc((sizeof(unsigned char))*6);
  }
  
    generacionKi(k, ki);

  //P1
  //Rondas(16)
    //F:
      // Expando r0 y hago XOR con la clave
      //Caja S con el resultado
      //Permutación P
    //XOR con L0

  
for(i = 0; i<16; i++){
    free(ki[i]);
  }
  free(ki);


}

void generacionKi(unsigned char *K , unsigned char **ki){
  //Para generacion de ki:
    //Quito bits de paridad
    //Permutacion PC1
    //Desplazo (cada uno de los subloques)
    //Permutacion PC2
    //Concateno
  unsigned char *permutationP1;
  unsigned char *permutationRot;
  unsigned char *permutationP2;
  unsigned char *Kaux;

  permutationP1 = (unsigned char*)malloc(7);
  permutationRot = (unsigned char*)malloc(7);
  permutationP2 = (unsigned char*)malloc(6);
  Kaux = (unsigned char*)malloc(7);
  
  int i,t;
  for (i = 0; i < 7; i++)
  {
    permutationP1[i] = 0;
    permutationRot[i] = 0;
    Kaux[i] = 0; 
  }
  //printf("Antes de quitar paridad\n");
  /*quitarParidad(K, Kaux);
for(i=0;i<7;i++){
      printf("Kaux[%d] = %d\n",i, Kaux[i]);
    }  printf("Antes de PC1\n");*/
  PC1fun(K, permutationP1);

  /*for(i=0;i<7;i++){
      printf("pc1[%d] = %d\n",i, permutationP1[i]);
    }*/

  for (i = 0; i < 16; i++)
  {
    for (t = 0; t < 48; t++)
    {
      permutationP2[t] =0;
    }
    // a rotarVector le paso toda la cadena junta pero los rota por separado y devuelve lass dos cadenas concatenadas
 

    rotarVector(permutationP1, permutationRot, i);
   
    for (t = 0; t < 7; t++)
    {
      permutationP1[t] =permutationRot[t];
    }
     
    PC2fun(permutationRot, permutationP2);
   

    for(t=0 ; t< 6 ; t++){
      ki[i][t] = permutationP2[t];
      printf("k = %d\n",ki[i][t]);
    }
  }

  /**************¿¿PORQUE PETAAN????**************/
  /*free(permutationRot);
  free(permutationP2);
  free(permutationP1);
  free(Kaux);*/


}