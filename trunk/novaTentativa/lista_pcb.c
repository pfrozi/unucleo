#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc


#include "lista_pcb.h"

PCB* cria_lista(void)
{
       return NULL;
}

PCB* insere (PCB *l, int pid, int status, int prio, ucontext_t context)
{
       PCB *novo;                   //novo elemento
       PCB *ant = NULL;             //ponteiro auxiliar para a posição anterior
       PCB *ptaux = l;              //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (PCB*) malloc(sizeof(PCB));
       
       /*insere a informação no novo nodo*/
       novo->info       = dados;
       novo->status     = status;
       novo->prio       = prio;
       novo->pid_wait   = -1;
       novo->context    = context;
       
       /*procurando a posição de inserção*/
       while (ptaux!=NULL) 
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }
       
       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
             //  puts("inserindo primeiro");
               novo->prox = l;
               l = novo;
       }
       else /*elemento inserido no meio da lista*/
       {
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return l;
}
void imprime(PCB* l)
{  
     PCB* ptaux;
     if (l == NULL)
        puts("\tlista vazia!\n");
     else
     for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
         printf("\tPID: %d | Status: %d | Prio: %d | Aguarda pid: %d\n",ptaux->pid,ptaux->status,ptaux->prio,ptaux->pid_wait);
}         

PCB* remove(PCB* l, int pid)
{
     PCB *ant = NULL; //ponteiro auxiliar para a posição anterior
     PCB *ptaux = l; //ponteiro auxiliar para percorrer a lista

     /*procura o elemento na lista*/
     while (ptaux !=NULL && (ptaux->pid != pid))
     {          
          ant = ptaux;
          ptaux = ptaux->prox;
     }
     
     /*verifica se achou*/
     if (ptaux == NULL)
       return l; /*retorna a lista original*/
       
    if (ant == NULL) /*vai remover o primeiro elemento*/
      l = ptaux->prox;
    else /*vai remover do meio ou do final*/
      ant->prox = ptaux->prox;
      
    free(ptaux); /*libera a memória alocada*/
    
    return l;
}  
 
PCB* destroi(PCB* l)
{
   PCB *ptaux;          //ponteiro auxiliar para percorrer a lista
   while (l != NULL)
   {
         ptaux = l;
         l = l->prox;
         free(ptaux);
   }
   free(l);   
   return NULL;            
}   


