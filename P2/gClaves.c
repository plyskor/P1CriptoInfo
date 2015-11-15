#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"

int mcd(int a, int b) {
    int c;
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    c = a;
    return c;
}

int generaClavesEquiprobable( int m){
   int i=0,end=0;
      int clave;
        while(end==0){
            clave = rand() % m;
            if(clave==0)continue;
            if(mcd(clave,m)==1)end=1;
        }
      return clave;
}
int generaClavesNoEquiprobable(int m){
   int i,end=0;
      int clave;
         clave = rand() % m;
      // de esta forma es mucho más probable una clave impar que una par
      while(end==0){
            for(i=0; i<2;i++){
                    if((clave%2)==0){
                            clave = rand() % m;
                            if(clave==0)continue;
                    }else break;
            }
            if(mcd(clave,m)==1)end=1;
        }
      return clave;

}