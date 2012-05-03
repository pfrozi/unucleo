/******************************************************************************
 * teste7.c
 ******************************************************************************
 * OBJETIVO:
 * Verficar um deadlock com prioridades diferentes.
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria os processos p1, p2, p3.
 * p1 deve aguardar p2.
 * p2 deve aguardar p3.
 * p3 deve agaurdar p1 gerando o deadlock.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

#define MAX_PROC_I 1

void teste_join_p1(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 1;
    printf("PID %d - CALL: teste_join() -> mproc_join(%d)\n", *((int*)pid), wait);
    int ret = mproc_join(wait);
    printf("PID %d - RET: teste_join() -> mproc_join(%d) = %d\n", *((int*)pid), wait, ret);
    printf("PID %d - FIM: teste_join()\n", *((int*)pid));
}

void teste_join_p2(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 2;
    printf("PID %d - CALL: teste_join() -> mproc_join(%d)\n", *((int*)pid), wait);
    int ret = mproc_join(wait);
    printf("PID %d - RET: teste_join() -> mproc_join(%d) = %d\n", *((int*)pid), wait, ret);
    printf("PID %d - FIM: teste_join()\n", *((int*)pid));
}

void teste_join_p3(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 3;
    printf("PID %d - CALL: teste_join() -> mproc_join(%d)\n", *((int*)pid), wait);
    int ret = mproc_join(wait);
    printf("PID %d - RET: teste_join() -> mproc_join(%d) = %d\n", *((int*)pid), wait, ret);
    printf("PID %d - FIM: teste_join()\n", *((int*)pid));
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
     
    int p1, p2, p3;
    
    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p2, &p1)");
    p1 = mproc_create(1, (void*)teste_join_p2, &p1);
    printf(" - RET: %d\n", p1);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p3, &p2)");
    p2 = mproc_create(1, (void*)teste_join_p3, &p2);
    printf(" - RET: %d\n", p2);

    printf("CREATE: main() -> mproc_create(2, (void*)teste_join_p1, &p3)");
    p3 = mproc_create(2, (void*)teste_join_p1, &p3);
    printf(" - RET: %d\n", p3);
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
