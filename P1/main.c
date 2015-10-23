/* 
 * File:   main.c
 * Author: jose
 *
 * Created on 20 de octubre de 2015, 20:22
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "matrixmn.h"
/*
 * 
 */
void leeClave(char *str,int* clave,int tam){
    int i=1,j=0;
    if(str[0]!='('){
        printf("La clave debe escribirse en formato (a,b,...,n)\n");
        return;
    }
    for(i=1,j=0;j<tam;j++,i+=2){
        clave[j]=atoi(&str[i]);
        if(clave[j]<=0||clave[j]>tam){
            printf("Al menos una de las claves contiene valores ilegales\n");
            clave[0]=-1;
            return;
        }
    }
    return;
}
int main(int argc, char** argv) {
    if(argc!=10){
        printf("El progama debe ser invocado asi: permutacion [-C|-D] [-k1 K1 -k2 K2] [-i inputFile] [-o outputFile]\n");
        return -1;
    }
    /*DECLARACIONES*/
    int *clave1,*clave2,*bloque,tam1=0,tam2=0,i=0,j=0,acabe=0;
    FILE *fin, *fout;
    matrixmn *m,*c;
    char *str;
    str=(char *)malloc(100*sizeof(char));
    if(!str)return -1;
    /*Leemos tamaño de las claves y las claves*/
    /*K1*/
    memset(str,0,100);
    strcpy(str,argv[3]);
    for (i=0; str[i]; str[i]==',' ? i++ : *str++);
    tam1=i+1;
    clave1=(int *)malloc(tam1*sizeof(int));
    if(!clave1) return -1;
    leeClave(argv[3],clave1,tam1);
    if(clave1[0]==-1)return -1;
    /*K2*/
    str=(char *)malloc(100*sizeof(char));
    if(!str)return -1;
    memset(str,0,100);
    strcpy(str,argv[5]);
    for (i=0; str[i]; str[i]==',' ? i++ : *str++);
    tam2=i+1;
    clave2=(int *)malloc(tam2*sizeof(int));
    if(!clave2) return -1;
    leeClave(argv[5],clave2,tam2);
    if(clave2[0]==-1)return -1;
    
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
    if (strcmp(argv[1], "-C") == 0) {
        /*CIFRADO*/
        m=initMatrixMN(tam1,tam2);
        c=initMatrixMN(tam1,tam2);
        bloque = (int*) malloc(tam2 * sizeof (int));
        if (!bloque) {
            fclose(fin);
           fclose(fout);
            return (-1);
        }
        for (i = 0; i < tam2; i++) {
            bloque[i] = fgetc(fin);

            if (bloque[i] == -1) {
                
                while (i < tam2) {
                    if(i==0&&j==0)acabe=1;
                    /*rellenamos con espacios el ultimo bloque si se llega al fin de fichero*/
                    bloque[i] = 32;
                    i++;
                }
                break;
            }
            if (i == tam2 - 1) {
                setRowMN(m,j,bloque);
                i = -1;
                if(j==tam1-1){
                    //Matriz completa, a cifrar
                    cifra(m,c,clave1,clave2);
                    toFileMN(fout,c);
                    j=-1;
                }
                j++;
            }
        }
        if(!acabe){
            //Si queda una matriz, la rellenamos con espacios
            setRowMN(m,j,bloque);
            j++;
            while(j<tam1){
                for(i=0;i<tam2;i++){
                    setValueMN(m,j,i,32);
                }
                j++;
            }
            cifra(m,c,clave1,clave2);
            toFileMN(fout,c);            
        }


    }
    if (strcmp(argv[1], "-D") == 0) {
        /*CIFRADO*/
        m=initMatrixMN(tam1,tam2);
        c=initMatrixMN(tam1,tam2);
        bloque = (int*) malloc(tam2 * sizeof (int));
        if (!bloque) {
            fclose(fin);
           fclose(fout);
            return (-1);
        }
        for (i = 0; i < tam2; i++) {
            bloque[i] = fgetc(fin);

            if (bloque[i] == -1) {
                if(i==0&&j==0)acabe=1;
                while (i < tam1) {
                    /*rellenamos con espacios el ultimo bloque si se llega al fin de fichero*/
                    bloque[i] = 32;
                    i++;
                }
                break;
            }
            if (i == tam2 - 1) {
                setRowMN(m,j,bloque);
                i = -1;
                if(j==tam1-1){
                    //Matriz completa, a descifrar
                    descifra(m,c,clave1,clave2);
                    toFileMN(fout,c);
                    j=-1;
                }
                j++;
            }
        }
        if(!acabe){
            //Si queda una matriz, la rellenamos con espacios
            setRowMN(m,j,bloque);
            j++;
            while(j<tam1){
                for(i=0;i<tam2;i++){
                    setValueMN(m,j,i,32);
                }
                j++;
            }
            descifra(m,c,clave1,clave2);
            toFileMN(fout,c);          
        }


    }
    free(m);
    free(c);
    fclose(fin);
    fclose(fout);
    free(clave1);
    free(clave2);
    
    return (EXIT_SUCCESS);
}

