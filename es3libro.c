/**
    @file   es3libro.c
    @author Matteo Rigolin
    @brief  esercizio 3 del libro
    @date   29/11/2021
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
* @fn       int main()
* @brief    funzione che crea tre processi figli, ognuno stampa a schermo una frase in sequenza, il padre attende la terminazione dell'ultimo figlio per poi terminare
*/

int main(){
    int pid1, pid2, pid3, status;
    pid1=fork();
    if(pid1==0){
        printf("Ciao, io sono Qui\n");
        exit(0);
    }
    else{
        pid2=fork();
        if(pid2==0){
            printf("Ciao, io sono Quo\n");
            exit(1);
        }
        else{
            pid3=fork();
            if(pid3==0){
                printf("Ciao, io sono Qua\n");
                exit(2);    
            }   
            else{
                waitpid(pid3, &status, 0);
                return 0;
            }
        }
    }
}