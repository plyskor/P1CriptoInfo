#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcionesDES.h"
void printbincharpad(unsigned char c)
{
    int i;
    for (i = 7; i >= 0; --i)
    {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar(' ');
    return;
}
void printbinarray(unsigned char*c,int tam){
    int i;
    for(i=0;i<tam;i++){
        printbincharpad(c[i]);
    }
    printf("\n");
    return;
}
/*
 * 
 */
void swapB(unsigned char*in, unsigned char*out){
    if(!in||!out)return;
    int i;
    for(i=0;i<4;i++){
        out[i+4]=in[i];
    }
    for(i=4;i<8;i++){
        out[i]=in[i+4];
    }
    return;
}
void printClave(unsigned char *k) {
    int i;
    if (!k)return;
    printf("Su clave generada aleatoriamente en hexadecimal es:");
    for (i = 0; i < 8; i++) {
        printf("%x", k[i]);
    }
    printf("\n");
    return;
}

void inverseKi(unsigned char**ki, unsigned char **res) {
    if (!ki || !res)return;
    int i;
    for (i = 0; i < 16; i++) {
        copiar(ki[15 - i], res[i], 6);
    }
    return;
}

void generaClaveRandom64(unsigned char *k) {
    int i = 0;
    if (!k)return;
    srand(time(NULL));
    for (i = 0; i < 8; i++) {
        k[i] = rand();
    }
    printClave(k);
    return;
}

void leeClave(const char * input, unsigned char *k) {
    if (!input || !k)return;
    sscanf(input, "%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx", &k[0], &k[1], &k[2], &k[3], &k[4], &k[5], &k[6], &k[7]);
    return;
}

void formatBloque(unsigned char *in, unsigned char *out) {
    if (!in || !out)return;
    int i;
    for (i = 0; i < 8; i++) {
        out[i] = in[i];
    }
    return;
}

int main(int argc, char** argv) {
    /*ARGUMENTOS*/
    if (argc < 2) {
        printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
        return -1;
    }
    /*DECLARACIONES*/
    unsigned char *key, **ki, **kiInv,  *bloqueaux, *bloquesalida, *l0, *r0, *l1, *r1, *bloquecifrado, *fres,leido=0;
    int i, aux=0,ronda,fin=0;
    FILE *input, *output;
    /*MEMORIA*/
    key = (unsigned char*) malloc(sizeof (unsigned char)*8);
    if (!key) return -1;
    bloqueaux = (unsigned char*) malloc(sizeof (unsigned char)*8);
    if (!bloqueaux) return -1;
    bloquesalida = (unsigned char*) malloc(sizeof (unsigned char)*8);
    if (!bloquesalida) return -1;
    bloquecifrado = (unsigned char*) malloc(sizeof (unsigned char)*8);
    if (!bloquecifrado) return -1;
    ki = (unsigned char**) malloc(16 * sizeof (unsigned char*));
    if (!ki)return -1;
    for (i = 0; i < 16; i++) {
        ki[i] = (unsigned char*) malloc(6 * sizeof (unsigned char));
        if (!ki[i])return -1;
        memset(ki[i], 0, 6);
    }
    l0 = (unsigned char*) malloc(sizeof (unsigned char)*4);
    if (!l0) return -1;
    r0 = (unsigned char*) malloc(sizeof (unsigned char)*4);
    if (!r0) return -1;
    l1 = (unsigned char*) malloc(sizeof (unsigned char)*4);
    if (!l0) return -1;
    r1 = (unsigned char*) malloc(sizeof (unsigned char)*4);
    if (!r0) return -1;
    fres = (unsigned char*) malloc(sizeof (unsigned char)*4);
    if (!fres) return -1;
    memset(l0, 0, 4);
    memset(r0, 0, 4);
    memset(l1, 0, 4);
    memset(r1, 0, 4);
    memset(fres, 0, 4);
    /*CASO CIFRADO*/
    if (!strcmp(argv[1], "-C")) {
        if (argc != 8) {
            printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
            return -1;
        }
        /*FICHEROS*/
        if (!(input = fopen(argv[5], "rb"))) {
            printf("Fallo al abrir %s\n", argv[5]);
            return -1;
        }
        if (!(output = fopen(argv[7], "wb"))) {
            printf("Fallo al abrir %s\n", argv[7]);
            return -1;
        }
        /*Generamos clave aleatoria y las Ki*/
        generaClaveRandom64(key);
        generacionKi(key, ki);
        
        /*A leer bloques de 64 bits (8 char)*/
        while (!fin) {
            memset(bloqueaux, 0 ,8);
            memset(r1, 0, 4);
            memset(l1, 0, 4);
            memset(l0, 0, 4);
            memset(r0, 0, 4);
            memset(bloquecifrado, 0 , 8);
            for(i=0;i<8;i++){
                leido=fgetc(input);
                if(feof(input)){
                    fin=1;
                    if(i==0)return 0;  
                    while(i<8){
                        bloqueaux[i]=' ';
                        i++;
                    }
                }else{
                    bloqueaux[i]=leido;
                }
            }
            
            memset(bloquesalida, 0, 8);
            //printf("BLOQUE LEIDO:\nBin:");
            //printbinarray(bloqueaux,8);
            //printf("String:%s\n",bloqueaux);
            IPfun(bloqueaux, bloquesalida);
            //printf("AFTER IP:");
            //printbinarray(bloquesalida,8);
            dividir(bloquesalida, l0, r0);
            //printf("DIVISION:\nLeft:");
            //printbinarray(l0,4);
            //printf("Right:");
            //printbinarray(r0,4);
            memset(bloquesalida, 0, 8);
            /*RONDAS DES*/
            for (ronda = 0; ronda < 16; ronda++) {
              //  printf("RONDA %d:\nL0:",ronda+1);
                //printbinarray(l0,4);
                //printf("R0:");
                //printbinarray(r0,4);
                copiar(r0, l1, 4);
                //printf("L1:");
                //printbinarray(l1,4);
                Ffun(r0, ki[ronda], fres);
                XORtam(l0, fres, 4, r1);
                //printf("xorESULT:");
            //printbinarray(r1,4);
                copiar(r1, r0, 4);
                copiar(l1, l0, 4);
                memset(r1, 0, 4);
                memset(l1, 0, 4);
            }
            /*final switch*/
            copiar(l0, r1, 4);
            copiar(r0, l1, 4);
            combinar(l1, r1, bloquesalida);
            /*final permutation*/
             //printf("ANTES IPINV:");
            //printbinarray(bloquesalida,8);
            IPinvfun(bloquesalida, bloquecifrado);
            /*escribir a salida el bloque cifrado*/
            //printf("AL ARCHIVO:");
            //printbinarray(bloquecifrado,8);
            for (i = 0; i < 8; i++) {
                fputc(bloquecifrado[i],output);
            }
        }

    }
    /*CASO DESCIFRADO*/
    if (!strcmp(argv[1], "-D")) {
        /*Generamos la clave aleatoria*/
        if (argc != 10) {
            printf("El programa se debe ejecutar asi: desECB [-C|-D -k clave] [-S s] [-i inputFile] [-o outputFile]\n");
            return -1;
        }
        /*FICHEROS*/
        if (!(input = fopen(argv[7], "rb"))) {
            printf("Fallo al abrir %s\n", argv[6]);
            return -1;
        }
        if (!(output = fopen(argv[9], "wb"))) {
            printf("Fallo al abrir %s\n", argv[8]);
            return -1;
        }
        /*Leemos la clave hexadecimal que nos pasan por argumento*/
        leeClave(argv[3], key);
        printf("Key:\n");
            printbinarray(key,8);
        generacionKi(key, ki);
        /*cosillas de memoria*/
        /*for(i=0;i<16;i++){
            printf("K%d:",i+1);
            printbinarray(ki[i],6);
        }*/
        kiInv = (unsigned char**) malloc(16 * sizeof (unsigned char*));
        if (!kiInv)return -1;
        for (i = 0; i < 16; i++) {
            kiInv[i] = (unsigned char*) malloc(6 * sizeof (unsigned char));
            if (!kiInv[i])return -1;
            memset(kiInv[i], 0, 6);
        }
        inverseKi(ki, kiInv);
        /*empieza el des*/
        while (!fin) {
            memset(bloqueaux, 0 ,8);
            memset(r1, 0, 4);
            memset(l1, 0, 4);
            memset(l0, 0, 4);
            memset(r0, 0, 4);
            memset(bloquecifrado, 0 , 8);
           // memset(bloquesalida, 0, 8);
            for(i=0;i<8;i++){
                leido=fgetc(input);
                if(feof(input)){
                    fin=1;
                    if(i==0)return 0;  
                    while(i<8){
                        bloqueaux[i]=0;
                        i++;
                    }
                }else{
                    
                    bloqueaux[i]=leido;
                }
            }
            //printf("bloque leido : %s\n",bloqueaux);
            //printbinarray(bloqueaux,8);
            memset(bloquesalida, 0, 8);
            IPfun(bloqueaux, bloquesalida);
            dividir(bloquesalida, l0, r0);
            memset(bloquesalida, 0, 8);
            /*RONDAS DES*/
            for (ronda = 0; ronda < 16; ronda++) {
                copiar(r0, l1, 4);
                Ffun(r0, kiInv[ronda], fres);
               
                XORtam(l0, fres, 4, r1);
                 
                copiar(r1, r0, 4);
                copiar(l1, l0, 4);
                memset(r1, 0, 4);
                memset(l1, 0, 4);
            }
            /*final switch*/
            copiar(l0, r1, 4);
            copiar(r0, l1, 4);
            combinar(l1, r1, bloquesalida);
            /*final permutation*/
            
            IPinvfun(bloquesalida, bloquecifrado);
            /*escribir a salida el bloque cifrado*/
            //printf("AL ARCHIVO:");
            //printbinarray(bloquecifrado,8);
            for (i = 0; i < 8; i++) {
                fputc(bloquecifrado[i],output);
            }
        }
    }

    /*LIBERAR MEMORIA Y CERRAR FICHEROS*/
    free(key);
    fclose(input);
    fclose(output);
    free(l0);
    free(l1);
    free(r0);
    free(r1);
    free(fres);
    free(bloqueaux);
    if (kiInv)free(kiInv);
    free(bloquesalida);
    free(bloquecifrado);

    return (EXIT_SUCCESS);
}

