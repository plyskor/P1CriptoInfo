/* 
 * File:   matrixmn.h
 * Author: Jose
 *
 * Created on 21 de octubre de 2015, 18:53
 */

#ifndef MATRIXMN_H
#define	MATRIXMN_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct{
        int **data;
        int rows;
        int columns;
    }matrixmn;
    
    matrixmn *initMatrixMN(int rows, int cols);
int getRowsMN(matrixmn *m);
int getColumnsMN(matrixmn *m);
void setValueMN(matrixmn *m,int row, int col, int value);
int getValueMN(matrixmn *m,int row, int col);
void zerosMN(matrixmn * m);
void exchangeRowsMN(matrixmn *m, int f1, int f2);
void exchangeColumnsMN(matrixmn *m, int f1, int f2);
void setRowMN(matrixmn *m,int f,int *row);
void setColumnMN(matrixmn *m,int c,int *col);
void printMatrixMN(matrixmn *m);
void copyMatrix(matrixmn* src, matrixmn *dest);
void cifra(matrixmn* P, matrixmn *C,int *k1,int *k2);
void descifra(matrixmn* C, matrixmn *P,int *k1,int *k2);
void toFileMN(FILE *f,matrixmn *m);

#ifdef	__cplusplus
}
#endif

#endif	/* MATRIXMN_H */

