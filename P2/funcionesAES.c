#include <stdio.h>
#include <stdlib.h>
#include "AES_tables.c"
#include "funcionesAES.h"



int hexaAdecimal(char hexadecimal){
	if(hexadecimal>96 && hexadecimal<103){
		hexadecimal-= 32;
	}
	if(hexadecimal>64 && hexadecimal< 71){
		return (int)((hexadecimal-54)-'0');
	}else{
		return (int)(hexadecimal-'0');
	}
} 

void cajaS_AESfun(char *input, char *output){
	//recibo un char[3] , que es un número en hexadecimal y \0 y devuelvo lo mismo
	int row =(int)hexaAdecimal(input[0]);
	//printf("row %d\n",row );
	int column = (int)hexaAdecimal(input[1]);
	//printf("column %d\n",column );
	strcmp(output,DIRECT_SBOX[row][column]);
}

