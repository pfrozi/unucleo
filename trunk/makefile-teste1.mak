# <- Comentários sempre iniciam por "#"
#
############################# Makefile ##########################
all: teste1
teste1: teste1.o unucleo.o fifo.o
	gcc -o teste1 teste1.o unucleo.o fifo.o
#-----> Usar TAB e nao espacos

teste1.o: teste1.c
	gcc -o teste1.o -c teste1.c

unucleo.o: unucleo.c
	gcc -o unucleo.o -c unucleo.c

fifo.o: fifo.c
	gcc -o fifo.o -c fifo.c

clean:
	rm -rf *.o
    
mrproper: clean
	rm -rf teste1
 