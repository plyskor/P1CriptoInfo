#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcionesAES.h"
#include "AES_tables.c"

static unsigned char Positions[8] = {128,64,32,16,8,4,2,1}; 

int charAint(char *hexstring){
	//printf("hexString en fun %s\n", hexstring);
	int number = (int)strtol(hexstring, NULL, 16);
	//printf("int en fun %d\n",number );
	return number;
}

void intAHexaChar(int input , char *output){
	int i, andi[2] = {240,15};
	char aux;
	for (i=0;i<2;i++){
		aux = input & andi[i];
		if(aux>15) aux = aux>>4;
      	if(aux == 0) output[i] = '0';
      	else if(aux == 1) output[i] = '1';
	  	else if(aux == 2) output[i] = '2';
	  	else if(aux == 3) output[i] = '3';
	  	else if(aux == 4) output[i] = '4';
	  	else if(aux == 5) output[i] = '5';
	  	else if(aux == 6) output[i] = '6';
	  	else if(aux == 7) output[i] = '7';
	  	else if(aux == 8) output[i] = '8';
	  	else if(aux == 9) output[i] = '9';
	  	else if(aux == 10) output[i] = 'A';
	  	else if(aux == 11) output[i] = 'B';
	  	else if(aux == 12) output[i] = 'C';
	  	else if(aux == 13) output[i] = 'D';
      	else if(aux == 14) output[i] = 'E';
      	else if(aux == 15) output[i] = 'F';
   }	
   //printf("outputFunHexa %s\n", output);
}

int main(int argc, char const *argv[])
{
	int i, t;
	char hexstring[3],inputS[3],aux;
	char res;
	double prob0[8], prob1[8];

	memset(prob0, 0 , 16);
	memset(prob1, 0 , 16);
	memset(hexstring, 0 , 3);
	memset(inputS, 0 , 3);
	
	for (i = 0; i < 255; i++)
	{
		intAHexaChar(i , inputS);
		//printf("inputS %s\n", inputS);
		memset(hexstring, 0 , 3);
		cajaS_AESfun(inputS, hexstring);
		res = charAint(hexstring);
		for (t = 0; t < 8; t++)
		{
			//printbincharpad(Positions[i]);
			aux = res & Positions[t];
			//printf("aux :");
			//printbincharpad(aux);
			//printf("\n");
			if(aux!= 0){
				prob1[t]++;
			}else{
				prob0[t]++;
			}	
		}

	}
	for(t=0; t<8;t++){
		prob0[t] = prob0[t]/255;
		prob1[t] = prob1[t]/255;
	}
	for(t=0; t<8;t++){
		printf("prob0[%d] = %lf\n",t ,prob0[t]);
		printf("prob1[%d] = %lf\n",t ,prob1[t]);
	}


	return 0;
}