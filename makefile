
all:	
	gcc -o afin afin.c funciones_gmp.c -lgmp -L.
	gcc -o afinModificado afinModificado.c funciones_gmp.c -lgmp -L.
	gcc -o vigenere vigenere.c
	gcc -o kasiski kasiski.c funciones.c
	gcc -o IC IC.c funciones.c
	gcc -o 
	gcc -o hill hill.c matrix.c

afin:
	gcc -o afin afin.c funciones_gmp.c -lgmp -L.

afinModificado:
	gcc -o afinModificado afinModificado.c funciones_gmp.c -lgmp -L.

vigenere:
	gcc -o vigenere vigenere.c

kasiski:
	gcc -o kasiski kasiski.c funciones.c

ic:
	gcc -o IC IC.c funciones.c