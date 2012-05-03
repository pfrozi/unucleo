/******************************************************************************
 * teste6.c
 ******************************************************************************
 * OBJETIVO:
 * Verficar o bloqueio de vários processos aguardando a execução de um.
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria os processos p1, p2, p3, p4, p5, p6, p7.
 * p1, p2, p3, p4 deve aguardar p5.
 * p6 deve aguardar p1 (já executou).
 * p7 deve agaurdar um processo inexistente.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

#define MAX_PROC_I 1

void teste(void* pid) {
    printf("PID %d - EXEC: teste()\n", *((int*)pid));
    printf("PID %d - FIM: teste()\n", *((int*)pid));
}

void teste_join_p5(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 5;
    printf("PID %d - CALL: teste_join() -> mproc_join(%d)\n", *((int*)pid), wait);
    int ret = mproc_join(wait);
    printf("PID %d - RET: teste_join() -> mproc_join(%d) = %d\n", *((int*)pid), wait, ret);
    printf("PID %d - FIM: teste_join()\n", *((int*)pid));
}

void teste_join_p1(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 1;
    printf("PID %d - CALL: teste_join() -> mproc_join(%d)\n", *((int*)pid), wait);
    int ret = mproc_join(wait);
    printf("PID %d - RET: teste_join() -> mproc_join(%d) = %d\n", *((int*)pid), wait, ret);
    printf("PID %d - FIM: teste_join()\n", *((int*)pid));
}

void teste_join_inexistente(void* pid) {
    printf("PID %d - EXEC: teste_join()\n", *((int*)pid));
    int wait = 100;
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
     
    int p1, p2, p3, p4, p5, p6, p7;
    
    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p5, &p1)");
    p1 = mproc_create(1, (void*)teste_join_p5, &p1);
    printf(" - RET: %d\n", p1);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p5, &p2)");
    p2 = mproc_create(1, (void*)teste_join_p5, &p2);
    printf(" - RET: %d\n", p2);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p5, &p3)");
    p3 = mproc_create(1, (void*)teste_join_p5, &p3);
    printf(" - RET: %d\n", p3);

    printf("CREATE: main() -> mproc_create(1, (void*)teste_join_p5, &p4)");
    p4 = mproc_create(1, (void*)teste_join_p5, &p4);
    printf(" - RET: %d\n", p4);

    printf("CREATE: main() -> mproc_create(2, (void*)teste, &p5)");
    p5 = mproc_create(2, (void*)teste, &p5);
    printf(" - RET: %d\n", p5);

    printf("CREATE: main() -> mproc_create(2, (void*)teste_join_p1, &p6)");
    p6 = mproc_create(2, (void*)teste_join_p1, &p6);
    printf(" - RET: %d\n", p6);

    printf("CREATE: main() -> mproc_create(2, (void*)teste_join_inexistente, &p7)");
    p7 = mproc_create(2, (void*)teste_join_inexistente, &p7);
    printf(" - RET: %d\n", p7);
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
