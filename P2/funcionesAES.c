#include <stdio.h>
#include <stdlib.h>
#include "AES_tables.c"
#include "funcionesAES.h"



int hexaAdecimal(char hexadecimal){
	//printf("hexadecimal %c\n",hexadecimal);
	if(hexadecimal>96 && hexadecimal<103){
		//printf("Minuscula\n");
		hexadecimal-= 32;
	}
	if(hexadecimal>64 && hexadecimal< 71){
		//printf("hexaMayus %d\n",hexadecimal);
		//printf("hmm.. %d\n", (int)(hexadecimal-54));
		return (int)((hexadecimal-54)-'0');
	}else{
		return (int)(hexadecimal-'0');
	}
} 

void cajaS_AESfun(char *input, char *output){
	//recibo un char[3] , que es un número en hexadecimal y \0 y devuelvo lo mismo
	int row =(int)hexaAdecimal(input[0]);
	printf("row %d\n",row );
	int column = (int)hexaAdecimal(input[1]);
	printf("column %d\n",column );
	strcpy(output,DIRECT_SBOX[row][column]);
	printf("outS %s\n", output);
}

/*void noLinealidadSboxes(char *a, char *b){
	//función lineal : f(a+b) = f(a) + f(b)
	char output1[2];
	char output2[2];
	cajaS_AESfun(a, output1);
	cajaS_AESfun(b,output2);


}*/