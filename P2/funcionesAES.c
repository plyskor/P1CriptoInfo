#include <stdio.h>
#include <stdlib.h>
#include "AES_tables.c"
#include "funcionesAES.h"



int hexaAdecimal(char hexadecimal){


      	if(hexadecimal == '0') return 0;;
      	if(hexadecimal == '1') return 1;
	  	if(hexadecimal == '2') return 2;
	  	if(hexadecimal == '3') return 3;
	  	if(hexadecimal == '4') return 4;
	  	if(hexadecimal == '5') return 5;
	  	if(hexadecimal == '6') return 6;
	  	if(hexadecimal == '7') return 7;
	  	if(hexadecimal == '8') return 8;
	  	if(hexadecimal == '9') return 9;
	  	if((hexadecimal == 'A') || (hexadecimal == 'a' )) return 10;
	  	if((hexadecimal == 'B') || (hexadecimal == 'b') )return 11;
	  	if((hexadecimal == 'C') || (hexadecimal == 'c') )return 12;
	  	if((hexadecimal == 'D') || (hexadecimal == 'd') )return 13;
      	if((hexadecimal == 'E') || (hexadecimal == 'e') )return 14;
      	if((hexadecimal == 'F') || (hexadecimal == 'f') )return 15;
	//printf("hexadecimal %d\n",hexadecimal);
	if(hexadecimal>96 && hexadecimal<103){
		//printf("Minuscula\n");
		hexadecimal-= 32;
	}
	if(hexadecimal>64 && hexadecimal< 71){
		//printf("hexaMayus %d\n",hexadecimal);
		//printf("hmm.. %d\n", (int)(hexadecimal-54));
		return (int)((hexadecimal-54));
	}else{
		return atoi(&hexadecimal);
	}
} 

void cajaS_AESfun(char *input, char *output){
	//recibo un char[3] , que es un número en hexadecimal y \0 y devuelvo lo mismo
	//printf("input de la Caja S %s\n", input);
	int row =(int)hexaAdecimal(input[0]);
	//printf("row %d\n",row );
	int column = (int)hexaAdecimal(input[1]);
	//printf("column %d\n",column );
	strcpy(output,DIRECT_SBOX[row][column]);
	//printf("outS %s\n", output);
}

/*void noLinealidadSboxes(char *a, char *b){
	//función lineal : f(a+b) = f(a) + f(b)
	char output1[2];
	char output2[2];
	cajaS_AESfun(a, output1);
	cajaS_AESfun(b,output2);


}*/