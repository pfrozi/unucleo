#include <ucontext.h>

typedef struct PCB
	{
       int         pid;
       int         status;
       int         prio;
       int         pid_wait;
       ucontext_t  context;
       struct PCB* prox;
       };



PCB* cria_lista(void);
PCB* insere_ord (PCB *l, int pid, int status, int prio, ucontext_t context);
void imprime(PCB* l);
PCB* remove(PCB* l, int pid);
PCB* destroi(PCB* l);

