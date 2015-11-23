#######################
###MAKEFILE############
#######################
CC = gcc
ODIR = obj/
all: seg-perf

seg-perf: funcionesTextos.o gClaves.o seg-perf.o probabilidad.o
	gcc -o $@ $(ODIR)seg-perf.o $(ODIR)gClaves.o $(ODIR)funcionesTextos.o $(ODIR)probabilidad.o
funcionesTextos.o: funcionesTextos.c
	gcc -c $< -o $(ODIR)funcionesTextos.o	
gClaves.o: gClaves.c
	gcc -c $< -o $(ODIR)gClaves.o
seg-perf.o: seg-perf.c
	gcc -c $< -o $(ODIR)seg-perf.o
probabilidad.o: probabilidad.c
	gcc -c $< -o $(ODIR)probabilidad.o
clean:
	@rm -R $(ODIR)* seg-perf 