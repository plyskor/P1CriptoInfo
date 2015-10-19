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
void copyMatrix(matrix* src, matrix *dest){
    if(!src||!dest)return;
    if(src->size!=dest->size)return;
    int i=0,j=0;
    for(i=0;i<src->size;i++){
        for(j=0;j<src->size;j++){
            setValue(dest,i,j,getValue(src,i,j));
        }
    }
    return;
}
void exchangeRows(matrix *m, int f1, int f2){
    if(!m||f1>m->size||f2>m->size||f1<0||f2<0)return;
    int i=0,filaAux[m->size];
    for(i=0;i<m->size;i++){
        filaAux[i]=getValue(m,f1,i);
        setValue(m,f1,i,getValue(m,f2,i));
        setValue(m,f2,i,filaAux[i]);
    }
    return;
    
}
int detMatrix(matrix *m){
    if(!m) return -999;
    int res=1,i=0,j=0,k=0,pivote=0,aux=0,aux2=0;
    /*Creamos matriz auxiliar ya q hay q diagonalizarla y no queremos tocar la otra*/
    matrix *auxM;
    auxM=initMatrix(m->size);
    copyMatrix(m,auxM);
    if(!auxM)return -999;
    for(i=0;i<m->size;i++){
        pivote=getValue(auxM,i,i);
        printf("pivote=%d\n",pivote);
        for(j=i+1;j<m->size;j++){
            aux=getValue(auxM,j,i);
            printf("aux=%d\n",aux);
            for(k=0;k<m->size;k++){
                if(pivote==0)return 0;
                aux2=(int)(getValue(auxM,j,k)-(getValue(auxM,i,k)*(aux/pivote)));
                printf("aux2=%d\n",aux2);
                setValue(auxM,j,k,aux2);
                printMatrix(auxM);
            }
        }
    }
    for(i=0;i<m->size;i++){
        res=res*getValue(auxM,i,i);
    }
    eraseMatrix(auxM);
    return res;
}
void eraseMatrix(matrix *m){
    if(!m) return;
    free(m);
    return;
}