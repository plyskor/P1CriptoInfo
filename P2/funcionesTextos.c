#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionesTextos.h"

int trataCaracter(int c){
	if(c>96 && c <123){
		c-=32;
	}

	if(c>64 && c<91){
		return c-65;
	}

	return -1;
}