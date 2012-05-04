cc = gcc
flags = -Wall


all: teste1 teste2 teste3 teste4 teste5 teste6 teste7

#-lsisop refere-se a libsisop.a no diretorio lib adicionado a lista de diretorios do linker por -L./lib ('.' eh o diretorio corrente)
teste1: testes/teste1.c libsisop.a	
	$(cc) -o bin/teste1 testes/teste1.c -L./lib -lsisop $(flags)
	
teste2: testes/teste2.c libsisop.a	
	$(cc) -o bin/teste2 testes/teste2.c -L./lib -lsisop $(flags)
	
teste3: testes/teste3.c libsisop.a	
	$(cc) -o bin/teste3 testes/teste3.c -L./lib -lsisop $(flags)
	
teste4: testes/teste4.c libsisop.a	
	$(cc) -o bin/teste4 testes/teste4.c -L./lib -lsisop $(flags)
	
teste5: testes/teste5.c libsisop.a	
	$(cc) -o bin/teste5 testes/teste5.c -L./lib -lsisop $(flags)
	
teste6: testes/teste6.c libsisop.a	
	$(cc) -o bin/teste6 testes/teste6.c -L./lib -lsisop $(flags)
	
teste7: testes/teste7.c libsisop.a	
	$(cc) -o bin/teste7 testes/teste7.c -L./lib -lsisop $(flags)
	
libsisop.a: unucleo fifo	
	ar crs lib/libsisop.a lib/unucleo.o lib/fifo.o
	
unucleo: src/unucleo.c include/unucleo.h fifo
	$(cc) -o lib/unucleo.o -c src/unucleo.c $(flags)

#minha lib para controle de listas, etc
fifo: src/fifo.c include/fifo.h
	$(cc) -o lib/fifo.o -c src/fifo.c $(flags)

clean:
	rm -rf */*o
	rm -rf */*a
	rm -rf bin/*


