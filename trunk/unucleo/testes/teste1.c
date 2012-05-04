/******************************************************************************
 * teste1.c
 ******************************************************************************
 * OBJETIVO:
 * Verificar a execução de múltiplos processos diferentes 
 ******************************************************************************
 * FUNCIONAMENTO:
 * Cria os processos p1, p2, p3.
 * p1 cria p4
 * p2 aguarda p4
 * 
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "../include/unucleo.h"

void teste4(void *arg);

void teste1(void *arg) {
    printf("INICIO: teste1()\n");

    int i = 30;

    printf("CALL: teste1() -> mproc_create(2,(void*)teste4,0)\n");
    int p4 = mproc_create(2,(void*)teste4,NULL);
    printf("RET: teste1() -> mproc_create(2,(void*)teste4,0) = %d\n", p4);

    for(;i>0;i--) {
        printf("Sou o teste 1 de prio 1 e vou executar mais %d vezes (chamei %d)\n", i, p4);
    }

    printf("FIM: teste1()\n");
}

void teste2(void *arg) {
    printf("INICIO: teste2()\n");

    int i = 25;

    for(;i>0;i--) {
        printf("Sou o teste 2 de prio 1 e vou executar mais %d vezes\n",i);
        if(i==15){
            printf("CALL: teste2() -> mproc_join(4)\n");
            mproc_join(4);
        }
    }

    printf("FIM: teste2()\n");
}

void teste3(void *arg) {
    printf("INICIO: teste3()\n");

    int i = 20;

    for(;i>0;i--) {
        printf("Sou o teste 3 de prio 1 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste3()\n");
}

void teste4(void *arg) {
    printf("INICIO: teste4()\n");

    int i = 15;

    for(;i>0;i--) {
        printf("Sou o teste 4 de prio 2 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste4()\n");
}

void teste5(void *arg) {
    printf("INICIO: teste5()\n");

    int i = 15;

    for(;i>0;i--) {
        printf("Sou o teste 5 de prio 2 e vou executar mais %d vezes\n",i);
    }

    printf("FIM: teste5()\n");
}

int main() {
    printf("INICIO: main()\n");
    
    printf("CALL: main() -> libsisop_init()\n");
    int init = libsisop_init();
    printf("RET: main() -> libsisop_init() = %d\n", init);

    printf("CALL: main() -> mproc_create(1,(void*)teste1,0)\n");
    int p1 = mproc_create(1,(void*)teste1,NULL);
    printf("RET: main() -> mproc_create(1,(void*)teste1,0) = %d\n", p1);

    printf("CALL: main() -> mproc_create(1,(void*)teste2,0)\n");
    int p2 = mproc_create(1,(void*)teste2,NULL);
    printf("RET: main() -> mproc_create(1,(void*)teste2,0) = %d\n", p2);

    printf("CALL: main() -> mproc_create(1,(void*)teste3,0)\n");
    int p3 = mproc_create(1,(void*)teste3,NULL);
    printf("RET: main() -> mproc_create(1,(void*)teste3,0) = %d\n", p3);

    printf("CALL: main() -> scheduler()\n");
    scheduler();
    
    printf("FIM: main()\n");
    return init;
}