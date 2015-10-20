#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 9999999999
#define MAXDIST 900


int main(int argc, char const *argv[]){

	FILE *f;
	f = fopen(argv[4], "r");
	char **cadenas;
	cadenas = (char**) malloc(MAX* sizeof(char *));
	char aux[3];
	int i=0,j,k=0;
	int *dist;
	dist= (int*)malloc(MAXDIST* sizeof(int));

	while(fread( aux, sizeof(char), 3, f )== 3){
		cadenas[i] = (char *)malloc(3 *(sizeof(char)));
		strcpy(cadenas[i], aux);
		for(j=i-1; j>=0;j--){
			if(strcmp(cadenas[j],cadenas[i])==0){
				dist[k] = i-j;
				k++;
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
	free(dist);
	return 0;

}