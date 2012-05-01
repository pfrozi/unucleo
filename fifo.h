//#include <ucontext.h>

typedef struct PCB {
    int pid;
    //ucontext_t contexto;
    int prio;
    int estado;
    int pid_wait;                   // Processo que ele aguardará o termino
} PCB;

typedef struct FIFO_PCB {
    PCB pcb;
    struct FIFO_PCB* prox;
}FIFO_PCB;

typedef struct FIFO_DESC {
    FIFO_PCB* prim;
    FIFO_PCB* ult;
}FIFO_DESC;

void cria_fifo(FIFO_DESC* f);
int insere_fifo(FIFO_DESC* f, PCB p);
FIFO_PCB* consulta_fifo(FIFO_DESC* f);
int remove_fifo(FIFO_DESC* f);
void destroi_fifo(FIFO_DESC* f);

void imprime_pcb(PCB p);
void imprime_fifo(FIFO_DESC* f);

int has_waiter(FIFO_DESC* f, int pid);               //verifica se a fila possui algum elemento com pid_wait=pid, se sim, retorna o pid desse cara, senão retorna -1
int busca_pcb(FIFO_DESC* f, int pid, PCB* result);   //percorre fila buscando PCB com  pid=pid, resultado é armazenado em result
int remove_pcb(FIFO_DESC* f, int pid);               //remove pcb especifico
