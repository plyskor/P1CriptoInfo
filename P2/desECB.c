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

void printClave(unsigned char *k){
    int i;
    if(!k)return;
    printf("Su clave generada aleatoriamente en hexadecimal es:");
    for(i=0;i<8;i++){
        printf("%x",k[i]);
    }
    printf("\n");
    return;
}
void generaClaveRandom64(unsigned char *k){
    int i =0;
    if(!k)return;
    srand(time(NULL));
    for(i=0;i<8;i++){
        k[i]=rand();
    }
    printClave(k);
    return;
}
void leeClave(const char * input,unsigned char *k){
    if(!input||!k)return;
    sscanf(input,"%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",&k[0],&k[1],&k[2],&k[3],&k[4],&k[5],&k[6],&k[7]); 
    return;
}
int main(int argc, char** argv) {
    /*ARGUMENTOS*/
    if(argc<2){
        printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
        return -1;
    }
    /*DECLARACIONES*/
    unsigned char *key;
    int i;
    /*MEMORIA*/
    key= (unsigned char*)malloc(sizeof(unsigned char)*8);
    if(!key) return -1;
    /*CASO CIFRADO*/
    if(!strcmp(argv[1],"-C")){ 
        if(argc!=7){
            printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
            return -1;
        }
        /*Generamos clave aleatoria*/
        generaClaveRandom64(key);
    }
    /*CASO DESCIFRADO*/
    if(!strcmp(argv[1],"-D")){
       /*Generamos la clave aleatoria*/ 
       if(argc!=9){
        printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
        return -1;
        }
       /*Leemos la clave hexadecimal que nos pasan por argumento*/
       leeClave(argv[3],key);
       
    }
    
    /*LIBERAR MEMORIA*/
    free(key);
    return (EXIT_SUCCESS);
}

