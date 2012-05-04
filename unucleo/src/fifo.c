#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc
//#include <ucontext.h>
#include "../include/fifo.h"

/*
    FUNÇÕES DE CONTROLE DA FIFO - INICIO
*/

void cria_fifo(FIFO_DESC* f) {
    f->prim = NULL;
    f->ult = NULL;
}

int insere_fifo(FIFO_DESC* f, PCB p) {
    FIFO_PCB* novo;
    if (f != NULL) { //testa se o descritor foi alocado
        novo = (FIFO_PCB*) malloc (sizeof(FIFO_PCB));
        novo->pcb = p;
        novo->prox = NULL;
        if (f->prim == NULL) // fila vazia, nodo será o primeiro da fila
            f->prim = novo;
        else
            f->ult->prox = novo; // fila não vazia, insere novo nodo no final
        f->ult = novo;
        return 1;
    }
    else
        return 0;
}

FIFO_PCB* consulta_fifo(FIFO_DESC* f) {
    if (f->prim == NULL)
        return NULL;
    else
        return f->prim;
}

int remove_fifo(FIFO_DESC* f) {
    FIFO_PCB* ptaux;
    if (f != NULL) //testa se o descritor foi alocado
        if (f->prim != NULL) // testa se tem algum elemento na fila
        {
            ptaux = f->prim;
            f->prim = f->prim->prox;
            free(ptaux);
            if (f->prim == NULL) //testa se a fila ficou vazia
                f->ult = NULL;
            return 1;
        }
        else return 0;
    else return 0;
}

void destroi_fifo(FIFO_DESC* f) {
    FIFO_PCB* ptaux;
    if (f != NULL) {
        while (f->prim != NULL) {
            ptaux = f->prim; //guarda o endereço do primeiro
            f->prim = f->prim->prox; //o próximo passa a ser o primeiro
            free(ptaux); //libera o que estava no inicio
        }
    }
}

/*
    FUNÇÕES DE CONTROLE DA FIFO - DEBUG
*/

void imprime_pcb(PCB p) {
    printf("PCB = { PID = %d, PRIO = %d, ESTADO = %d }\n", p.pid, p.prio, p.estado);
}

void imprime_fifo(FIFO_DESC *f) {
    int i = 0;
    FIFO_PCB* Atual;

    Atual = f->prim;
    if(Atual == NULL) {
        printf("Fila Vazia!\n");
    } else {
        printf("Início da Fila\n");
        do {
            i++;
            printf("Elemento: %d - ", i);
            imprime_pcb(Atual->pcb);
            Atual = Atual->prox;
        } while(Atual != NULL);
        printf("Fim da Fila\n");
    }
}

/*
    FUNÇÕES DE CONTROLE DA FIFO - FIM
*/


/*
    FUNCOES ADICIONAIS - INICIO
*/

int has_waiter(FIFO_DESC* f,int pid)
{
    FIFO_PCB* Atual = f->prim;

    if(Atual != NULL) {
        do {
            if(Atual->pcb.pid_wait==pid)
                return Atual->pcb.pid;
            Atual = Atual->prox;
        }while(Atual != NULL);
    }
    return -1;
}


int busca_pcb(FIFO_DESC* f, int pid, PCB* result)
{

    FIFO_PCB* Atual = f->prim;
    int ret = -1;

    if(Atual != NULL) {
        do {
            if(Atual->pcb.pid==pid)
            {
                *result = Atual->pcb;
                ret = Atual->pcb.pid;
                return ret;
            }
            Atual = Atual->prox;
        }while(Atual != NULL);
    }
    return -1;

}
int existe_pcb(FIFO_DESC* f, int pid)
{
    FIFO_PCB* Atual = f->prim;

    if(Atual != NULL) {
        do {
            if(Atual->pcb.pid==pid)
                return pid;
            Atual = Atual->prox;
        }while(Atual != NULL);
    }
    return -1;
}

int remove_pcb(FIFO_DESC* f, int pid)
{
    FIFO_PCB* aux   = NULL;
    FIFO_PCB* Atual = f->prim;

    if(Atual != NULL) {
        do {
            if(Atual->pcb.pid==pid)
            {
                if(aux==NULL)
                    f->prim = Atual->prox;
                else
                {
                    aux->prox = Atual->prox;
                    if(aux->prox==NULL)
                        f->ult = aux;
                }
                free(Atual);
                return 0;
            }
            aux   = Atual;
            Atual = Atual->prox;
        }while(Atual != NULL);
    }
    return -1;
}

/*
    FUNCOES ADICIONAIS - FIM
*/
