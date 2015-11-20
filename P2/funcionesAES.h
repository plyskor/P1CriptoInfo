#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef FUNCIONESAES_H
#define	FUNCIONESAES_H


#ifdef	__c
extern "C" {
#endif

void cajaS_AESfun(char *input, char *output);

#ifdef	__c
}
#endif

#endif	/* FUNCIONESAES_H */