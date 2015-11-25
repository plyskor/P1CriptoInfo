#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef PROBABILIDAD_H
#define	PROBABILIDAD_H


#ifdef	__c
extern "C" {
#endif
void calculaProbs(FILE *f, double *prob);
void calculaProbsCondicionadas(FILE *plano, FILE *cifrado , double **prob);

#ifdef	__c
}
#endif

#endif	/* PROBABILIDAD_H */