#include <stdio.h>
#include <stdlib.h>
 #include <string.h>


#ifndef GCLAVES_H
#define	GCLAVES_H


#ifdef	__c
extern "C" {
#endif
	
int generaClaveAEquiprobable( int m);
int generaClaveBEquiprobable( int m);
int generaClavesNoEquiprobable(int m);

#ifdef	__c
}
#endif

#endif	/* GCLAVES_H */