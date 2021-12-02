/**
    @file   es2libro.c
    @author Matteo Rigolin
    @brief  esercizio 2 del libro
    @date   29/11/2021
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
* @fn       int main()
* @brief    funzione che fa inserire all'utente un numero e crea un processo figlio, al numero viene aggiunto 15 nel figlio, nel padre invece si aggiunge 10, alla fine vengono stampati a schermo i due numeri diversi
*/

int main(){
    int pid;
    float num;
    printf("Inserisci un numero: \n");
    scanf("%f", &num);
    pid = fork();
    if (pid == 0)
    {
        num = num + 15;
        printf("Il numero ottenuto sommando 15 è: %f", num);
        exit(0);
    }
    else
    {
        wait(&pid);
        num = num + 10;
        printf("Il numero ottenuto sommando 10 è: %f", num);
        return 0;
    }
}