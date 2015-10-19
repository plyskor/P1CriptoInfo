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
void setValue(matrix *m,const int fila,const int col, const double value);
double getValue(matrix *m,const int fila,const int col);
void readMatrix(FILE *in, matrix *m);
void printMatrix(matrix *m);
void copyMatrix(matrix* src, matrix *dest);
double detMatrix(matrix *m);
void eraseMatrix(matrix *m);
void exchangeRows(matrix *m, int f1, int f2);
#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

