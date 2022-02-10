#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2)
    {
        printf("Errore negli argomenti");
        exit(1);
    }
    char stringhe[100];
    char ris[10];
    int piped[2], pid, totale;
    do
    {
        printf("\nInserisci una stringa: ");
        scanf("%s", str);
        pid = fork();
        if(pid == 0)
        {
            close(0);
            dup(piped[0]);
            close(piped[0]);
            close(1);
            dup(piped[1]);
            close(piped[1]);
            execl("/bin/grep", "grep ","-c", str, argv[1], (char *)0);
            exit(0);
        }
        read(piped[0], ris, sizeof(ris));
        printf("\nLa stringa %s e' presente : %d  volte nel fil", str, atoi(ris));
        totale += atoi(ris);
    } while(strcmp(str, "fine") != 0);
    close(piped[0]);
    close(piped[1]);
    printf("Il numero di stringhe trovate è: %d\n", totale);
    return 0;
}