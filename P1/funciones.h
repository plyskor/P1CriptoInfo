/* 
 * File:   funciones.h
 * Author: jose y cris
 *
 * Created on 18 de octubre de 2015, 23:17
 */
#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef FUNCIONES_H
#define	FUNCIONES_H


#ifdef	__cplusplus
extern "C" {
#endif

int cmpfunc (const void * a, const void * b);
int mcd(int a,int b);
int mcd_numeros_recusiva(int *numeros,int cont);
int mcd_numeros(int *numeros, int longitud);
double calculaFrecuencia(char letra, char *cadena, int sizeCadena);
double calculaIndiceC(double *frecs, int size, int sizeFrecs);
double indiceCdeColumna(FILE *f,int columna , int ngrama);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCIONESGMP_H */