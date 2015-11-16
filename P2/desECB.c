/* 
 * File:   main.c
 * Author: Jose
 *
 * Created on 16 de noviembre de 2015, 17:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcionesDES.h"

/*
 * 
 */
void generaClaveRandom64(unsigned char *k){
    int i =0;
    if(!k)return;
    srand(time(NULL));
    for(i=0;i<8;i++){
        k[i]=rand();
    }
    printf("Su clave generada aleatoriamente en hexadecimal es:");
    for(i=0;i<8;i++){
        printf("%x",k[i]);
    }
    printf("\n");
    return;
}
int main(int argc, char** argv) {
    /*ARGUMENTOS*/
    if(argc!=7&&argc!=9){
        printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
        return -1;
    }
    /*DECLARACIONES*/
    unsigned char *key;
    int i;
    /*MEMORIA*/
    key= (unsigned char*)malloc(sizeof(unsigned char)*8);
    if(!key) return -1;
    /*Generamos la clave aleatoria*/
    generaClaveRandom64(key);
    /*LIBERAR MEMORIA*/
    free(key);
    return (EXIT_SUCCESS);
}

