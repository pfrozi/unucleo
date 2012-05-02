#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "unucleo.h"

void teste1() {
    int i = 30;
    for(;i>0;i--) {
        printf("Sou o teste 1 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste2() {
    int i = 25;
    for(;i>0;i--) {
        printf("Sou o teste 2 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste3() {
    int i = 20;
    for(;i>0;i--) {
        printf("Sou o teste 3 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste4() {
    int i = 15;
    for(;i>0;i--) {
        printf("Sou o teste 4 de prio 2 e vou executar mais %d vezes\n",i);
    }
}
void teste5() {
    int i = 15;
    for(;i>0;i--) {
        printf("Sou o teste 5 de prio 2 e vou executar mais %d vezes\n",i);
    }
}

int main(int argc, char* argv[]) {

    int init = 0;
    int proc1 = 0;
    int proc2 = 0;

    init = libsisop_init();
    proc1 = mproc_create(1,(void*)teste2,0);
    //proc2 = mproc_create(1, teste3,0);

    printf("pid INIT: %d\npid TESTE2: %d\npid TESTE3: %d\n\n",init,proc1,proc2);

    mproc_join(proc1);
    //mproc_join(proc2);

    printf("\n\ninit : RETORNEI!!");
    //teste1();
    return init;
}
