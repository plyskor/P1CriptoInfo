#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"
#include "funcionesTextos.h"
#include "funcionesAES.h"




int main(int argc, char const *argv[]){
	
	char input[2] ;
	char output[2];
	char *endptr;
	strcmp(input,"61");
	long int intege1 , intege2;
	

	cajaS_AESfun("61", output);

	printf("output0 %c\n",output[0]);
	printf("output1 %c\n",output[1]);

	intege1 = strtol(output, &endptr, 8);

	printf("strtol = %ld\n", intege1);

	return 0;
}