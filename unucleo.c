#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "unucleo.h"
#include "fifo.h"


PCB         executando;
FIFO_DESC   fifo_aptos[PRIORIDADES];
FIFO_DESC   fifo_bloqs;

 ucontext_t contextoSaida;
 int        pidCount;

 /* Funções reservadas do sistema operacional - INICIO */

 //Verifica se tinha algum processo esperando o processo que esta executando, retorna -1 se não houver ninguem
 int verifica_waiters()
 {
    int ret=-1;                                                                             // pid do waiter, retorna -1 se não existir

    if(fifo_bloqs.prim != NULL)
        ret = has_waiter(&fifo_bloqs,executando.pid);                                                   //verifica se possui alguem esperando pelo processo que esta no estado running
    return ret;
 }

 void troca_bloq_to_ready()
 {
    PCB pcb_bloq;
    int pid_bloq = verifica_waiters();
    while(verifica_waiters()>-1)
    {
        pid_bloq = verifica_waiters();
        if(busca_pcb(&fifo_bloqs,pid_bloq,&pcb_bloq)!=-1){                                  //armazena pcb que vai ser liberado na variavel

            remove_pcb(&fifo_bloqs,pid_bloq);                                               //exclui determinado PCB da lista de bloqueados
            insere_fifo(&fifo_aptos[pcb_bloq.prio], pcb_bloq);
            }
    }
}

 // verifica proximo pcb que deverá ser executado
 int pcb_caller(PCB* pcb_result)
 {
    if(fifo_aptos[P_ALTA].prim!=NULL){

        *pcb_result = fifo_aptos[P_ALTA].prim->pcb;
        remove_fifo(&fifo_aptos[P_ALTA]);
        }
	else if(fifo_aptos[P_MEDIA].prim!=NULL){

        *pcb_result = fifo_aptos[P_MEDIA].prim->pcb;
        remove_fifo(&fifo_aptos[P_MEDIA]);
        }
    else if(fifo_aptos[P_BAIXA].prim!=NULL){

        *pcb_result = fifo_aptos[P_BAIXA].prim->pcb;
        remove_fifo(&fifo_aptos[P_BAIXA]);
        }
    else
        return -1;                                                                  // todas as filas estão vazias
    return pcb_result->pid;
 }

 void pcb_fim()
 {
    PCB pcb_ready;
    printf("\n\nVerifica fim.");
    troca_bloq_to_ready();                                                                 // Processos que estavam esperando o processo em execução são liberados aqui

    if(pcb_caller(&pcb_ready)<0)
        exit(0);

    executando = pcb_ready;
    setcontext(&pcb_ready.contexto);
}

void ini_make(ucontext_t* contexto)
{
    char all_stack[SIGSTKSZ];

    contexto->uc_stack.ss_sp    = all_stack;
	contexto->uc_stack.ss_size  = sizeof(all_stack);
	contexto->uc_stack.ss_flags = 0;

}
 /* Funções reservadas do sistema operacional - FIM */

int libsisop_init()
{
    PCB init_pcb;
    int i;
    pidCount = 1;
    ucontext_t contextoInit;

    cria_fifo(&fifo_bloqs);                                                          // Cria uma fila de bloqueados
    for(i = 0;i<PRIORIDADES-1;i++)                                                 // Cria uma fila para cada prioridade
        cria_fifo(&fifo_aptos[i]);

    getcontext(&contextoSaida);
	ini_make(&contextoSaida);
	makecontext(&contextoSaida,(void (*)(void)) pcb_fim, 0);

    getcontext(&contextoInit);

	contextoInit.uc_link = &contextoSaida;
    init_pcb.pid         = pidCount;
    init_pcb.contexto    = contextoInit;
    init_pcb.prio        = P_ALTA;
    init_pcb.estado      = APTO;

    pidCount++;
    //insere_fifo(&fifo_aptos[P_ALTA], init_pcb);                                   //Main que está rodando, naoão precisa ser adicionado

    executando = init_pcb;
	return init_pcb.pid;

}

int mproc_create(int prio, void *(*start_routine)(void*), void *arg)
{
    PCB pcb_add;

    if (prio<1 || prio>2)
	{
 		printf("Sem permissão para inserir processos com prioridade de sistema (0). \n");
		return -1;
	}
	pcb_add.pid = pidCount;
	pcb_add.prio= prio;
	pcb_add.pid_wait = -1;
    pidCount++;

    getcontext(&pcb_add.contexto);
	ini_make(&pcb_add.contexto);
	makecontext(&pcb_add.contexto, (void (*)(void)) start_routine, 1, arg);

    pcb_add.contexto.uc_link = &contextoSaida;

    insere_fifo(&fifo_aptos[prio], pcb_add);

	return pcb_add.pid;
}

int mproc_join(int pid)
{
    PCB prox_pcb,ant_pcb;

    if (pcb_caller(&prox_pcb)>-1)
    {
        executando.pid_wait = pid;
        ant_pcb    = executando;

        prox_pcb.contexto.uc_link = &ant_pcb.contexto;

        executando = prox_pcb;


        insere_fifo(&fifo_bloqs,ant_pcb);
        swapcontext(&ant_pcb.contexto,&executando.contexto);
    }
    return 0;
}


void mproc_yield(void)
{
    PCB prox_pcb,ant_pcb;

    if (pcb_caller(&prox_pcb)>-1)
    {
        insere_fifo(&fifo_aptos[executando.prio], executando);
        ant_pcb    = executando;
        executando = prox_pcb;
        swapcontext(&ant_pcb.contexto,&executando.contexto);
    }
}

