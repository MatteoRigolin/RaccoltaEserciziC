#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct 
{
    char nome[20];
    char cognome[20];
    char ruolo[20];
} Giocatore_T;

int main (int argc, char *argv[]){
    FILE *stream;
    int pid;
    Giocatore_T squadra[11];
    if(argc != 2)
    {
        printf("Errore negli argomenti");
        exit(0);
    }
    stream = fopen(argv[1], "r");
    if (stream == NULL)
    {
        printf("File non trovato");
        exit(1);
    }
    int num;
    for(num = 0; !feof(stream); num++)
    {       
        fscanf(stream, "%s %s %s", squadra[num].nome, squadra[num].cognome, squadra[num].ruolo);
    }
    num--;
    fclose(stream);
    pid = fork();
    if(pid==0)
    {
        for(int i = 0; i < num; i++)
        {
            if(strcmp(squadra[i].ruolo, "attaccante")==0)
            {
                printf("%s %s %s", squadra[i].nome, squadra[i].cognome, squadra[i].ruolo);
            }
        }
        exit(2);
    }
    else
    {
        wait(&pid);
    }
    return 0;
}