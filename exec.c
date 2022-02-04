#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    int fd[2];
    pipe(fd);
    int pid1 = fork();
    if (pid1 == 0) //figlio 1
    {
        printf("Il primo figlio ha PID: %d\n", getpid());
        close(1);
        dup(fd[1]);
        close(fd[1]);
        close(fd[0]);
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
            dup(fd[0]);
            close(fd[0]);
            close(fd[1]);
            execl("/bin/wc", "wc -l", NULL);
            exit(0);
        }
        else if (pid2 > 0)
        {
            printf("Il padre ha PID: %d\n", getpid());
            wait(&status);
            close(fd[0]);
            close(fd[1]);
            printf("I figli hanno terminato");
        }
    }
    return 0;
}