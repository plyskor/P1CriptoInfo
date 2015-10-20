/* 
 * File:   matrix.h
 * Author: jose
 *
 * Created on 18 de octubre de 2015, 23:17
 */
#include <stdio.h>
#include <stdlib.h>
#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct{
        double **data;
        int size;
    }matrix;
matrix *initMatrix(int size);
void transpuesta (matrix*src,matrix*res);
void inversa(matrix* src,matrix *res,int mod);
void setValue(matrix *m,const int fila,const int col, const double value);
double getValue(matrix *m,const int fila,const int col);
void readMatrix(FILE *in, matrix *m);
void printMatrix(matrix *m);
void copyMatrix(matrix* src, matrix *dest);
double detMatrix(matrix *m);
void eraseMatrix(matrix *m);
void exchangeRows(matrix *m, int f1, int f2);
void cofactores(matrix *src, matrix *des);
void matrixMod(matrix *m,int mod);
int inversoZm(int a, int m);
int mod(int a ,int b);
#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */
