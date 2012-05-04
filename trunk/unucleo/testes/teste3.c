/******************************************************************************
 * teste3.c
 ******************************************************************************
 * OBJETIVO:
 * Verificar a execução correta dos processos de acordo com as prioridades
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria MAX_PROC_I processos com a mproc_create(), processos com PID ímpar 
 * recebem prioridade 1 (devem ser executados primeiro), processos com PID par
 * recebem prioridade 2 (devem ser executados depois
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "../include/unucleo.h"

#define MAX_PROC_I 130

void teste(void* pid) {
    printf("EXEC: teste(), PID %d\n", *((int*)pid));
}

int main() {
    printf("INICIO: main()\n");
    
    /****************
     * Inicializaão *
     ****************/
    printf("CALL: main() -> libsisop_init()");
    int init = libsisop_init();
    printf(" - RET: %d\n", init);
    /* Fim Inicialização */
    
    
    /*************************
     * Criação dos Processos *
     *************************/  
     
    int p[MAX_PROC_I];
    int i;
    int prioridade;
    
    for(i=0; i<MAX_PROC_I; i++) {
        prioridade = (i % 2) + 1;
        printf("CREATE: main() -> mproc_create(%d, (void*)teste, &p[%d])", prioridade, i);
        p[i] = mproc_create(prioridade, (void*)teste, &p[i]);
        printf(" - RET: %d\n", p[i]);
    }
    /* Fim Criação dos Processos */


    /**************************
     * Chamada do Escalonador *
     **************************/      
    printf("CALL: main() -> scheduler()\n");
    scheduler();
    /* Fim Chamada do Escalonador */
    
    printf("FIM: main()\n");
    return init;
}
