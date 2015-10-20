#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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
}