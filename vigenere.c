#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
int mod(int a, int b);
int conv_ascii(int l){
  if(l==10){
    l=32;
  }
  if(l>64 && l<91){
     l+=32;
  }
        if(l==32){
            return 26;
        }
  if(l<97 || l>122){
     printf("ERROR, %d esto no es una letra\n",l);
     return(-1);
  }
  l-=97;
  return(l);
}

int cifra_vigenere(int plano , int clave , int m){
  int cifrado;
  cifrado = mod(plano + clave , m);
        if(cifrado==26){
            cifrado=32;
            return cifrado;
        }
  cifrado+=65; //Para pasarlo a ascii
  return cifrado;

}
int descifra_vigenere(int cifrado , int clave , int m){
  int descifrado;
  descifrado = mod(cifrado - clave , m);
        if(descifrado==26){
            descifrado=32;
            return descifrado;
        }
  descifrado+=65; //Para pasarlo a ascii
  return descifrado;

}

int mod(int a, int b){
  int ret = a%b;
  if(ret<0){
    ret+=b;
  }
  return ret;
}

int main (int argc,char *argv[]) {

  if(argc!=10){
      printf("Los argumentos del programa deben ser: vigenere {-C|-D} {-k clave} {-m |Zm|} [-i filein] [-o fileout]\n");
      return(0);
    }
    char *clave;
    clave = (char *) malloc (MAX);
    int l,i,size,claveInt, cifrado, m, aux;
    m = atoi(argv[5]);
    i=0;
    strcpy(clave, argv[3]);
    size= strlen(clave);
    
      FILE *f , *out;
      f= fopen(argv[7],"r");
      out = fopen(argv[9] , "w");
      while(!feof(f)){
        l =fgetc(f);
        if(l == -1){
            break;
        }
        l = conv_ascii(l);
        aux = (int)clave[i];

        claveInt = conv_ascii(aux);
        if(strcmp(argv[1],"-C")==0){
        cifrado = cifra_vigenere(l , claveInt ,m);
                        if(cifrado==-1) continue;
        
        }else if(strcmp(argv[1],"-D")==0){
          cifrado = descifra_vigenere(l , claveInt ,m);
        }
      fprintf(out,"%c",cifrado);
        i++;
      if(i==size) i=0;
    }
    fclose(f);
    fclose(out);
    free(clave);
    return (0);
  }