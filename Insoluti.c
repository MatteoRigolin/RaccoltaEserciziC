#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
    { 
        printf("Errore negli argomenti\n");
        exit(0);
    }
    char ris[1000];
    char controllo[1000];
    char codice[10];
    int p1, p2;
    int p1p0[2];
    int p2p0[2];
    int tot = 0;

    while(1)
    {
        printf("Inserisci il codice del cliente da cercare, oppure digita 'esci' per uscire dal programma\n");
        scanf("%s", codice); 
        if(strcmp(codice, "esci")== 0)  
        {
            printf("Il cliente cercato ha: %d insoluti\n", tot);
            exit(1);
        }
        if (strcasecmp(codice, "esci") != 0)
        {
            p1 = fork();
            if (p1 == 0)
            {
                close(p1p0[0]);
                close(1);
                dup(p1p0[1]);
                close(p1p0[1]);
                execl("/bin/grep", "grep", "-c", codice, argv[1], NULL); 
            }
            if(p1 > 0)
            {
                wait(&p1);
                read(p1p0[0], ris, sizeof(ris));
                if (atoi(ris) == 0)
                {
                    printf("Il codice non è stato trovato\n");
                }
                else
                {
                    printf("Il codice è stato trovato %d volte\n", atoi(ris));
                    p2 = fork();
                    if (p2 == 0)
                    {
                        close(1);
                        dup(p2p0[1]);
                        close(p2p0[0]);
                        close(p2p0[1]);
                        execl("/bin/grep", "grep", "-c", strcat(codice, " insoluto"), argv[1], NULL);
                    }
                    if (p2 > 0)
                    { 
                        wait(&p2);
                        read(p2p0[0], str, sizeof(str));
                        printf("Il cliente ha %d insoluti\n", atoi(str));
                        tot += atoi(str);
                    }
                }                                                               
            }
        }     
    } 
    close(p1p0[0]);
    close(p1p0[1]);
    close(p2p0[1]);
    close(p2p0[0]);
    return 0;
}