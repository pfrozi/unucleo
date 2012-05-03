#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "unucleo.h"
#include "fifo.h"


PCB         executando;
FIFO_DESC   fifo_aptos[PRIORIDADES];
FIFO_DESC   fifo_bloqs;

 ucontext_t scheduler_context;
 int        pidCount;

 /* Funções reservadas do sistema operacional - INICIO */

 //Verifica se tinha algum processo esperando o processo que esta executando, retorna -1 se não houver ninguem
 int verifica_waiters()
 {
    int ret=-1;                                                                             // pid do waiter, retorna -1 se não existir
    printf("procurando waiters ### xx ###");//debug
    if(fifo_bloqs.prim != NULL)
        ret = has_waiter(&fifo_bloqs,executando.pid);                                                   //verifica se possui alguem esperando pelo processo que esta no estado running
    return ret;
 }

 void troca_bloq_to_ready()
 {
    PCB pcb_bloq;
    int pid_bloq = verifica_waiters();
    while(pid_bloq>-1)
    {

        printf("procurando waiters ### %d ###",pid_bloq);//debug
        if(busca_pcb(&fifo_bloqs,pid_bloq,&pcb_bloq)!=-1){                                  //armazena pcb que vai ser liberado na variavel

            remove_pcb(&fifo_bloqs,pid_bloq);                                               //exclui determinado PCB da lista de bloqueados
            insere_fifo(&fifo_aptos[pcb_bloq.prio], pcb_bloq);
            }
        pid_bloq = verifica_waiters();
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

 int pcb_fim()
 {
    PCB pcb_ready;
    printf("\n\nVerifica fim.");
    troca_bloq_to_ready();                                                                 // Processos que estavam esperando o processo em execução são liberados aqui

    if(pcb_caller(&pcb_ready)<0)
        return -1;

    executando = pcb_ready;
    return 0;
}

void ini_make(ucontext_t* contexto,char all_stack[])
{

    contexto->uc_stack.ss_sp    = all_stack;
	contexto->uc_stack.ss_size  = sizeof(all_stack);
	contexto->uc_stack.ss_flags = 0;

}
 /* Funções reservadas do sistema operacional - FIM */

int libsisop_init()
{
    int i;
    pidCount = 1;

    cria_fifo(&fifo_bloqs);                                                          // Cria uma fila de bloqueados
    for(i = 0;i<PRIORIDADES-1;i++)                                                 // Cria uma fila para cada prioridade
        cria_fifo(&fifo_aptos[i]);

    //getcontext(&scheduler_context);

	return 0;

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
    pcb_add.contexto.uc_link = &scheduler_context;

	ini_make(&pcb_add.contexto,pcb_add.all_stack);
	makecontext(&pcb_add.contexto, (void (*)(void)) start_routine, 1, arg);

    insere_fifo(&fifo_aptos[prio], pcb_add);

	return pcb_add.pid;
}

int mproc_join(int pid)
{
//    PCB prox_pcb,ant_pcb;
//
//    if (pcb_caller(&prox_pcb)>-1)
//    {
//        executando.pid_wait = pid;
//        ant_pcb    = executando;
//        executando = prox_pcb;
//
//        insere_fifo(&fifo_bloqs,ant_pcb);
//        swapcontext(&ant_pcb.contexto,&executando.contexto);
//    }

    executando.pid_wait = pid;

    insere_fifo(&fifo_bloqs,executando);
    swapcontext(&executando.contexto,&scheduler_context);

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

void scheduler()
{
    getcontext(&scheduler_context);
    printf("\npassou antes\n");
    if(pcb_fim()<0)
        return;
    //while(pcb_fim()>=0){
        //setcontext(&executando.contexto);
        //swapcontext(&scheduler_context,&executando.contexto);
        printf("\npassou depois\n");
     //   }
    setcontext(&executando.contexto);
}
