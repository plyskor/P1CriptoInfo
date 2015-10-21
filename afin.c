#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "funciones_gmp.h"
#define TAM 50
/*#include "gmp.h"*/


void init_mpz_vector(mpz_t *vector,int size);

int cifra_caracter_afin(int cha, mpz_t a, mpz_t b , mpz_t m){
  if(cha==10){
    cha=32;
  } 
  int cint,mAux;
  mAux = mpz_get_ui(m);
  if(cha>64 && cha<91){
    cha+=32;
  }
  if(cha<97 || cha>122){
    if(cha == 32){
      cha = mAux-1;
    }else{
      printf("ERROR, esto no es una letra\n");
      return(-1);
    }
    
  }
  if(cha!=(mAux-1)){
    cha-=97;
  }
  
  mpz_t p,c,aux, x, mod;
  mpz_init(p);
  mpz_init(c);
 mpz_init(aux);
  mpz_init(x);
  mpz_init(mod);


  mpz_set_ui(p,cha);
  mpz_mul(aux,a,p);

  mpz_add(c,aux,b);
  mpz_cdiv_qr(x,mod,c,m);
  //gmp_printf("modulo \n");
  if(mpz_cmp_ui(mod,0)<0){
    
    mpz_add(mod,mod,m);
  }

  cint = mpz_get_ui(mod);


  if(cint==mAux-1){
    cint = 32;
  }else{
    cint+=97;
  }
  

  mpz_clear(c);
  mpz_clear(aux);
  mpz_clear(x); 
  mpz_clear(mod);
  mpz_clear(p);
  return cint;
}

int descifra_caracter_afin(int cha, mpz_t a, mpz_t b , mpz_t m){
  if(cha==10){
    cha=32;
  } 
  int cifint=0,mAux;
  mpz_t cif;
   mAux = mpz_get_ui(m);
  if(cha>64 && cha<91){
    cha+=32;
  }
  if(cha<97 || cha>122){
    if(cha == 32){
      cha = mAux-1;
    }else{
      printf("ERROR, esto no es una letra\n");
      return(-1);
    }
    
  }
  if(cha!=(mAux-1)){
    cha-=97;
  }

  mpz_init_set_ui(cif,cha);
  mpz_sub(cif,cif,b);
  mpz_mul(cif, cif,a);
  mpz_mod(cif,cif,m);

  cifint = mpz_get_ui(cif);
  mpz_clear(cif);

  if(cifint==mAux-1){
    cifint = 32;
  }else{
    cifint+=97;
  }
  return cifint;

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
    gmp_printf("El resultado de euclides extendido es: mcd = %Zd , inverso de a = %Zd \n", mcd , inva);
    if( mpz_cmp_ui (mcd, 1) !=0){
      printf("Error\n");
      return(0);
    }

    //abro los ficheros
    FILE *f;
    FILE *out;
    f = fopen(argv[9], "r");
    out = fopen(argv[11] , "w");


  
    
    int pint;
    char cint;

    

    while(!feof(f)){
      pint=fgetc(f);
      if(pint == -1){
        break;
      }
  
      if(strcmp(argv[1],"-C")==0){
    //El programa cifra 
        cint=cifra_caracter_afin(pint,a,b,m);
        

      }else if(strcmp(argv[1],"-D")==0){
        cint = descifra_caracter_afin(pint, inva, b ,m);
      }
     if(cint == -1) continue;
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