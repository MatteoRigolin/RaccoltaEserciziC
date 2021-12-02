/**
    @file   es1libro.c
    @author Matteo Rigolin
    @brief  esercizio 1 del libro
    @date   29/11/2021
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
* @fn       int main()
* @brief    funzione che crea un processo figlio e stampa a schermo i pid del processo prima del fork, del figlio e del padre   
*/

int main(){
    printf("\nIl processo corrente ha pid: %d", getpid());
    int pid;
    pid=fork();
    if(pid==0){
        printf("\nSolo il figlio, il mio pid è: %d", getpid());
        exit(0);
    }
    else{
        printf("\nSolo il padre, il mio pid è: %d", getpid());
        wait(&pid);
        exit(0);
        return 0;
    }
}