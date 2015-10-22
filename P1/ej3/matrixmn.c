/* 
 * File:   matrixmn.c
 * Author: Jose
 *
 * Created on 21 de octubre de 2015, 18:55
 */

#include <stdio.h>
#include <stdlib.h>
#include "matrixmn.h"

/*
 * 
 */
matrixmn *initMatrixMN(int rows, int cols){
    if(rows<=0||cols<=0)return NULL;
    matrixmn *ret;
    int i=0;
    ret=(matrixmn*)malloc(sizeof(matrixmn));
    if(!ret)return NULL;
    ret->rows=rows;
    ret->columns=cols;
    ret->data=(int **)malloc(rows*sizeof(int *));
    if(!ret->data)return NULL;
    for(i=0;i<rows;i++){
        ret->data[i]=(int *)malloc(cols*sizeof(int));
    }
    return ret;
}
int getRowsMN(matrixmn *m){
    if(!m)return-1;
    return m->rows;
}
int getColumnsMN(matrixmn *m){
    if(!m)return-1;
    return m->columns;
}
void setValueMN(matrixmn *m,int row, int col, int value){
    if(!m||row<0||col<0||row>=m->rows||col>=m->columns)return;
    m->data[row][col]=value;
}
int getValueMN(matrixmn *m,int row, int col){
    if(!m||row<0||col<0||row>=m->rows||col>=m->columns)return-999 ;
    return(m->data[row][col]);
}
void zerosMN(matrixmn * m){
    if(!m) return;
    int i=0,j=0;
    for(i=0;i<m->rows;i++){
        for(j=0;j<m->columns;j++){
            setValueMN(m,i,j,0);
        }
    }
    return;
}
void exchangeRowsMN(matrixmn *m, int f1, int f2){
    if(!m||f1>getRowsMN(m)||f2>getRowsMN(m)||f1<0||f2<0)return;
    int i=0,filaAux[getColumnsMN(m)];
    for(i=0;i<getColumnsMN(m);i++){
        filaAux[i]=getValueMN(m,f1,i);
        setValueMN(m,f1,i,getValueMN(m,f2,i));
        setValueMN(m,f2,i,filaAux[i]);
    }
    return;
}
void exchangeColumnsMN(matrixmn *m, int f1, int f2){
    if(!m||f1>getColumnsMN(m)||f2>getColumnsMN(m)||f1<0||f2<0)return;
    int i=0,filaAux[getRowsMN(m)];
    for(i=0;i<getRowsMN(m);i++){
        filaAux[i]=getValueMN(m,i,f1);
        setValueMN(m,i,f1,getValueMN(m,i,f2));
        setValueMN(m,i,f2,filaAux[i]);
    }
    return;
}
void setRowMN(matrixmn *m,int f,int *row){
    if(!m||f>getRowsMN(m)||f<0)return;
    int i=0;
    for(i=0;i<getColumnsMN(m);i++){
        setValueMN(m,f,i,row[i]);
    }
    return;
}
void setColumnMN(matrixmn *m,int c,int *col){
    if(!m||c>getColumnsMN(m)||c<0)return;
    int i=0;
    for(i=0;i<getRowsMN(m);i++){
        setValueMN(m,i,c,col[i]);
    }
    return;
}
void cifra(matrixmn* P, matrixmn *C,int *k1,int *k2){
    if(!P||!C||!k1||!k2)return;
    matrixmn *aux;
    aux=initMatrixMN(getRowsMN(P),getColumnsMN(P));
    int i=0,j=0;
    for(i=0;i<getRowsMN(C);i++){
        for(j=0;j<getColumnsMN(P);j++){
            setValueMN(aux,i,j,getValueMN(P,k1[i]-1,j));
        }
    }
    for(i=0;i<getColumnsMN(C);i++){
        for(j=0;j<getRowsMN(P);j++){
            setValueMN(C,j,i,getValueMN(aux,j,k2[i]-1));
        }
    }
    
    return;
}
void descifra(matrixmn* C, matrixmn *P,int *k1,int *k2){
    if(!P||!C||!k1||!k2)return;
    matrixmn *aux;
    aux=initMatrixMN(getRowsMN(P),getColumnsMN(P));
    int i=0,j=0;
    
    for(i=0;i<getColumnsMN(C);i++){
        for(j=0;j<getRowsMN(P);j++){
            setValueMN(aux,j,k2[i]-1,getValueMN(C,j,i));
        }
    }
    for(i=0;i<getRowsMN(C);i++){
        for(j=0;j<getColumnsMN(P);j++){
            setValueMN(P,k1[i]-1,j,getValueMN(aux,i,j));
        }
    }
    
    return;
}
void toFileMN(FILE *f,matrixmn *m){
    if(!f||!m) return;
    int i,j;
    for(i=0;i<getRowsMN(m);i++){
        for(j=0;j<getColumnsMN(m);j++){
            fprintf(f,"%c",getValueMN(m,i,j));
        }
    }
    return;
}
void copyMatrix(matrixmn* src, matrixmn *dest){
    if(!src||!dest)return;
    int i=0,j=0;
    for(i=0;i<getRowsMN(src);i++){
        for(j=0;j<getColumnsMN(src);j++){
            setValueMN(dest,i,j,getValueMN(src,i,j));
        }
    }
    return;
}
void printMatrixMN(matrixmn *m){
    if(!m)return;
    int i=0,j=0;
    for(i=0;i<getRowsMN(m);i++){
        for(j=0;j<getColumnsMN(m);j++){
            printf("%d\t",getValueMN(m,i,j));
        }
        printf("\n");
    }
    return;
}


