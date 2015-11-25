#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcionesDES.h"
#include "Des_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};


char randascii(int t){
	int input = 0;
	 srand(t);
	input = rand()%254 + 1;
	printf("input %d\n", input);
	return input;
}

int main(int argc, char const *argv[])
{
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
		


	for(z=0; z< 48; z++){
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