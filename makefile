
all:	
	gcc -o afin afin.c funciones_gmp.c -lgmp -L.
	gcc -o afinModificado afinModificado.c funciones_gmp.c -lgmp -L.
	gcc -o vigenere vigenere.c
	gcc -o kasiski kasiski.c funciones.c
	gcc -o IC IC.c funciones.c
	gcc -o hill hill.c matrix.c
