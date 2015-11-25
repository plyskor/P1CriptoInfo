#######################
###MAKEFILE############
#######################
CC = gcc
ODIR = obj/
NOW = -w
all: seg-perf desECB linealidadSBoxesDES linealidadSBoxesAES SAC_BIC_AES SAC_BIC_DES

SAC_BIC_AES: SAC_BIC_AES.o funcionesAES.o
	$(CC) -o $@ $(ODIR)SAC_BIC_AES.o $(ODIR)funcionesAES.o
SAC_BIC_DES: SAC_BIC_DES.o funcionesDES.o
	$(CC) -o $@ $(ODIR)SAC_BIC_DES.o $(ODIR)funcionesDES.o
linealidadSBoxesAES: linealidadSBoxesAES.o
	$(CC) -o $@ $(ODIR)linealidadSBoxesAES.o
linealidadSBoxesDES: linealidadSBoxesDES.o funcionesDES.o
	$(CC) -o $@ $(ODIR)linealidadSBoxesDES.o $(ODIR)funcionesDES.o
desECB: desECB.o funcionesDES.o 
	$(CC) -o $@ $(ODIR)desECB.o $(ODIR)funcionesDES.o
seg-perf: funcionesTextos.o gClaves.o seg-perf.o probabilidad.o
	$(CC) -o $@ $(ODIR)seg-perf.o $(ODIR)gClaves.o $(ODIR)funcionesTextos.o $(ODIR)probabilidad.o
funcionesTextos.o: funcionesTextos.c
	$(CC) -c $< -o $(ODIR)funcionesTextos.o
linealidadSBoxesDES.o: linealidadSBoxesDES.c
	$(CC) -c $< -o $(ODIR)linealidadSBoxesDES.o
linealidadSBoxesAES.o: linealidadSBoxesAES.c
	$(CC) -c $< -o $(ODIR)linealidadSBoxesAES.o
gClaves.o: gClaves.c
	$(CC) -c $< -o $(ODIR)gClaves.o
seg-perf.o: seg-perf.c
	$(CC) -c $< -o $(ODIR)seg-perf.o
probabilidad.o: probabilidad.c
	$(CC) -c $< -o $(ODIR)probabilidad.o
funcionesDES.o: funcionesDES.c
	$(CC) -c $< -o $(ODIR)funcionesDES.o
funcionesAES.o: funcionesAES.c
	$(CC) -c $< -o $(ODIR)funcionesAES.o
desECB.o: desECB.c
	$(CC) -c $< -o $(ODIR)desECB.o
SAC_BIC_DES.o: SAC_BIC_DES.c
	$(CC) $(NOW) -c $< -o $(ODIR)SAC_BIC_DES.o
SAC_BIC_AES.o: SAC_BIC_AES.c
	$(CC) $(NOW) -c $< -o $(ODIR)SAC_BIC_AES.o
clean:
	rm -f -R $(ODIR)* seg-perf desECB linealidadSBoxesDES linealidadSBoxesAES SAC_BIC_AES SAC_BIC_DES