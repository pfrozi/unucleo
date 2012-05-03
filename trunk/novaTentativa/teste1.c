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
        if (i==15)
        {
            printf("\n  fiz join!  \n");
            mproc_join(3);
        }
    }

}
void teste2()
{
    int i = 25;
    for(;i>0;i--)
    {
        printf("Sou o teste 2 de prio 1 e vou executar mais %d vezes\n",i);
        if (i==5)
        {
            printf("\n  fiz Yield!  \n");
            mproc_yield();

        }
    }
}
void teste5();
void teste3()
{
    int i = 20;
    int p = mproc_create(2,(void*)teste5,0);
    for(;i>0;i--)
    {
        printf("Sou o teste 3 de prio 1 e vou executar mais %d vezes (chamei %d)\n",i,p);
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
void teste6()
{
    int i = 15;
    for(;i>0;i--)
    {
        printf("Sou o teste 6 de prio 2 e vou executar mais %d vezes\n",i);
    }
}
void teste5()
{
    int i = 15;
    int p = mproc_create(1,(void*)teste6,0);
    for(;i>0;i--)
    {
        printf("Sou o teste 5 de prio 2 e vou executar mais %d vezes(chamei %d)\n",i,p);
    }
}
void teste7()
{
    int i = 9;
    for(;i>0;i--)
    {
        printf("Sou o teste 7 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste8()
{
    int i = 8;
    for(;i>0;i--)
    {
        printf("Sou o teste 8 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste9()
{
    int i = 7;
    for(;i>0;i--)
    {
        printf("Sou o teste 9 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
void teste10()
{
    int i = 6;
    for(;i>0;i--)
    {
        printf("Sou o teste 10 de prio 1 e vou executar mais %d vezes\n",i);
    }
}
int main() {

    int init  = 0;
    int proc1,proc2,proc3,proc7,proc8,proc9,proc10;

    init = libsisop_init();

    proc1 = mproc_create(1,(void*)teste1,0);
    proc2 = mproc_create(1,(void*)teste2,0);
    proc3 = mproc_create(1,(void*)teste3,0);
    proc7 = mproc_create(1,(void*)teste7,0);
    proc8 = mproc_create(1,(void*)teste8,0);
    proc9 = mproc_create(1,(void*)teste9,0);
    proc10 = mproc_create(1,(void*)teste10,0);


    printf("%d %d %d %d %d %d %d %d\n\n",init,proc1,proc2,proc3,proc7,proc8,proc9,proc10);

    printf("\n\ninit : INICIEI!!\n");
    scheduler();
    return init;
}
