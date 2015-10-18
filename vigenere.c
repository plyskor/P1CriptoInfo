#include <stdio.h>
#include <stdlib.h>

#define MAX 80

int conv_ascii(int l){
	if(l>64 && l<91){
 	   l+=32;
 	}
 	if(l<97 || l>122){
 	   printf("ERROR, esto no es una letra\n");
 	   return(0);
 	}
 	l-=97;
 	return(l);
}

int cifra_vigenere(int plano , int clave , int m){
	int cifrado;
	cifrado = mod(plano + clave , m);
	cifrado+=97; //Para pasarlo a ascii
	return cifrado;

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
  	  printf("Los argumentos del programa deben ser: afin {-C|-D} {-k clave} {-m |Zm|} [-i filein] [-o fileout]\n");
  	  return(0);
  	}
  	char *clave;
  	clave = (char *) malloc (MAX);
  	int l,i,size,claveInt, cifrado, m, aux;
  	m = atoi(argv[5]);
  	i=0;
  	strcpy(clave, argv[3]);
  	size= strlen(clave);
  	if(strcmp(argv[1],"-C")==0){
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
  			cifrado = cifra_vigenere(l , claveInt ,m);
  			fprintf(out,"%c",cifrado);
  			i++;
 			if(i==size) i=0;
  		}
  		fclose(f);
  		fclose(out);
  		free(clave);
  		return (0);
  	}

	return(0);
}