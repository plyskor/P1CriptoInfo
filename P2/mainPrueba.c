#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"
#include "funcionesTextos.h"
#include "funcionesAES.h"




int main(int argc, char const *argv[]){
	
	char input[2] ;
	char output[2];
	strcmp(input,"61");

	cajaS_AESfun("61", output);

	printf("output0 %d\n",output[0]);
	printf("output1 %d\n",output[1]);


	return 0;
}