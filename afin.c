#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#define TAM 50
/*#include "gmp.h"*/


void init_mpz_vector(mpz_t *vector,int size);

int cifra_caracter_afin(int cha, mpz_t a, mpz_t b , mpz_t m){
  int cint;

  if(cha>64 && cha<91){
    cha+=32;
  }
  if(cha<97 || cha>122){
    printf("ERROR, esto no es una letra\n");
    return(0);
  }
 
  cha-=97;
  mpz_t p,c,aux, x, mod;
  mpz_init(p);
  mpz_init(c);
 mpz_init(aux);
  mpz_init(x);
  mpz_init(mod);


  mpz_set_ui(p,cha);
  mpz_mul(aux,a,p);
gmp_printf("modulo \n");
  mpz_add(c,aux,b);
  mpz_cdiv_qr(x,mod,c,m);
  //gmp_printf("modulo \n");
  if(mpz_cmp_ui(mod,0)<0){
    mpz_set_ui(aux,27);
    mpz_add(mod,mod,aux);
  }

  cint = mpz_get_ui(mod);

  cint+=97;

  mpz_clear(c);
  mpz_clear(aux);
  mpz_clear(x); 
  mpz_clear(mod);
  mpz_clear(p);
  return cint;
}

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

    mpz_cdiv_qr(coc,rest,r1,r2);
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


void init_mpz_vector(mpz_t *vector,int size){
  int i=0;
  if(size<=0)return;
  for(i=0;i<size;i++){
    mpz_init(vector[i]);
  }return;
}

/* PROGRAMA PRINCIPAL */
int main (int argc,char *argv[]) {
  mpz_t a,m,b , mcd , inva , invb;
  if(argc!=12){
    printf("Los argumentos del programa deben ser: afin {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n");
    return(0);
  }

  if(strcmp(argv[1],"-C")==0){
    //El programa cifra 
     mpz_init_set_str(a,argv[5],10);
     mpz_init_set_str(m,argv[3],10);
     mpz_init_set_str(b,argv[7],10);
     mpz_init(mcd);
     mpz_init(inva);
     mpz_init(invb);

     //mpz_add(b,a,m);
    if((mpz_cmp(a, m) > 0) || (mpz_cmp(b, m) > 0)) {
      printf("Error\n");
      return(0);
    }

    euclidesExtendido(a, m, mcd,inva,invb);
    //gmp_printf("El resultado de euclides extendido es: mcd = %Zd , inverso de a = %Zd \n", mcd , inva);
    if( mpz_cmp_ui (mcd, 1) !=0){
      printf("Error\n");
      return(0);
    }

    //abro los ficheros
    FILE *f;
    FILE *out;
    int pint;
    char cint;

    f = fopen(argv[9], "r");
    out = fopen(argv[11] , "w");

    while(!feof(f)){
      pint=fgetc(f);
      if(pint == -1){
        break;
      }
      printf("pint : %d\n", pint);

      cint=cifra_caracter_afin(pint,a,b,m);
      
      fprintf(out,"%c",cint);

    }

    fclose(f);
    fclose(out);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    mpz_clear(inva);
    mpz_clear(invb);
    mpz_clear(mcd);
    return(0);

  }
  return(0);
}