#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    int p1p2[2];
    int p2p0[2];
    pipe(p1p2);
    pipe(p2p0);
    int pid1 = fork();
    if (pid1 == 0) //figlio 1
    {
        printf("Il primo figlio ha PID: %d\n", getpid());
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        close(p1p2[0]);
        execl("/bin/cat", "cat", "file.txt", NULL);
        exit(0);
    }
    else if (pid1 > 0)
    {
        int pid2 = fork();
        if (pid2 == 0) //figlio 2
        {
            printf("Il secondo figlio ha PID: %d\n", getpid());
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);
            close(p1p2[1]);
            execl("/bin/wc", "wc -l", NULL);           
            exit(0);
        }
        else if (pid2 > 0)
        {
            printf("Il padre ha PID: %d\n", getpid());
            wait(&status);
            close(p1p2[0]);
            close(p1p2[1]);
            printf("I figli hanno terminato");
        }
    }
    return 0;
}