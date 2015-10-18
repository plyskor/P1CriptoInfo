/* 
 * File:   matrix.h
 * Author: jose
 *
 * Created on 18 de octubre de 2015, 23:17
 */

#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct{
        int **data;
        int size;
    }matrix;
matrix *initMatrix(int size);
void setValue(matrix *m,const int fila,const int col, const int value);
int getValue(matrix *m,const int fila,const int col);
#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

