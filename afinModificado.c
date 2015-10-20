#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#define TAM 50
/*#include "gmp.h"*/


void init_mpz_vector(mpz_t *vector,int size);

int* cifra_caracter_afinModificado(int *cha, mpz_t a, mpz_t b , mpz_t m){
  int *cint,chaAux,mAux;
  cint = (int *) malloc (2*(sizeof(int)));
  mAux = mpz_get_ui(m);
  if(cha[0]>64 && cha[0]<91){
    cha[0]+=32;
  }
  if(cha[0]<97 || cha[0]>122){
    if(cha[0]==32){
      cha[0]=(mAux -1);
    }else{
      printf("ERROR, esto no es una letra , %d\n", cha[0]);
    return(NULL);
    }  
  }
  if(cha[1]>64 && cha[1]<91){
    cha[1]+=32;
  }
  if(cha[1]<97 || cha[1]>122){
    if(cha[1]==32){
      cha[1]=(mAux -1);
    }else{
      printf("ERROR, esto no es una letra , %d\n", cha[0]);
    return(NULL);
    }  
  }
 
  if(cha[0]!= (mAux -1)) cha[0]-=97;
  if(cha[1]!= (mAux -1)) cha[1]-=97;

  

  chaAux = (cha[0]*mAux) + cha[1];


  mpz_t p,c,aux, x, mod;
  mpz_init(p);
  mpz_init(c);
  mpz_init(aux);
  mpz_init(x);
  mpz_init(mod);
  


  mpz_set_ui(p,chaAux);
  mpz_mul(aux,a,p);

  mpz_add(c,aux,b);
  mpz_mul(aux, m ,m);
  mpz_mod(c,c,aux);

   
  mpz_tdiv_qr(x,mod,c,m);


  if(mpz_cmp_ui(mod,0)<0){
    mpz_add(mod,mod,m);
  }

  cint[0] = mpz_get_ui(x);
  cint[1] = mpz_get_ui(mod);

  if(cint[0]==(mAux -1)){
    cint[0] = 32;
  }else{
    cint[0]+=97;
  }
  

  if(cint[1]==(mAux -1)){
    cint[1] = 32;
  }else{
    cint[1]+=97;
  }
 

  mpz_clear(c);
  mpz_clear(p);
  mpz_clear(aux);
  mpz_clear(x);
  mpz_clear(mod);

  return cint;
}

int* descifra_caracter_afinModificado(int *cha, mpz_t a, mpz_t b , mpz_t m){
  
  int *cifint,mAux,chaAux;
  mpz_t cif,aux, coc, rest;
  mAux = mpz_get_ui(m);
  if(cha[0]>64 && cha[0]<91){
    cha[0]+=32;
  }
  if(cha[0]<97 || cha[0]>122){
    if(cha[0]==32){
      cha[0]=(mAux -1);
    }else{
      printf("ERROR, esto no es una letra , %d\n", cha[0]);
    return(NULL);
    }  
  }
  if(cha[1]>64 && cha[1]<91){
    cha[1]+=32;
  }
  if(cha[1]<97 || cha[1]>122){
    if(cha[1]==32){
      cha[1]=(mAux -1);
    }else{
      printf("ERROR, esto no es una letra , %d\n", cha[0]);
    return(NULL);
    }  
  }
 
  if(cha[0]!= (mAux -1)) cha[0]-=97;
  if(cha[1]!= (mAux -1)) cha[1]-=97;

  cifint = (int*)malloc(2*(sizeof(int)));

   


  chaAux = (cha[0]*mAux) + cha[1];
  mpz_init(aux);
  mpz_init(coc);
  mpz_init(rest);
  mpz_init_set_ui(cif,chaAux);
  mpz_mul(aux, m ,m);

  mpz_sub(cif,cif,b);
  mpz_mul(cif,cif,a);
  mpz_mod(cif,cif,aux);
  mpz_tdiv_qr(coc, rest,cif,m);

  cifint[0] = mpz_get_ui(coc);
  cifint[1] = mpz_get_ui(rest);

  mpz_clear(cif);
  mpz_clear(aux);
  mpz_clear(coc);
  mpz_clear(rest);

  if(cifint[0]==(mAux -1)){
    cifint[0] = 32;
  }else{
    cifint[0]+=97;
  }

  if(cifint[1]==(mAux -1)){
    cifint[1] = 32;
  }else{
    cifint[1]+=97;
  }
  return cifint;

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


void init_mpz_vector(mpz_t *vector,int size){
  int i=0;
  if(size<=0)return;
  for(i=0;i<size;i++){
    mpz_init(vector[i]);
  }return;
}

/* PROGRAMA PRINCIPAL */
int main (int argc,char *argv[]) {
  mpz_t a,m,b , mcd , inva , invb ,mAux;
  if(argc!=12){
    printf("Los argumentos del programa deben ser: afin {-C|-D} {-m |Zm|} {-a N×} {-b N+} [-i filein] [-o fileout]\n");
    return(0);
  }

 
    //El programa cifra 
     mpz_init_set_str(a,argv[5],10);
     mpz_init_set_str(m,argv[3],10);
     mpz_init_set_str(b,argv[7],10);
     mpz_init(mcd);
     mpz_init(inva);
     mpz_init(invb);
     mpz_init(mAux);

     //mpz_add(b,a,m);
    if((mpz_cmp(a, m) > 0) || (mpz_cmp(b, m) > 0)) {
      printf("Error\n");
      return(0);
    }
    mpz_mul(mAux,m,m);

    euclidesExtendido(a, mAux, mcd,inva,invb);
    gmp_printf("El resultado de euclides extendido es: mcd = %Zd , inverso de a = %Zd \n", mcd , inva);
    if( mpz_cmp_ui (mcd, 1) !=0){
      printf("Error\n");
      return(0);
    }

    //abro los ficheros
    FILE *f;
    FILE *out;
    int pint[2], *cintAux;
    char cint[2];

    f = fopen(argv[9], "r");
    out = fopen(argv[11] , "w");

    while(!feof(f)){

      pint[0]=fgetc(f);

      if(pint[0] == -1){
        break;
      }

      pint[1] = fgetc(f);
      if(pint[1] == -1){
        pint[1] = 32;
      }

       if(strcmp(argv[1],"-C")==0){
      
      cintAux=cifra_caracter_afinModificado(pint,a,b,m);

    }else if(strcmp(argv[1],"-D")==0){
      cintAux=descifra_caracter_afinModificado(pint,inva,b,m);
    }

      cint[0] = cintAux[0];
      cint[1] = cintAux[1];
      free(cintAux);
      fprintf(out,"%c",cint[0]);
      fprintf(out,"%c",cint[1]);

    }

    fclose(f);
    fclose(out);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(m);
    mpz_clear(inva);
    mpz_clear(invb);
    mpz_clear(mcd);
    mpz_clear(mAux);

  return(0);
}