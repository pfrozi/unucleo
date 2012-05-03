#include <stdio.h>
#include <stdlib.h>
#include "unucleo.h"

void teste4();

void teste1() {
    printf("INICIO: teste1()\n");

    int i = 30;

    printf("CALL: teste1() -> mproc_create(2,(void*)teste4,0)\n");
    int p4 = mproc_create(2,(void*)teste4,0);
    printf("RET: teste1() -> mproc_create(2,(void*)teste4,0) = %d\n", p4);

    for(;i>0;i--) {
        printf("Sou o teste 1 de prio 1 e vou executar mais %d vezes (chamei %d)\n", i, p4);
    }

    printf("FIM: teste1()\n");
}

void teste2() {
    printf("INICIO: teste2()\n");

    int i = 25;

    for(;i>0;i--) {
        printf("Sou o teste 2 de prio 1 e vou executar mais %d vezes\n",i);
        printf("CALL: teste2() -> mproc_join(4)\n");
        mproc_join(4);
    }

    printf("FIM: teste2()\n");
}

void teste3() {
    printf("INICIO: teste3()\n");

    int i = 20;

    for(;i>0;i--) {
        printf("Sou o teste 3 de prio 1 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste3()\n");
}

void teste4() {
    printf("INICIO: teste4()\n");

    int i = 15;

    for(;i>0;i--) {
        printf("Sou o teste 4 de prio 2 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste4()\n");
}

void teste5() {
    printf("INICIO: teste5()\n");

    int i = 15;

    for(;i>0;i--) {
        printf("Sou o teste 5 de prio 2 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste5()\n");
}

int main() {
    printf("INICIO: main()\n");
    
    /****************
     * Inicializaão *
     ****************/
    printf("CALL: main() -> libsisop_init()\n");
    int init = libsisop_init();
    printf("RET: main() -> libsisop_init() = %d\n", init);
    /* Fim Inicialização */
    
    
    /*************************
     * Criação dos Processos *
     *************************/  
    printf("CALL: main() -> mproc_create(1,(void*)teste1,0)\n");
    int p1 = mproc_create(1,(void*)teste1,0);
    printf("RET: main() -> mproc_create(1,(void*)teste1,0) = %d\n", p1);

    printf("CALL: main() -> mproc_create(1,(void*)teste2,0)\n");
    int p2 = mproc_create(1,(void*)teste2,0);
    printf("RET: main() -> mproc_create(1,(void*)teste2,0) = %d\n", p2);

    printf("CALL: main() -> mproc_create(1,(void*)teste3,0)\n");
    int p3 = mproc_create(1,(void*)teste3,0);
    printf("RET: main() -> mproc_create(1,(void*)teste3,0) = %d\n", p3);
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