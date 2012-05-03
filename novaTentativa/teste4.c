/******************************************************************************
 * teste4.c
 ******************************************************************************
 * OBJETIVO:
 * Verificar se os processos não estão sendo criados com prioridades indevidas
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria 1 processo com prioridade < 1 e outro processo com prioridade > 2.
 * Deve retornar erro.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

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
     
    int p1, p2;
    
    printf("CREATE: main() -> mproc_create(0, (void*)teste, &p1)");
    p1 = mproc_create(0, (void*)teste, &p1);
    printf(" - RET: %d\n", p1);
    
    printf("CREATE: main() -> mproc_create(5, (void*)teste, &p2)");
    p2 = mproc_create(5, (void*)teste, &p2);
    printf(" - RET: %d\n", p2);
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
