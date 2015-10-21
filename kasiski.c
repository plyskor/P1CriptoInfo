#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#define MAX 9999999
#define MAXDIST 9000
#define MAXCADS 100


int main(int argc, char const *argv[]){

	FILE *f;
	f = fopen(argv[2], "r");
	char **cadenas;
	cadenas = (char**) malloc(MAX* sizeof(char *));

	char aux[3];
	int i=0,j,k=0;
	/*for (i = 0; i < MAX; ++i)
	{
		
	}*/
	i=0;
	int *dist,mcd;
	dist= (int*)malloc(MAXCADS* sizeof(int));

	while((fread( aux, sizeof(char), 3, f )== 3)&& k< MAXCADS){
		
		cadenas[i] = (char *) malloc(4* sizeof(char));
	
		strcpy(cadenas[i], aux);
		
		if(i>0){
			for(j=i-1; j>=0;j--){
				if(strcmp(cadenas[j],cadenas[i])==0){
					dist[k] = i-j;
					//printf("cadena %d,%d =%s , dist = %d\n",i,j,cadenas[j],dist[k]);
					k++;
					break;
				}
			}
		}
		fseek( f, ++i, SEEK_SET );
	}

	for(j=0;j<i;j++){
		free(cadenas[j]);
	}
	free(cadenas);
	fclose(f);
	//ahora hay que hallar el mcd de las distancias
	mcd = mcd_numeros(dist,k);
	printf("Hipótesis: El tamaño de la clave es = %d\n",mcd);
	free(dist);
	return 0;

}