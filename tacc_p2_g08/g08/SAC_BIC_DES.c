#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "funcionesDES.h"
#include "Des_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};


void randascii(char *output){
struct timeval temp;
  int pid ,randomnumer=0,i;
	memset(output, 0 , 7);
gettimeofday(&temp, NULL);
srand(temp.tv_usec * temp.tv_sec * pid);
	for(i=0;i<6;i++){
		randomnumer= rand()%256;
		output[i] = randomnumer;
		//printf("randomnumer %d\n",randomnumer);
	}
}

int main(int argc, char const *argv[])
{
	unsigned char output[5], input[7],inputaux[7], aux = 0, inputC = 0, aux1 = 0;
	double prob1[32][48], prob0[32][48], prob1C[4] , prob0C[4] , probsij[16][48];
	int  i, t, z,ind =0, randomnumer=0,h, nbitsalida=0, ncaja=0;
	
	memset(probsij, 0 , 16*2*48);

		memset(prob1, 0 , 64*48);
		memset(prob0, 0 , 64*48);
		memset(prob1C, 0 , 8);
		memset(prob0C, 0 , 8);
		memset(inputaux, 0 , 7);
		


	for(z=0; z< 1000; z++){
		randascii(input);
		memset(output, 0 , 5);
		
		
		cajaSfun(input, output);
		for(h=0;h<48;h++){
			memset(inputaux, 0 , 7);
			strcpy(inputaux,input);
			inputaux[h/8] = inputaux[h/8] ^ Positions[h%8];
			memset(output, 0 , 5);
			cajaSfun(inputaux, output);

			ncaja = h/6;
			nbitsalida = ncaja*4;

			if((nbitsalida%8)<4){
				//printf("ESTOY MIRANDO EL BYE %d , la salida es: %d\n",nbitsalida/8,output[nbitsalida/8]>>4);
				probsij[(15&(output[nbitsalida/8]>>4))][h]++;
				for(t=0; t<4;t++){
					aux = output[nbitsalida/8] & Positions[t];
					if(aux!= 0){
						prob1[((nbitsalida/8)*8)+t][h]++;
					}else{
						prob0[((nbitsalida/8)*8)+t][h]++;
					}
	
				}
			}else{
				//printf("ESTOY MIRANDO EL BYE %d , la salida es: %d\n",nbitsalida/8,15 & output[nbitsalida/8]);
				probsij[(15 & (output[nbitsalida/8]))][h]++;
				for(t=4; t<8;t++){
					aux = output[nbitsalida/8] & Positions[t];
					if(aux!= 0){
						prob1[((nbitsalida/8)*8)+t][h]++;
					}else{
						prob0[((nbitsalida/8)*8)+t][h]++;
					}
	
				}
			}
		}
	}
	for(h=0;h<48;h++){
		for(t=0; t<32;t++){
			prob0[t][h] = prob0[t][h]/(1000);
			prob1[t][h] = prob1[t][h]/(1000);
		}
	}
	for(h=0;h<48;h++){
		for(t=0; t<4;t++){

			printf("prob0 [%d][%d]: %lf\n", ((h/6)*4)+t ,h, prob0[((h/6)*4)+t][h]);
			printf("prob1 [%d][%d]: %lf\n", ((h/6)*4)+t ,h, prob1[((h/6)*4)+t][h]);
		}
	
	}
	for(h=0;h<48;h++){
		for (i = 0; i < 16; i++)
		{
			printf("probbsij[%d][%d] = %lf\n", i,h, probsij[i][h]/1000);
		}
	}



	return 0;
}