# <- Comentários sempre iniciam por "#"
#
############################# Makefile ##########################
all: fifo_teste
fifo_teste: fifo_teste.o fifo.o
	gcc -o fifo_teste fifo_teste.o fifo.o
#-----> Usar TAB e nao espacos

fifo_teste.o: fifo_teste.c
	gcc -o fifo_teste.o -c fifo_teste.c

fifo.o: fifo.c
	gcc -o fifo.o -c fifo.c

clean:
	rm -rf *.o
    
mrproper: clean
	rm -rf fifo_teste
 