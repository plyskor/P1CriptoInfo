/* 
 * File:   main.c
 * Author: Jose
 *
 * Created on 23 de noviembre de 2015, 17:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcionesDES.h"
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

/*
 * 
 */
void generaBloque(unsigned char *res,int n){
    if(!res||n<=0)return;
    int i;
    
    for(i=0;i<n;i++){
        res[i]=rand();
    }
    return;
}
int main(int argc, char** argv) {
    /*Delclaraciones*/
    unsigned short n=-1,i;
    unsigned char *a,*b,*amasb,*fa,*fb,*famasb,*faux;
    /*Argumentos de entrada*/
    if(argc!=3){
        printf("El programa se debe ejecutar como linealidadSBoxes -n N , siendo N el numero de iteraciones que se desean\n");
        return EXIT_FAILURE;
    }
    n=atoi(argv[2]);
    if(n<=0)return EXIT_FAILURE;
    /*Memoria*/
    a=(unsigned char *)malloc(6*sizeof(unsigned char));
    if(!a) return EXIT_FAILURE;
    b=(unsigned char *)malloc(6*sizeof(unsigned char));
    if(!b) {
        if(a)free(a);
        return EXIT_FAILURE;
    }
    amasb=(unsigned char *)malloc(6*sizeof(unsigned char));
    if(!amasb){
        if(a)free(a);
        if(b)free(b);
        return EXIT_FAILURE;
    }
    
     fa=(unsigned char *)malloc(4*sizeof(unsigned char));
    if(!fa) {
        
        if(amasb)free(amasb);
        if(a)free(a);
        if(b)free(b);
        return EXIT_FAILURE;
    }
    fb=(unsigned char *)malloc(4*sizeof(unsigned char));
    if(!fb) {
        if(fa)free(fa);
        
        if(amasb)free(amasb);
        if(a)free(a);
        if(b)free(b);
        return EXIT_FAILURE;
    }
    famasb=(unsigned char *)malloc(4*sizeof(unsigned char));
    if(!famasb){
        if(fb)free(fb);
        if(fa)free(fa);
        
        if(amasb)free(amasb);
        if(a)free(a);
        if(b)free(b);
        return EXIT_FAILURE;
    }
    faux=(unsigned char *)malloc(4*sizeof(unsigned char));
    if(!faux){
        if(famasb)free(famasb);
        if(fb)free(fb);
        if(fa)free(fa);
        
        if(amasb)free(amasb);
        if(a)free(a);
        if(b)free(b);
        return EXIT_FAILURE;
    }
    /*Iteramos*/
    srand(time(NULL));
    for(i=0;i<n;i++){
        memset(a,0,6);
        memset(b,0,6);
        memset(amasb,0,6);
        
        memset(fa,0,4);
        memset(fb,0,4);
        memset(famasb,0,4);
        memset(faux,0,4);
        printf("ITERACION %d:\n",i+1);
        generaBloque(a,6);  
        cajaSfun(a,fa);
        generaBloque(b,6);
        cajaSfun(b,fb);
        XORtam(a,b,6,amasb);
        cajaSfun(amasb,famasb);
        XORtam(fa,fb,4,faux);
        printf("f(a):");
        printbinarray(fa,4);
        printf("f(b):");
        printbinarray(fb,4);
        printf("f(a+b):");
        printbinarray(famasb,4);
        printf("f(a)+f(b):");
        printbinarray(faux,4);
    }
   /*Liberar memoria reservada al salir*/
        if(faux)free(faux);
        if(famasb)free(famasb);
        if(fb)free(fb);
        if(fa)free(fa);
        
        if(amasb)free(amasb);
        if(a)free(a);
        if(b)free(b);
}

