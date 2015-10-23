#include "funciones_gmp.h"
#include <stdio.h>
#include <stdlib.h>

void euclidesExtendido(const mpz_t a, const mpz_t b,mpz_t mcd, mpz_t s, mpz_t t){
  int flag = 0;

  mpz_t x,aux,r1,r2,s1,s2,t1,t2,coc,rest;
  mpz_init(x);
  mpz_init(aux);
  mpz_init(coc);
  mpz_init(rest);
  mpz_init(t1);
  mpz_init(s2);
 

  if(mpz_cmp(a,b)>0){
    mpz_init_set(r1,a);
    mpz_init_set(r2 , b);
  }else{
    mpz_init_set(r1,b);
    mpz_init_set(r2 ,a);
    flag = 1;
  }
 

  mpz_init_set_ui(s1,1);
  mpz_init_set_ui(t2,1);

  while(mpz_cmp_ui(r2,0)!=0){

    mpz_tdiv_qr(coc,rest,r1,r2);
    mpz_set(r1,r2);
    mpz_set(r2,rest);

    mpz_mul(x,coc,s2);
    mpz_sub(aux,s1,x);
    mpz_set(s1,s2);
    mpz_set(s2,aux);

    mpz_mul(x,coc,t2);
    mpz_sub(aux,t1,x);
    mpz_set(t1,t2);
    mpz_set(t2,aux);
  }

  
  mpz_set(mcd,r1);
  
  if(flag==1){
    
    mpz_set(s,t1);
    mpz_set(t,s1);
  }else{
    mpz_set(s,s1);
    mpz_set(t,t1);
  }
  if(mpz_cmp_ui(s,0)<0){
      mpz_add(s,s,b);
  }
  mpz_clear(x);
  mpz_clear(aux);
  mpz_clear(r1);
  mpz_clear(r2);
  mpz_clear(s1);
  mpz_clear(s2);
  mpz_clear(t1);
  mpz_clear(t2);
  mpz_clear(coc);
  mpz_clear(rest);
  return;
}
