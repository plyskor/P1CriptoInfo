#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gClaves.h"

#include <sys/time.h>

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

int generaClaveAEquiprobable( int m){
  struct timeval t;
  int pid ; // get it as per your OS

gettimeofday(&t, NULL);
srand(t.tv_usec * t.tv_sec * pid);
   int i=0,end=0;
      int clave;
        while(end==0){
            clave = rand() % m;
            if(clave==0)continue;
            if(mcd(clave,m)==1)end=1;
        }
      return clave;
}

int generaClaveBEquiprobable( int m){
  struct timeval t;
  int pid ; // get it as per your OS

gettimeofday(&t, NULL);
srand(t.tv_usec * t.tv_sec * pid);
   int i=0,end=0;
      int clave;
       
            clave = rand() % m;
           
        
      return clave;
}

int generaClavesNoEquiprobable(int m){
  struct timeval t;
  int pid ; // get it as per your OS

gettimeofday(&t, NULL);
srand(t.tv_usec * t.tv_sec * pid);
   int i,end=0;
      int clave;
         clave = rand() % m;
      // de esta forma es mucho más probable una clave menor que m/2 que una mayor
      while(end==0){
                    if(clave>(m/2)){
                            clave = rand() % m;
                            if(clave==0)continue;
                    }else break;
            
            if(mcd(clave,m)==1)end=1;
        }
      return clave;

}