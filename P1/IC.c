#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"




int main (int argc,char *argv[]) {
	FILE *f;
	int n,i;
	if((f = fopen(argv[4] ,"r"))==NULL) return -1;
	n = atoi(argv[2]);
	double *IC,ICfinal=0;
	IC = (double*)malloc(sizeof(double)*n);
	for (i = 0; i < n; i++)
	{
		IC[i]=indiceCdeColumna(f,i,n);
	}
	for (i = 0; i < n; i++)
	{
		 ICfinal+=IC[i];
	}
	ICfinal=ICfinal/n;
	printf(" ICfinal %f\n",ICfinal );
	fclose(f);
	return;
}



/*
int main (int argc,char *argv[]) {
	char *mensaje;
	double *indicesC ,*frecs;
	int flag=0, nfrecs=0 , i, j,k;
	int sizeMensaje= strlen(argv[2]);
	mensaje = (char*) malloc (sizeMensaje* (sizeof(char))+1);
	indicesC = (double *) malloc (sizeMensaje*(sizeof(double))+1);
	frecs = (double *) malloc (sizeMensaje*(sizeof(double))+1);
	strcpy(mensaje,argv[2]);
	

	for (i = 1; i < sizeMensaje ; i++){
		for (j = 0; j <=i; j++){
			for (k = 0; k < j; k++){
				if(mensaje[j] == mensaje[k]){
				
					flag = 1;
					break;
				}
			}
			
			if(flag==0){
				frecs[nfrecs]=calculaFrecuencia(mensaje[j], mensaje , i);
				nfrecs++;
			}else{
				
				flag = 0;
			}
		}
		indicesC[i] = calculaIndiceC(frecs,i,nfrecs);
		nfrecs = 0;
	}
	free(frecs);
	free(indicesC);
	free(mensaje);
	return 0;
}*/
