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
    unsigned char *key, **ki, **kiInv, *bloqueplano, *bloqueaux, *bloquesalida, *l0, *r0, *l1, *r1, *bloquecifrado, *fres;
    int i, aux=0,ronda,fin=0;
    FILE *input, *output;
    /*MEMORIA*/
    key = (unsigned char*) malloc(sizeof (unsigned char)*8);
    if (!key) return -1;
    bloqueplano = (unsigned char*) malloc(sizeof (unsigned char)*9);
    if (!bloqueplano) return -1;
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
        if (!(input = fopen(argv[5], "r"))) {
            printf("Fallo al abrir %s\n", argv[5]);
            return -1;
        }
        if (!(output = fopen(argv[7], "w"))) {
            printf("Fallo al abrir %s\n", argv[7]);
            return -1;
        }
        /*Generamos clave aleatoria y las Ki*/
        generaClaveRandom64(key);
        generacionKi(key, ki);

        /*A leer bloques de 64 bits (8 char)*/
        while (fgets(bloqueplano, 9, input) != NULL) {
            formatBloque(bloqueplano, bloqueaux);
            memset(bloqueplano,0,9);
            memset(bloquesalida, 0, 8);
            IPfun(bloqueaux, bloquesalida);
            dividir(bloquesalida, l0, r0);
            memset(bloquesalida, 0, 8);
            /*RONDAS DES*/
            for (ronda = 0; ronda < 16; ronda++) {
                copiar(r0, l1, 4);
                Ffun(r0, ki[ronda], fres);
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
            for (i = 0; i < 8; i++) {
                fprintf(output, "%c", bloquecifrado[i]);
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
        if (!(input = fopen(argv[7], "r"))) {
            printf("Fallo al abrir %s\n", argv[6]);
            return -1;
        }
        if (!(output = fopen(argv[9], "w"))) {
            printf("Fallo al abrir %s\n", argv[8]);
            return -1;
        }
        /*Leemos la clave hexadecimal que nos pasan por argumento*/
        leeClave(argv[3], key);
        generacionKi(key, ki);
        /*cosillas de memoria*/
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
            for(i=0;i<8;i++){
                aux=fgetc(input);
                if(aux==-1){
                    bloqueaux[i]=0;
                    fin=1;
                }else{
                bloqueaux[i]=aux;
                }
            }
            printf("bloque leido : %s\n",bloqueaux);
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
            for (i = 0; i < 8; i++) {
                fprintf(output, "%c", bloquecifrado[i]);
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
    free(bloqueplano);
    free(bloqueaux);
    if (kiInv)free(kiInv);
    free(bloquesalida);
    free(bloquecifrado);

    return (EXIT_SUCCESS);
}

