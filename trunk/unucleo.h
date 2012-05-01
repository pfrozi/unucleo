
#define APTO 0
#define EXEC 1
#define BLOQ 2

/* A prioridade P_ALTA é reservada às funções do unucleo.
   O usuário só pode criar processos com as prioridades
   P_MEDIA e P_BAIXA */
#define PRIORIDADES 3
#define P_ALTA 0
#define P_MEDIA 1
#define P_BAIXA 2

/* Inicializa o unucleo.
   Retorna "0" se inicializou corretamente ou "-1" caso contrário. */
int libsisop_init();

/* Cria um novo processo de usuário com a prioridade "prio".
   A prioridade deve ser 1 ou 2 senão a função retorna erro.
   O código a ser executado é apontado por "start_routine".
   Retorna o PID (Process Identification) do processo ou "-1" em caso de erro. */
int mproc_create(int prio, void *(*start_routine)(void*), void *arg);

/* O processo retorna o controle ao escalonador (cedência voluntária)
   e vai para o final da fila de APTOS para executar. */
void mproc_yield(void);

/* Aguarda até que o processo identificado por "pid" seja encerrado.
   Retorna "0" se funcionou corretamente ou "-1" caso contrário. */
int mproc_join(int pid);

/* Encerra o processo chamado e sinaliza o encerramento para um
   evento join. */
void procExit(int status);
