#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef FUNCIONESDES_H
#define	FUNCIONESDES_H


#ifdef	__c
extern "C" {
#endif
void printbincharpad(unsigned char c);
void printbinarray(unsigned char*c,int tam);
void PC1fun(unsigned char *input, unsigned char *permutation);
void IPfun(unsigned char *input, unsigned char *permutation);
void quitarParidad(unsigned char *input, unsigned char *output);
void PC2fun(unsigned char *input, unsigned char *permutation);
void rotarVector(unsigned char *input, unsigned char *permutation, int round);
void cajaSfun(unsigned char *input, unsigned char *output);
void generacionKi(unsigned char *K , unsigned char **ki);
void dividir(unsigned char *in,unsigned char *left,unsigned char* right);
void copiar(unsigned char *src,unsigned char *dst,int tam);
void Efun(unsigned char *input, unsigned char *permutation);
void Ffun(unsigned char *r,unsigned char *ki,unsigned char *res);
void XORtam(unsigned char *a,unsigned char*b,int tam,unsigned char *out);
void Pfun(unsigned char *input, unsigned char *permutation);
void IPinvfun(unsigned char *input, unsigned char *permutation);
void combinar(unsigned char *left,unsigned char *right,unsigned char *res);
#ifdef	__c
}
#endif

#endif	/* FUNCIONESDES_H */