#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"
#include "funcionesTextos.h"
#include "probabilidad.h"



int main(int argc, char const *argv[]){
    double *p,**pp;
    int m;
    p = (double *)malloc (26*sizeof(double));
    if(!p)return -1;
    pp=(double **)malloc(26*sizeof(double*));
    if(!pp)return -1;
    for(m=0;m<26;m++){
        pp[m]=(double*)malloc(26*sizeof(double));
            if(!pp[m])return -1;
    }
    
    int car;
        if(argc!=6){
		printf("ERROR! El programa debe ejecutarse con los siguientes argumentos: ./seg-perf {-P | -I} [-i filein] [-o fileout]\n");
		return -1;
	}

	FILE *in;
	FILE *out,*tratado ,*probsOut;
	FILE *fClaves;
	int l,i,c;
	int claves[2];

	if(!(in=fopen(argv[3],"r"))){
		printf("Fallo al abrir %s\n",argv[3]);
		return -1;
	}
        if(!(tratado=fopen("textoTratado.txt","w"))){
		printf("Fallo al guardar el archivo de tratado\n");
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
                fputc((l+65),tratado);
		if(strcmp(argv[1],"-P")==0){
			
				claves[0]=generaClaveAEquiprobable(26);
				claves[1]=generaClaveBEquiprobable(26);
			

		}else if(strcmp(argv[1],"-I")==0){
			
			for (i = 0; i < 2; i++)
			{
				claves[i]=generaClavesNoEquiprobable(26);
				
			}
		}else{
			printf("Primer argumento inválido\n");
			return -1;
		}
		fprintf(fClaves,"claves : %d, %d\n",claves[0],claves[1]);
		c = ((claves[0]*l) + claves[1])%26;
		c+=65;
		if(fputc(c,out)==EOF){
			printf("ERROR al escribir en fichero\n");
			return -1;
		}
                
	}
        fclose(tratado);
        fclose(out);
        if(!(tratado=fopen("textoTratado.txt","r"))){
		printf("Fallo al abrir el archivo de tratado\n");
		return -1;
	}
        if(!(out=fopen(argv[5],"r"))){
		printf("Fallo al abrir %s\n",argv[5]);
		return -1;
	}
        calculaProbs(tratado, p);
        fclose(tratado);
        fclose(out);
        if(!(tratado=fopen("textoTratado.txt","r"))){
		printf("Fallo al abrir el archivo de tratado\n");
		return -1;
	}
        if(!(out=fopen(argv[5],"r"))){
		printf("Fallo al abrir %s\n",argv[5]);
		return -1;
	}
        calculaProbsCondicionadas(tratado, out, pp);
	/*
	Llamar a la función de las probabilidades
	Irlo escribiendo todo en out
	*/

	 if(!(probsOut=fopen("probabilidades.out","w"))){
		printf("Fallo al abrir archivo\n");
		return -1;
	}
        car=65;
        for(i=0;i<26;i++){
            printf("Pp(%c):%lf\n",car+i,p[i]);
            fprintf(probsOut,"Pp(%c):%lf\n",car+i,p[i]);
        }
        
        for(i=0;i<26;i++){
            for(m=0;m<26;m++){
            printf("Pp(%c|%c):%lf\n",car+i,car+m,pp[i][m]);
            fprintf(probsOut, "Pp(%c|%c):%lf\n",car+i,car+m,pp[i][m]);
        }
        }
	fclose(in);
	fclose(out);
	fclose(fClaves);
	fclose(probsOut);
        free(p);
        free(pp);
	return 0;
}