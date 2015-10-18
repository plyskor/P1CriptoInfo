#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


int main (int argc,char *argv[]) {
    int m=0, n=0;
    FILE *fmatrix, *fin, *fout;
    if(argc != 12){
        printf("El programa ha de ser invocado asi: hill [-C|-D] [-m |Zm|] [-n Nk] [-k filematriz] [-i infile] [-o outfile]\n");
        return(0);
    }
    m=atoi(argv[3]);
    n=atoi(argv[5]);
    if((n<0)||(m<0)){
        printf("Valores no validos para m o n");
        return(0);
    }
    return(0);
}