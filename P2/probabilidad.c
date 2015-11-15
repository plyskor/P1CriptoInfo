    #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "probabilidad.h"



void calculaProbs(FILE *f, double *prob){ //Mi texto estará en mayúsculas y sin espacios, con un alfabeto de 26 letras
	int longText=0, frec=0 ,i,l;
	for (i = 0; i < 26; ++i){
		prob[i]=0;
	}

	while((l=fgetc(f))!=EOF){
		prob[l-65]++;
		longText++;
	}

	for (i = 0; i < 26; ++i){
		prob[i]=prob[i]/longText;
	}

	return;
}

void calculaProbsCondicionadas(FILE *plano, FILE *cifrado , double **prob){
	int i,j,p,c, longText=0;
        
	for (i = 0; i < 26; ++i){
            
		for(j=0;j<26;j++){
			prob[i][j]=0;
		}
		
	}
	while((c=fgetc(cifrado))!=EOF){
		p = fgetc(plano);
		prob[p-65][c-65]++;
		longText++;
	}
	for (i = 0; i < 26; ++i){
		for(j=0;j<26;j++){
			prob[i][j]=prob[i][j]/longText;
		}
		
	}
	return;

}