#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc
//#include <ucontext.h>
#include "fifo.h"

int main(int argc, char* argv[]) {
    FIFO_DESC f;
    FIFO_PCB* e;
    PCB p;

    printf("Criando a Fila:\n");
    cria_fifo(&f);
    imprime_fifo(&f);

    printf("Inserindo elementos:\n");
    p.pid = 0; p.prio = 0; p.estado = 0;
    insere_fifo(&f, p);
    imprime_fifo(&f);
    p.pid = 1; p.prio = 1; p.estado = 1;
    insere_fifo(&f, p);
    imprime_fifo(&f);
    p.pid = 2; p.prio = 2; p.estado = 2;
    insere_fifo(&f, p);
    imprime_fifo(&f);

    printf("Removendo elementos:\n");
    remove_fifo(&f);
    imprime_fifo(&f);

    printf("Consultando o PCB:");
    e = consulta_fifo(&f);
    imprime_pcb(e->pcb);
    printf("teste consulta:\n");
    imprime_pcb(f.prim->pcb);
    printf("\n");

    printf("Destruindo a Fila:\n");
    destroi_fifo(&f);
    imprime_fifo(&f);

    return 0;
}
