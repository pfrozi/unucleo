#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "unucleo.h"

void teste4();

void teste1()
{
    int i = 30;
    int p = mproc_create(2,(void*)teste4,0);

    for(;i>0;i--)
    {
        printf("Sou o teste 1 de prio 1 e vou executar mais %d vezes (chamei %d)\n",i,p);
    }
}
void teste2()
{
    int i = 25;
    for(;i>0;i--)
    {
        printf("Sou o teste 2 de prio 1 e vou executar mais %d vezes\n",i);
        mproc_join(4);
    }
}
void teste3()
{
    int i = 20;
    for(;i>0;i--)
    {
        printf("Sou o teste 3 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste4()
{
    int i = 15;
    for(;i>0;i--)
    {
        printf("Sou o teste 4 de prio 2 e vou executar mais %d vezes\n",i);
    }
}
void teste5()
{
    int i = 15;
    for(;i>0;i--)
    {
        printf("Sou o teste 5 de prio 2 e vou executar mais %d vezes\n",i);
    }
}

int main() {

    int init  = 0;
    int proc1 = 0;
    int proc2 = 0;
    int proc3 = 0;
    int proc4 = 0;

    init = libsisop_init();

    proc1 = mproc_create(1,(void*)teste1,0);
    proc2 = mproc_create(1,(void*)teste2,0);
    proc3 = mproc_create(1,(void*)teste3,0);

    printf("result INIT: %d\npid TESTE1: %d\npid TESTE2: %d TESTE3: %d TESTE4: %d\n\n",init,proc1,proc2,proc3,proc4);

    printf("\n\ninit : INICIEI!!\n");
    scheduler();
    return init;
}
