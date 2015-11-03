#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef FUNCIONESDES_H
#define	FUNCIONESDES_H


#ifdef	__c
extern "C" {
#endif
	
void PC1fun(unsigned char *input, unsigned char *permutation);
void quitarParidad(unsigned char *input, unsigned char *output);
void PC2fun(unsigned char *input, unsigned char *permutation);
void rotarVector(unsigned char *input, unsigned char *permutation, int round);
void cajaSfun(unsigned char *input, unsigned char *output);

#ifdef	__c
}
#endif

#endif	/* FUNCIONESDES_H */