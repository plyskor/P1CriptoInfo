#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "funcionesAES.h"
#include "AES_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};

void intAHexaChar(int input , char *output){
	int i, andi[2] = {240,15};
	int aux[2];
	for (i=0;i<2;i++){
		aux[i] = input & andi[i];
		if(aux[i]> 15) aux[i]= aux[i]>>4;
		
      	if(aux[i] == 0) output[i] = '0';
      	else if(aux[i] == 1) output[i] = '1';
	  	else if(aux[i] == 2) output[i] = '2';
	  	else if(aux[i] == 3) output[i] = '3';
	  	else if(aux[i] == 4) output[i] = '4';
	  	else if(aux[i] == 5) output[i] = '5';
	  	else if(aux[i] == 6) output[i] = '6';
	  	else if(aux[i] == 7) output[i] = '7';
	  	else if(aux[i] == 8) output[i] = '8';
	  	else if(aux[i] == 9) output[i] = '9';
	  	else if(aux[i] == 10) output[i] = 'A';
	  	else if(aux[i] == 11) output[i] = 'B';
	  	else if(aux[i] == 12) output[i] = 'C';
	  	else if(aux[i] == 13) output[i] = 'D';
      	else if(aux[i] == 14) output[i] = 'E';
      	else if(aux[i] == 15) output[i] = 'F';
   }	
   
}
int charAint(char *hexstring){
	int number = (int)strtol(hexstring, NULL, 16);
	return number;
}
void randascii(char output){
struct timeval temp;
  int pid ,randomnumer=0,i;
gettimeofday(&temp, NULL);
srand(temp.tv_usec * temp.tv_sec * pid);
	
		randomnumer= rand()%255;

		output = randomnumer;
		
	
}

int main(int argc, char const *argv[])
{
	unsigned char inputS[3], output[3],input, aux = 0, inputC = 0, aux1 = 0;
	double prob1[8][8], prob0[8][8] , probsij[256][8];
	int  i, t, z,ind =0, randomnumer=0,h, outputaux=0, ncaja=0 ,inputaux =0;
	FILE *out;
	out = fopen(argv[4], "w");

	
	memset(probsij, 0 , 256*8);
	memset(inputS , 0 ,3);
	memset(output , 0 ,3);

		memset(prob1, 0 , 66);
		memset(prob0, 0 , 64);
	


	for(z=0; z< 1000; z++){

		intAHexaChar(z , inputS);

		if(strcmp(argv[2],"-C") == 0){
			cajaS_AESfun(inputS, output);
		}else{
			cajaSINV_AESfun(inputS,output);
		}
		
		
		for(h=0;h<8;h++){
			memset(output , 0 ,3);
			inputaux = z;
			inputaux = inputaux ^ Positions[h];
			memset(inputS , 0 ,3);
			intAHexaChar(inputaux , inputS);
		
			if(strcmp(argv[2],"-C") == 0){
				cajaS_AESfun(inputS, output);
			}else{
				cajaSINV_AESfun(inputS,output);
			}
			outputaux=0;
			outputaux = charAint(output);


				probsij[outputaux][h]++;
				for(t=0; t<8;t++){
					aux = outputaux & Positions[t];
					if(aux!= 0){
						prob1[t][h]++;
					}else{
						prob0[t][h]++;
					}
	
				}
			
		}
	}
	for(h=0;h<8;h++){
		for(t=0; t<8;t++){
			prob0[t][h] = prob0[t][h]/(1000);
			prob1[t][h] = prob1[t][h]/(1000);
		}
	}
	for(h=0;h<8;h++){
		for(t=0; t<8;t++){

			printf("prob0 [%d][%d]: %lf\n", t ,h, prob0[t][h]);
			fprintf(out, "prob0 [%d][%d]: %lf\n", t ,h, prob0[t][h]);
			printf("prob1 [%d][%d]: %lf\n", t ,h, prob1[t][h]);
			fprintf(out,"prob1 [%d][%d]: %lf\n", t ,h, prob1[t][h]);
		}
	
	}
	for(h=0;h<8;h++){
		for (i = 0; i < 256; i++)
		{
			printf("probbsij[%d][%d] = %lf\n", i,h, probsij[i][h]/1000);
			fprintf(out,"probbsij[%d][%d] = %lf\n", i,h, probsij[i][h]/1000);
		}
	}

	fclose(out);


	return 0;
}