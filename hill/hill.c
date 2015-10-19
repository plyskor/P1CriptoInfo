#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "matrix.h"
int conv_ascii(int *bloque,int i){
  if(bloque[i]>64 && bloque[i]<91){
     bloque[i]+=32;
  }
        if(bloque[i]==32){
            return 26;
        }
  if(bloque[i]<97 || bloque[i]>122){
     printf("ERROR, esto no es una letra %d\n",bloque[i]);
     return(-1);
  }
  bloque[i]-=97;
  return(bloque[i]);
}
void cifraHill(int * bloque, int *cifrado,matrix *m,int dim){
    int i=0,j=0;
    long int aux=0;
    for(i=0;i<m->size;i++){
        for(j=0;j<m->size;j++){
           aux=aux+(bloque[i]*(int)getValue(m,j,i)); 
        }
        cifrado[i]=(int)aux%dim;
        if(cifrado[i]==26)cifrado[i]=32;
        aux=0;
        printf("%c",cifrado[i]+97);
    }
    return;
}
int mcd(int a, int b) {
    int i,r[50];
    if(a<0)a*=-1;
    if(b<0)b*=-1;
    for(i=0;i<50;i++){
        r[i]=0;
    }
    r[0]=a;
    r[1]=b;
    i=1;
    while(r[i]!=0){
        r[i+1]=r[i-1]%r[i];
        i++;
    }
    return r[i-1];
}
int main (int argc,char *argv[]) {
    int i=0,m=0,n=0,detint=0,cha=0;
    int *bloque,*cifrado;
    double det=0;
    FILE *fmatrix, *fin, *fout;
    matrix *K;
    /*LECTURA DE ARGUMENTOS DE ENTRADA*/
    if(argc !=12){
        printf("El programa ha de ser invocado asi: hill [-C|-D] [-m |Zm|] [-n Nk] [-k filematriz] [-i infile] [-o outfile]\n");
        return(0);
    }
    m=atoi(argv[3]);
    n=atoi(argv[5]);
    if((n<0)||(m<0)){
        printf("Valores no validos para m o n");
        return(0);
    }
    /*Inicializamos la estructura de datos para la matriz*/
    K=initMatrix(n);
    /*Leemos la matriz del fichero */
    fmatrix=fopen(argv[7],"r");
    if(!fmatrix){
        printf("Error al abrir el archivo %s\n",argv[7]);
        return -1;
    }
    readMatrix(fmatrix,K);
    fclose(fmatrix);
    /*Comprobamos la matriz de claves*/
    if(detMatrix(K)==0){
        printf("LA matriz de claves debe ser no singular\n");
        eraseMatrix(K);
        return(-1);
    }
    printf("jo");
    detint=(int)detMatrix(K);
    printf("%d\n",detint);
    /*if(mcd(detint,m)!=1){
        printf("La matriz de claves proporcionada no define una función inyectiva.\n");
        eraseMatrix(K);
        return(-1);
    }*/
    printf("jo");
    /*Si todo va bien vamos al cifrado o descifrado*/
    /*Abrimos los ficheros*/
    fin=fopen(argv[9],"r");
    if(!fin){
        printf("Error al abrir el fichero de entrada %s\n",argv[9]);
    }
    fout=fopen(argv[11],"w");
    if(!fout){
        printf("Error al abrir el fichero de salida %s\n",argv[9]);
    }
    printf("jo");
    if(strcmp(argv[1],"-C")==0){
        /*CIFRADO*/
        printf("jo");
        bloque=(int*)malloc(n*sizeof(int));
        if(!bloque){
            fclose(fin);
            fclose(fout);
            return(-1);
        }
        cifrado=(int*)malloc(n*sizeof(int));
        if(!cifrado){
            fclose(fin);
            fclose(fout);
            return(-1);
        }
        for(i=0;i<n;i++){
            bloque[i] = fgetc(fin);
            printf("jo");
            if (bloque[i] == -1) {
                while(i<n){
                    /*rellenamos con espacios el ultimo bloque si se llega al fin de fichero*/
                    bloque[i]=32;
                }
                break;
            }
            printf("jo");
            bloque[i] = conv_ascii(bloque,i);
            printf("Jo");
            if(bloque[i]==-1){
                i--;
                continue;
            }
            if(i==n-1){
                //cifraHill(bloque,cifrado,K,m);
                for(i=0;i<n;i++){
                   fprintf(fout,"%c",bloque[i]+97);
                }
                i=-1;
            }
        }
        //cifraHill(bloque,cifrado,K,m);
        for(i=0;i<n;i++){
            fprintf(fout,"%c",(bloque[i]+97));
         }
        
        
        
    }
    if(strcmp(argv[1],"-D")){
        /*DESCIFRADO*/
    }
    /*CERRAMOS FICHEROS ABIERTOS*/
    free(bloque);
    fclose(fin);
    fclose(fout);
    return(0);
}