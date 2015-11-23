#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcionesDES.h"
#include "Des_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};

void printbincharpad(unsigned char c)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar(' ');
    return;
}
void printbinarray(unsigned char*c,int tam){
    int i;
    for(i=0;i<tam;i++){
        printbincharpad(c[i]);
    }
    printf("\n");
    return;
}

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
      printf("CAJA %d, FILA : %d , COLUMNA : %d\n", caja, posrow, poscolaux );
      
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
	unsigned char output = 0, input =0, aux = 0, inputC = 0;
	double prob1[4], prob0[4], prob1C[4] , prob0C[4] ;
	int  i, t;
	memset(prob1, 0 , 8);
	memset(prob0, 0 , 8);
	memset(prob1C, 0 , 8);
	memset(prob0C, 0 , 8);

	for(t=0; t<254; t++){
		input = t+1;
		printf("input %d\n", input);
		printbincharpad(input);
		output = cajaSDES_Simp(input, 0);
		printf("output %d\n", output);
		printbincharpad(output);
		printf("\n");
		for (i = 0; i < 4; i++)
		{
			printbincharpad(Positions[i]);
			aux = output & Positions[i];
			printf("aux :");
			printbincharpad(aux);
			printf("\n");
			if(aux!= 0){
				prob1[i]++;
			}else{
				prob0[i]++;
			}	
		}
		//Complemento input
		inputC = input ^ 255;
		output = 0;
		printf("input %d\n", inputC);
		printbincharpad(inputC);
		output = cajaSDES_Simp(inputC, 0);
		printf("output %d\n", output);
		printbincharpad(output);
		printf("\n");
		for (i = 0; i < 4; i++)
		{
			aux = output & Positions[i];
			printf("aux :");
			printbincharpad(aux);
			printf("\n");
			if(aux!= 0){
				prob1C[i]++;
			}else{
				prob0C[i]++;
			}	
		}
	}

	/*for(t=0; t<4;t++){
		printf("prob0 [%d]: %lf\n", t , prob0[t]);
		printf("prob1 [%d]: %lf\n", t , prob1[t]);
		printf("prob0C[%d] : %lf\n",t ,  prob0C[t]);
		printf("prob1C[%d] : %lf\n",t ,  prob1C[t]);
	}*/


	for(t=0; t<4;t++){
		prob0[t] = prob0[t]/254;
		prob1[t] = prob1[t]/254;
		prob0C[t] = prob0C[t]/254;
		prob1C[t] = prob1C[t]/254;
	}

	for(t=0; t<4;t++){
		printf("prob0 [%d]: %lf\n", t , prob0[t]);
		printf("prob1 [%d]: %lf\n", t , prob1[t]);
		printf("prob0C[%d] : %lf\n",t ,  prob0C[t]);
		printf("prob1C[%d] : %lf\n",t ,  prob1C[t]);
	}

	return 0;
}