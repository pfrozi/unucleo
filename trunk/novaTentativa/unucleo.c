#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "unucleo.h"
#include "fifo.h"


/* Estruturas que armazenam os processos nos diferentes estados */
PCB         executando;                                                         // Como só um processo usa o processador por vez, o estado executando é apenas um PCB
FIFO_DESC   fifo_aptos[PRIORIDADES];                                            // Os processos APTOS são separados em filas por prioridades
FIFO_DESC   fifo_bloqs;                                                         // Os processos bloqueados ficam numa lista

/* Variáveis globais que armazenam informções do unucleo */
ucontext_t scheduler_context;                                                   // Armazena o contexto do escalonador para retorno das funções
int        pidCount;                                                            // Número de processos ativos

 /* Funções reservadas do sistema operacional - INICIO */

 //Verifica se tinha algum processo esperando o processo que esta executando, retorna -1 se não houver ninguem
 int verifica_waiters()
 {
    int ret=-1;                                                                 // pid do waiter, retorna -1 se não existir
    if(fifo_bloqs.prim != NULL)
        ret = has_waiter(&fifo_bloqs,executando.pid);                           // verifica se possui alguem esperando pelo processo que esta no estado running
    return ret;
 }

 void troca_bloq_to_ready()
 {
    PCB pcb_bloq;
    int pid_bloq = verifica_waiters();
    while(pid_bloq>-1)
    {
        if(busca_pcb(&fifo_bloqs,pid_bloq,&pcb_bloq)!=-1){                      // armazena pcb que vai ser liberado na variavel

            remove_pcb(&fifo_bloqs,pid_bloq);                                   //exclui determinado PCB da lista de bloqueados
            pcb_bloq.estado = APTO;
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
    troca_bloq_to_ready();                                                                 // Processos que estavam esperando o processo em execução são liberados aqui

    if(pcb_caller(&pcb_ready)<0)
        return -1;

    executando = pcb_ready;
    return 0;
}

void ini_make(ucontext_t* contexto)
{

    contexto->uc_stack.ss_sp    = NULL;
	contexto->uc_stack.ss_size  = 0;
	contexto->uc_stack.ss_flags = 0;

}
 /* Funções reservadas do sistema operacional - FIM */

 /* Inicializa o unucleo.
   Retorna "0" se inicializou corretamente ou "-1" caso contrário. */
int libsisop_init()
{
    int i;
    pidCount = 1;

    cria_fifo(&fifo_bloqs);                                                          // Cria uma fila de bloqueados
    for(i = 0;i<PRIORIDADES-1;i++)                                                   // Cria uma fila para cada prioridade
        cria_fifo(&fifo_aptos[i]);

    ini_make(&scheduler_context);
	getcontext(&scheduler_context);

	scheduler_context.uc_stack.ss_sp    = (char*)malloc(SIGSTKSZ*sizeof(char));
	scheduler_context.uc_stack.ss_size  = SIGSTKSZ*sizeof(char);
    scheduler_context.uc_link = NULL;

	return 0;

}

/* Cria um novo processo de usuário com a prioridade "prio".
   A prioridade deve ser 1 ou 2 senão a função retorna erro.
   O código a ser executado é apontado por "start_routine".
   Retorna o PID (Process Identification) do processo ou "-1" em caso de erro. */
int mproc_create(int prio, void *(*start_routine)(void*), void *arg)
{
    PCB pcb_add;

    if (prio<1 || prio>2)
	{
 		printf("Sem permissão para inserir processos com prioridade de sistema (0). \n");
		return -1;
	}
	pcb_add.pid  = pidCount;
	pcb_add.prio = prio;
	pcb_add.pid_wait = -1;
	pcb_add.estado = APTO;
	pcb_add.contexto=(ucontext_t*)malloc(sizeof(ucontext_t));
    pidCount++;

    getcontext(pcb_add.contexto);


	ini_make(pcb_add.contexto);
	getcontext(pcb_add.contexto);

	pcb_add.contexto->uc_stack.ss_sp    = (char *)malloc(SIGSTKSZ*sizeof(char));
	pcb_add.contexto->uc_stack.ss_size  = SIGSTKSZ*sizeof(char);
    pcb_add.contexto->uc_link = &scheduler_context;

	makecontext(pcb_add.contexto, (void (*)(void)) start_routine, 1, arg);

    insere_fifo(&fifo_aptos[prio], pcb_add);

	return pcb_add.pid;
}

/* Aguarda até que o processo identificado por "pid" seja encerrado.
   Retorna "0" se funcionou corretamente ou "-1" caso contrário. */
int mproc_join(int pid)
{

    executando.pid_wait = pid;
    executando.estado = BLOQ;
    insere_fifo(&fifo_bloqs,executando);

    swapcontext(executando.contexto,&scheduler_context);
    return 0;
}

/* O processo retorna o controle ao escalonador (cedência voluntária)
   e vai para o final da fila de APTOS para executar. */
void mproc_yield(void)
{

        executando.estado = APTO;
        insere_fifo(&fifo_aptos[executando.prio], executando);
        swapcontext(executando.contexto,&scheduler_context);

}

void destroi_exec()
{
    free(executando.contexto->uc_stack.ss_sp);
    free(executando.contexto);
}
/* Inicia o esclonador de processos, deve ser chamado apenas na função
   main() após as chamadas de mproc_create() */
void scheduler()
{

    getcontext(&scheduler_context);
    while(pcb_fim()>=0){
        executando.estado = EXEC;
        swapcontext(&scheduler_context,executando.contexto);
        if (executando.estado == EXEC)
            destroi_exec();
//        printf("\nFila prio 1:\n");imprime_fifo(&fifo_aptos[1]);//debug
//        printf("\nFila prio 2:\n");imprime_fifo(&fifo_aptos[2]);//debug
//        printf("\nFila bloqs :\n");imprime_fifo(&fifo_bloqs);   //debug

        }
}

