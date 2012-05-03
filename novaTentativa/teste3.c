#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

#define MAX_PROC_I 130

void teste(void* arg) {
    printf("EXEC: teste(), PID %d\n", (int*)arg);
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
        printf("CREATE: main() -> mproc_create(%d, (void*)teste, (void*)&i)", prioridade);
        p[i] = mproc_create(prioridade, (void*)teste, &i);
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
