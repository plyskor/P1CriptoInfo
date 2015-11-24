#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcionesDES.h"
#include "Des_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};



char cajaSDES_Simp(unsigned char input , int caja){
	int bit, posrow=0 , poscol=0 ,poscolaux = 0, newpos=0 , i;
	char output = 0;
  unsigned char leoAux[8];
  unsigned char desiredbit, leo, aux;
  unsigned char androw = 192;
  unsigned char andcol = 240;
  aux = 0; 

	leo=0;
    poscol =0;
    leo = input;
      for(bit = 0; bit<6;bit++){//rotamos para obtener la pos de la columna
        newpos = bit+1;
        if(newpos==6){
          newpos=0;
        }
        desiredbit = leo & Positions[newpos];
       //printf("BIT : %d , POSITIONS : %d , DESIREDBIT : %d, LEO : %d\n",bit , Positions[newpos] ,desiredbit, leo);
        if (desiredbit != 0) {
              desiredbit = Positions[bit];
              poscol = desiredbit ^ poscol;
        }
      }
     
      poscolaux = poscol & andcol;
      poscolaux = poscolaux >> 4;
     // printf("columna %d\n", poscolaux);

      leo = poscol;
      poscol=0;
       for(bit = 0; bit<6;bit++){//rotamos para obtener la pos de la fila
        newpos = bit+4;
        if(newpos>5){
          newpos-=6;
        }
        desiredbit = leo & Positions[newpos];
        //printf("BIT : %d , POSITIONS : %d newpos %d , DESIREDBIT : %d, LEO : %d\n",bit , Positions[newpos] , newpos ,desiredbit, leo);

        if (desiredbit != 0) {
              desiredbit = Positions[bit];
              poscol = desiredbit ^ poscol;
        }
         
      }
      
      poscol = poscol & androw;
      leo = poscol;
     // printf("leo %d\n", leo);
      posrow=0;
      for(bit = 0; bit<2;bit++){//rotamos para hacer swap de los dos ultimos bits
        newpos = bit+1;
        if(newpos>=2){
          newpos-=2;
        }
        desiredbit = leo & Positions[newpos];
        //printf("BIT : %d , POSITIONS : %d newpos %d , DESIREDBIT : %d, LEO : %d\n",bit , Positions[newpos] , newpos ,desiredbit, leo);

        if (desiredbit != 0) {
              desiredbit = Positions[bit];
      
              posrow = desiredbit ^ posrow;
        }
        
        
      }
      posrow = posrow >> 6;
       // printf("fila %d\n", posrow);
      //printf("CAJA %d, FILA : %d , COLUMNA : %d\n", caja, posrow, poscolaux );
      
      output =S_BOXES[caja][posrow][poscolaux] <<4;
         //printf("out1 %d\n", output);
         return output;
       
}

char randascii(int t){
	int input = 0;
	 srand(t);
	input = rand()%254 + 1;
	printf("input %d\n", input);
	return input;
}

int main(int argc, char const *argv[])
{
	/* Este es un programa de prueba para comprobar el criterio SAC
	Cogemos una entrada cuyo primer bit es 0 y comprobamos la probabilidad que tiene
	cada bit de salida de ser 1.
	Hacemos lo mismo pero con la probabilidad de 0
	Luego complementamos es bit y vemos que las probabilidades de salida siguen siendo 
	las mismas (1/2)*/
	unsigned char output[4], input[6],inputaux[6], aux = 0, inputC = 0, aux1 = 0;
	double prob1[32], prob0[32], prob1C[4] , prob0C[4] , probsij[16];
	int  i, t, z,ind =0, randomnumer=0;
	for(i=0;i<6;i++){
		randomnumer= rand()%256;
		input[i] = randomnumer;
		printf("randomnumer %d\n",randomnumer);
	}
	
	
	
	memset(probsij, 0 , 16);

		memset(prob1, 0 , 64);
		memset(prob0, 0 , 64);
		memset(prob1C, 0 , 8);
		memset(prob0C, 0 , 8);
		memset(input, 0 , 6);
		memset(inputaux, 0 , 6);
		


	for(z=0; z< 32; z++){
		memset(output, 0 , 4);
		strcpy(inputaux, input);
		inputaux[z/8] = inputaux[z/8] ^ Positions[z%8];
		cajaSfun(inputaux, output);

		for (i = 0; i < 4; i++){
			for(t=0; t<8;t++){
				aux = output[i] & Positions[t];
				if(aux!= 0){
					prob1[t + (8*i)]++;
				}else{
					prob0[t + (8*i)]++;
				}

			}	
		}
	}

		for(t=0; t<32;t++){
			prob0[t] = prob0[t]/32;
			prob1[t] = prob1[t]/32;
		}
		for(t=0; t<32;t++){
			//printf("Para la entrada: %d las probabilidades son: \n", z);
			printf("prob0 [%d]: %lf\n", t , prob0[t]);
			printf("prob1 [%d]: %lf\n", t , prob1[t]);
		}



	return 0;
}