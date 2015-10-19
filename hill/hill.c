#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "matrix.h"

int mcd(int a, int b) {
    int i,r[50];
    if(a<0)a*=-1;
    if(b<0)b*=-1;
    for(i=0;i<50;i++){
        r[i]=0;
    }
    r[0]=a;
    r[1]=b;
    i=1;
    while(r[i]!=0){
        r[i+1]=r[i-1]%r[i];
        i++;
    }
    return r[i-1];
}
int main (int argc,char *argv[]) {
    int m=0,n=0,detint=0;
    double det=0;
    FILE *fmatrix, *fin, *fout;
    matrix *K;
    /*LECTURA DE ARGUMENTOS DE ENTRADA*/
    if(argc != 12){
        printf("El programa ha de ser invocado asi: hill [-C|-D] [-m |Zm|] [-n Nk] [-k filematriz] [-i infile] [-o outfile]\n");
        return(0);
    }
    m=atoi(argv[3]);
    n=atoi(argv[5]);
    if((n<0)||(m<0)){
        printf("Valores no validos para m o n");
        return(0);
    }
    /*Inicializamos la estructura de datos para la matriz*/
    K=initMatrix(n);
    /*Leemos la matriz del fichero */
    fmatrix=fopen(argv[7],"r");
    if(!fmatrix){
        printf("Error al abrir el archivo %s\n",argv[7]);
        return -1;
    }
    readMatrix(fmatrix,K);
    fclose(fmatrix);
    /*Comprobamos la matriz de claves*/
    if(detMatrix(K)==0){
        printf("LA matriz de claves debe ser no singular\n");
        eraseMatrix(K);
        return(-1);
    }
    detint=(int)detMatrix(K);
    printf("%d\n",detint);
    if(mcd(detint,m)!=1){
        printf("La matriz de claves proporcionada no define una función inyectiva.\n");
        eraseMatrix(K);
        return(-1);
    }
    
    return(0);
}