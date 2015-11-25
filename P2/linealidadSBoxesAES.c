/* 
 * File:   main.c
 * Author: Jose
 *
 * Created on 25 de noviembre de 2015, 20:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AES_tables.c"
static unsigned char Positions[8] = {128,64,32,16,8,4,2,1};
unsigned char hexatoint(char c){
    if(c=='0')return 0;
    if(c=='1')return 1;
    if(c=='2')return 2;
    if(c=='3')return 3;
    if(c=='4')return 4;
    if(c=='5')return 5;
    if(c=='6')return 6;
    if(c=='7')return 7;
    if(c=='8')return 8;
    if(c=='9')return 9;
    if(c=='a')return 10;
    if(c=='b')return 11;
    if(c=='c')return 12;
    if(c=='d')return 13;
    if(c=='e')return 14;
    if(c=='f')return 15;
    return -1;
}
void SBOXAES(unsigned char *src, unsigned char *dst){
    if(!src||!dst)return;
    unsigned char fila=0,columna=0,aux[2];
    fila = src[0] & 0xF0;
    fila = fila >>4;
    columna= src[0] & 0x0F;
   // printf("fila:%d columnda : %d \n",fila,columna);
    memset(&aux,0,2);
    aux[0]=DIRECT_SBOX[fila][columna][0];
    aux[1]=DIRECT_SBOX[fila][columna][1];
    memset(dst,0,1);
    dst[0]=hexatoint(aux[0]);
    dst[0]=dst[0]<<4;
    columna=hexatoint(aux[1]);
    dst[0]=dst[0]^columna;
    //printf("salida: %x\n",dst[0]);
    return;
}
void randchar(unsigned char *dst){
    if(!dst)return;
    dst[0]=rand();
    return;
}
int main(int argc, char** argv) {
    unsigned char a,b,amasb,fa,fb,famasb,aux;
    int n=-1,i=0;
    if(argc!=3){
        printf("El programa se debe ejecutar como linealidadSBoxesAES -n N , siendo N el numero de iteraciones que se desean\n");
        return EXIT_FAILURE;
    }
    n=atoi(argv[2]);
    srand(time(NULL));
    for(i=0;i<n;i++){
        a=0;b=0;amasb=0;fa=0;fb=0;famasb=0;aux=0;
        randchar(&a);
        randchar(&b);
        printf("ITERACION %d:\n",i+1);
        amasb=a+b;
        SBOXAES(&a,&fa);
        SBOXAES(&b,&fb);
        SBOXAES(&amasb,&famasb);
        aux=fa+fb;
        printf("a=%x\nb=%x\nf(a)=%x\nf(b)=%x\nf(a+b)=%x\nf(a)+f(b)=%x\n",a,b,fa,fb,famasb,aux);
    }
   //rintf("hexa: %x\n",a); 
    SBOXAES(&a,&fa);
    return (EXIT_SUCCESS);
}

