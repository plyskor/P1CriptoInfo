#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200


double calculaFrecuencia(char letra, char *cadena, int sizeCadena){ 
	//la cadena es el mensaje entero, en sizeCadena guardo hasta donde quiero analizar
	int i;
	double frec=0;
	for ( i = 0; i <= sizeCadena; ++i){

		if(cadena[i]==letra) frec++;
	}
	
	return frec;
}

double calculaIndiceC(double *frecs, int size, int sizeFrecs){
	int i;
	double indiceC=0;
	
	for (i = 0; i <sizeFrecs; i++){
		
		indiceC+=((frecs[i]/(size+1))*((frecs[i]-1)/size));
	}
	return indiceC;
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


int main (int argc,char *argv[]) {
	FILE *f;
	f = fopen(argv[4] , "r");
	int i=0, cont=0, temp=0, sizeC=0, flag=0,n, aux;
	char *c,a;
	c = (char*) malloc(sizeof(char)*MAX);
	double *frecs , IC;
	n = atoi(argv[2]);
	//cojo la primera letra de cada n-grama
	while (1){
		if((aux=fgetc(f))== -1){
			break;
		}
		c[i] = aux;
		
		for(cont=0;cont<n-1;cont++){
			if((temp=fgetc(f))== 10){
				//caso \n
				cont --;
				continue;
			}	
		}
		i++;
	}
	c[i] = '\0';

	sizeC = strlen(c);
	frecs = (double *) malloc(sizeC * (sizeof(double))+1);
	for (cont = 0; cont < sizeC; cont++){
		for(temp=0; temp<cont;temp++){
			if(c[cont] == '\0'){
				flag = -1;
				break;
			}
			if(c[temp] == c[cont]){
				flag = 1;
				break;
			}
			
		}
		if(flag ==-1){
			break;
		}else if(flag ==1){
			flag=0;
		}else{
			frecs[cont]= calculaFrecuencia(c[cont], c, sizeC);
		}
		
	}

	IC = calculaIndiceC(frecs, sizeC, cont-1);
	printf("IC = %f\n",IC);
	free(frecs);
	free(c);
	fclose(f);
	return;
}