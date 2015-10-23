#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"

int generaClavesEquiprobable( int m){
	int i;
   	time_t t;
   	int clave;
      
      	clave = rand() % m;
   	

   	return clave;
}


int generaClavesNoEquiprobable(int m){

	int i;
   	time_t t;
   	int clave;
   
      	clave = rand() % m;
   	

   	// de esta forma es mucho más probable una clave impar que una par
   	for(i=0; i<2;i++){
   		if((clave%2)==0){
   			clave = rand() % m;
   		}else break;
   	}
   	
   	return clave;

}