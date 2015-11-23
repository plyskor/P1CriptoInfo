#######################
###MAKEFILE############
#######################
CC = gcc
ODIR = obj/
all: seg-perf desECB SAC linealidadSBoxesDES

linealidadSBoxesDES: linealidadSBoxesDES.o funcionesDES.o
	gcc -o $@ $(ODIR)linealidadSBoxesDES.o $(ODIR)funcionesDES.o
desECB: desECB.o funcionesDES.o 
	gcc -o $@ $(ODIR)desECB.o $(ODIR)funcionesDES.o
SAC: SAC.o funcionesDES.o 
	gcc -o $@ $(ODIR)SAC.o $(ODIR)funcionesDES.o 
seg-perf: funcionesTextos.o gClaves.o seg-perf.o probabilidad.o
	gcc -o $@ $(ODIR)seg-perf.o $(ODIR)gClaves.o $(ODIR)funcionesTextos.o $(ODIR)probabilidad.o
funcionesTextos.o: funcionesTextos.c
	gcc -c $< -o $(ODIR)funcionesTextos.o
linealidadSBoxesDES.o: linealidadSBoxesDES.c
	gcc -c $< -o $(ODIR)linealidadSBoxesDES.o
SAC.o: SAC.c
	gcc -c $< -o $(ODIR)SAC.o
gClaves.o: gClaves.c
	gcc -c $< -o $(ODIR)gClaves.o
seg-perf.o: seg-perf.c
	gcc -c $< -o $(ODIR)seg-perf.o
probabilidad.o: probabilidad.c
	gcc -c $< -o $(ODIR)probabilidad.o
funcionesDES.o: funcionesDES.c
	gcc -c $< -o $(ODIR)funcionesDES.o
desECB.o: desECB.c
	gcc -c $< -o $(ODIR)desECB.o
clean:
	rm -f -R $(ODIR)* seg-perf desECB SAC linealidadSBoxesDES