#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
matrix *initMatrix(int size){
    if(size<=0)return NULL;
    matrix *ret;
    int i=0,j=0;
    ret=(matrix*)malloc(sizeof(matrix));
    if(!ret)return NULL;
    ret->size=size;
    ret->data=(int**)malloc(size*sizeof(int*));
    for(i=0;i<size;i++){
        ret->data[i]=(int *)malloc(size*sizeof(int));
        if(!ret->data[i])return NULL;
    }
    for (i=0;i<size;i++){
        for(j=0;j<size;j++){
            ret->data[i][j]=0;
        }
    }
    return ret;
}
void setValue(matrix *m,const int fila,const int col, const int value){
    if(!m||(fila<0)||(col<0)||(fila>m->size)||(col>m->size))return;
    m->data[fila][col]=value;
    return;
}
int getValue(matrix *m,const int fila,const int col){
   if(!m||(fila<0)||(col<0)||(fila>m->size)||(col>m->size))return -9999;
   return m->data[fila][col];
}
void readMatrix(FILE *in, matrix *m){
    if(!m||!in)return;
    int i=0,j=0,aux=0;
    for(i=0;i<m->size;i++){
        for(j=0;j<m->size;j++){
            fscanf(in,"%d",&aux);
            setValue(m,i,j,aux);
        }
    }
    return;
}
void printMatrix(matrix *m){
    if(!m)return;
    int i=0,j=0;
    for(i=0;i<m->size;i++){
        for(j=0;j<m->size;j++){
            printf("%d\t",getValue(m,i,j));
        }
        printf("\n");
    }
    return;
}