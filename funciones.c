#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
 #include <string.h>
 #define MAX 2000
#define MAXDIST 9000
#define MAXCADS 100


int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a > *(int*)b );
}

int mcd(int a,int b) // función recursiva.
{
    return(b==0) ? a : mcd(b,a%b);
  //si b==0 es verdad,devolvemos a = m.c.d.
  //si no,entramos en otra función recursiva (hasta que se resuelva).
}

int mcd_numeros_recusiva(int *numeros,int cont){
	if(cont == 2){
		return mcd(numeros[0],numeros[1]);
	}else if(cont>2){
		cont--;
		return mcd(numeros[cont+1], mcd_numeros_recusiva(numeros,cont));
	}
	

}
int mcd_numeros(int *numeros, int longitud){

	qsort(numeros, longitud, sizeof(int), cmpfunc);
	return mcd_numeros_recusiva(numeros,longitud);
}



	

void factores (int num , int *factores){
	int i= 2,j=0;
   
   	while( i <= num ){
   	   if( (num%i) == 0 ){    
   	      factores[j] = i;
   	      j++;
   	      num= num/i;
   	   }
   	   else
   	      i++;
   	}
}

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

double indiceCdeColumna(FILE *f,int columna , int ngrama){
  int i=0, cont=0, temp=0, sizeC=0, flag=0,n, aux;
  char *c,a;
  c = (char*) malloc(sizeof(char)*MAX);
  double *frecs , IC=0;
  
  //cojo la letra m de cada n-grama
  fseek(f, columna, SEEK_SET);
  while (1){
    if((aux=fgetc(f))== -1){
      break;
    }
    c[i] = aux;

    
    for(cont=0;cont<ngrama-1;cont++){
      if((temp=fgetc(f))== 10){
        //caso \n
        cont --;
        continue;
      } 
    }
    i++;
  }
  c[i] = '\0';
  //printf("leo :%s\n",c);

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
      //printf("frec de %c = %f\n",c[cont], frecs[cont]);
    }
    
  }

  IC = calculaIndiceC(frecs, sizeC, cont-1);
  //printf("IC = %f\n",IC);
  free(frecs);
  free(c);
  return IC;
}

