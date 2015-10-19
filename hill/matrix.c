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
    ret->data=(double**)malloc(size*sizeof(double*));
    for(i=0;i<size;i++){
        ret->data[i]=(double *)malloc(size*sizeof(double));
        if(!ret->data[i])return NULL;
    }
    for (i=0;i<size;i++){
        for(j=0;j<size;j++){
            ret->data[i][j]=0;
        }
    }
    return ret;
}
void setValue(matrix *m,const int fila,const int col, const double value){
    if(!m||(fila<0)||(col<0)||(fila>m->size)||(col>m->size))return;
    m->data[fila][col]=value;
    return;
}
double getValue(matrix *m,const int fila,const int col){
   if(!m||(fila<0)||(col<0)||(fila>m->size)||(col>m->size))return -9999;
   return m->data[fila][col];
}
void readMatrix(FILE *in, matrix *m){
    if(!m||!in)return;
    int i=0,j=0;
    double aux=0;
    for(i=0;i<m->size;i++){
        for(j=0;j<m->size;j++){
            fscanf(in,"%lf",&aux);
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
            printf("%.2f\t",getValue(m,i,j));
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

double detMatrix(matrix *m) {
    if (!m) return -999;
    int  i = 0, j = 0, k = 0, z = 1, p = 0, f = 0;
    double aux2=0,res=1,pivote=0,aux=0;
    
    /*Creamos matriz auxiliar ya q hay que hacerla triangular superior y no queremos tocar la otra*/
    matrix *auxM;
    auxM = initMatrix(m->size);
    copyMatrix(m, auxM);
    if (!auxM)return -999;

    /*Empieza*/
    for (i = 0; i < m->size; i++) {
        p = 0;
        if (getValue(auxM, i, i) == 0) {
            p = -1;
            f = i;
            while ((f <= m->size)&&(p = -1)) {
                if (getValue(auxM, i, p) != 0) {
                    p = f;
                    exchangeRows(auxM, i, p);
                    z = z*-1;
                }
                f += 1;
            }
        }

        pivote = getValue(auxM, i, i);
        
        if (p != -1)
            for (j =i +1 ; j < m->size; j++) {
                aux = getValue(auxM, j, i);
                
                for (k = 0; k < m->size; k++) {
                    aux2 = (getValue(auxM, j, k)-(getValue(auxM, i, k)*(aux / pivote)));
                    
                    setValue(auxM, j, k, aux2);
                    
                }
            }
    }
    for (i = 0; i < m->size; i++) {
        res = res * getValue(auxM, i, i);
    }
    res *= z;
    eraseMatrix(auxM);
    return res;
}
void eraseMatrix(matrix *m){
    if(!m) return;
    free(m);
    return;
}