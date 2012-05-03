/******************************************************************************
 * teste5.c
 ******************************************************************************
 * OBJETIVO:
 * Verficar o bloqueio de processos e a cedencia voluntária
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria os processos p1, p2, p3, p4, p5.
 * p1 executa normalmente.
 * p2 deve aguardar p3 que deve aguardar p4.
 * p4 e p5 fazem uma cedencia voluntária
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

#define MAX_PROC_I 1

void teste(void* pid) {
    printf("PID %d - EXEC: teste()\n", *((int*)pid));
    printf("PID %d - FIM: teste()\n", *((int*)pid));
}

void teste_yield(void* pid) {
    printf("PID %d - EXEC: teste_yield()\n", *((int*)pid));
    printf("PID %d - CALL: teste_yield() -> mproc_yield()\n", *((int*)pid));
    mproc_yield();
    printf("PID %d - RET: teste_yield() -> mproc_yield()\n", *((int*)pid));
    printf("PID %d - FIM: teste_yield()\n", *((int*)pid));
}

void teste_join(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = *((int*)pid) + 1;
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
     
    int p1, p2, p3, p4, p5;
    
    printf("CREATE: main() -> mproc_create(1, (void*)teste, &p1)");
    p1 = mproc_create(1, (void*)teste, &p1);
    printf(" - RET: %d\n", p1);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join, &p2)");
    p2 = mproc_create(1, (void*)teste_join, &p2);
    printf(" - RET: %d\n", p2);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join, &p3)");
    p3 = mproc_create(1, (void*)teste_join, &p3);
    printf(" - RET: %d\n", p3);

    printf("CREATE: main() -> mproc_create(2, (void*)teste_yield, &p4)");
    p4 = mproc_create(2, (void*)teste_yield, &p4);
    printf(" - RET: %d\n", p4);

    printf("CREATE: main() -> mproc_create(2, (void*)teste_yield, &p5)");
    p5 = mproc_create(1, (void*)teste_yield, &p5);
    printf(" - RET: %d\n", p5);
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
