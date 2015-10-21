/* 
 * File:   main.c
 * Author: jose
 *
 * Created on 20 de octubre de 2015, 20:22
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
void leeClave(char *str,int* clave){
    int i=1,j=0;
    if(str[0]!='('){
        printf("La clave debe escribirse en formato (a,b,...,n)\n");
        return;
    }
    for(i=1,j=0,str[i];str[i+1]==',';i+=2,j++){
        clave[i]=str[i];
    }
    return;
}
int main(int argc, char** argv) {
    if(argc!=10){
        printf("El progama debe ser invocado asi: permutacion [-C|-D] [-k1 K1 -k2 K2] [-i inputFile] [-o outputFile]\n");
        return -1;
    }
    /*DECLARACIONES*/
    int *clave1,*clave2,tam1=0,tam2=0,i=0;
    FILE *fin, *fout;
    /*Leemos tamaño de las claves*/
    for (i=0; argv[3][i]; argv[3][i]==',' ? i++ : *argv[3]++);
    tam1=i+1;
    for (i=0; argv[5][i]; argv[5][i]==',' ? i++ : *argv[5]++);
    tam2=i+1;
    /*Reservamos memoria para las claves*/
    clave1=(int *)malloc(tam1*sizeof(int));
    if(!clave1) return -1;
    clave2=(int *)malloc(tam2*sizeof(int));
    if(!clave2) return -1;
    /*Leemos las claves*/
    leeClave(argv[3],clave1);
    for(i=0;i<tam1;i++){
        printf("%d,",clave1[i]);
    }
    /*Abrimos los ficheros*/
    fin=fopen(argv[7],"r");
    if(!fin){
        free(clave1);
        free(clave2);
        printf("Error al abrir el fichero %s\n",argv[7]);
        return -1;
    }
    fout=fopen(argv[9],"w");
    if(!fout){
        fclose(fin);
        free(clave1);
        free(clave2);
        printf("Error al abrir el fichero %s\n",argv[9]);
        return -1;
    }
    fclose(fin);
    fclose(fout);
    free(clave1);
    free(clave2);
    
    return (EXIT_SUCCESS);
}

