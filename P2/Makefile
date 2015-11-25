#######################
###MAKEFILE############
#######################
CC = gcc
ODIR = obj/
all: seg-perf desECB SAC linealidadSBoxesDES linealidadSBoxesAES

linealidadSBoxesAES: linealidadSBoxesAES.o
	$(CC) -o $@ $(ODIR)linealidadSBoxesAES.o
linealidadSBoxesDES: linealidadSBoxesDES.o funcionesDES.o
	$(CC) -o $@ $(ODIR)linealidadSBoxesDES.o $(ODIR)funcionesDES.o
desECB: desECB.o funcionesDES.o 
	$(CC) -o $@ $(ODIR)desECB.o $(ODIR)funcionesDES.o
SAC: SAC.o funcionesDES.o 
	$(CC) -o $@ $(ODIR)SAC.o $(ODIR)funcionesDES.o 
seg-perf: funcionesTextos.o gClaves.o seg-perf.o probabilidad.o
	$(CC) -o $@ $(ODIR)seg-perf.o $(ODIR)gClaves.o $(ODIR)funcionesTextos.o $(ODIR)probabilidad.o
funcionesTextos.o: funcionesTextos.c
	$(CC) -c $< -o $(ODIR)funcionesTextos.o
linealidadSBoxesDES.o: linealidadSBoxesDES.c
	$(CC) -c $< -o $(ODIR)linealidadSBoxesDES.o
linealidadSBoxesAES.o: linealidadSBoxesAES.c
	$(CC) -c $< -o $(ODIR)linealidadSBoxesAES.o
SAC.o: SAC.c
	$(CC) -c $< -o $(ODIR)SAC.o
gClaves.o: gClaves.c
	$(CC) -c $< -o $(ODIR)gClaves.o
seg-perf.o: seg-perf.c
	$(CC) -c $< -o $(ODIR)seg-perf.o
probabilidad.o: probabilidad.c
	$(CC) -c $< -o $(ODIR)probabilidad.o
funcionesDES.o: funcionesDES.c
	$(CC) -c $< -o $(ODIR)funcionesDES.o
desECB.o: desECB.c
	$(CC) -c $< -o $(ODIR)desECB.o
clean:
	rm -f -R $(ODIR)* seg-perf desECB SAC linealidadSBoxesDES linealidadSBoxesAES