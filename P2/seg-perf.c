#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"
#include "funcionesTextos.h"




int main(int argc, char const *argv[]){
	if(argc!=6){
		printf("ERROR! El programa debe ejecutarse con los siguientes argumentos: ./seg-perf {-P | -I} [-i filein] [-o fileout]\n");
		return -1;
	}

	FILE *in;
	FILE *out;
	FILE *fClaves;
	int l,i,c;
	int claves[2];

	if(!(in=fopen(argv[3],"r"))){
		printf("Fallo al abrir %s\n",argv[3]);
		return -1;
	}

	if(!(out=fopen(argv[5],"w"))){
		printf("Fallo al abrir %s\n",argv[5]);
		return -1;
	}

	if(!(fClaves=fopen("claves.out","w"))){
		printf("Fallo al abrir claves.out\n");
		return -1;
	}
	
	while((l=fgetc(in))!=EOF){
		if((l=trataCaracter(l))==-1) continue;
		printf("l= %d\n",l);
		if(strcmp(argv[1],"-P")==0){
			for (i = 0; i < 2; ++i)
			{
				claves[i]=generaClavesEquiprobable(26);
				if(fputc(claves[i],fClaves)==EOF){
					printf("ERROR al escribir en fichero\n");
					return -1;
				}
			}

		}else if(strcmp(argv[1],"-I")==0){
			for (i = 0; i < 2; ++i)
			{
				claves[i]=generaClavesNoEquiprobable(26);
				if(fputc(claves[i],fClaves)==EOF){
					printf("ERROR al escribir en fichero\n");
					return -1;
				}	
			}
		}else{
			printf("Primer argumento inválido\n");
			return -1;
		}
		printf("claves : %d, %d\n",claves[0],claves[1]);
		c = ((claves[0]*l) + claves[1])%26;
		c+=65;
		if(fputc(c,out)==EOF){
			printf("ERROR al escribir en fichero\n");
			return -1;
		}
	}

	/*
	Falta:
	LLamar a la función de tratar texto
	Hacer el afin
	Llamar a la función de las probabilidades
	Irlo escribiendo todo en out
	*/	
	fclose(in);
	fclose(out);
	fclose(fClaves);

	return 0;
}