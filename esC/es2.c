#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main(int argc, char*argv[]){
    if(argc!=2){
        printf("Argomenti errati\n");
        exit(1);
    }
    int p1p2[2], p2p0[2], pid, fd, nread;
    char buffer[1024];
    pipe(p1p2);
    pid=fork();
    if(pid==0){
        close(p1p2[0]);
        close(1);
        dup(p1p2[1]);
        close(p1p2[1]);
        execl("/usr/bin/cat", "cat", argv[1], (char*)0);
        return -1;
    }
    pipe(p2p0);
    pid=fork();
    if(pid==0){
        close(p1p2[1]);
        close(0);
        dup(p1p2[0]);
        close(p1p2[0]);

        close(p2p0[0]);
        close(1);
        dup(p2p0[1]);
        close(p2p0[1]);

        execl("/usr/bin/wc", "wc", (char*)0);
        return -1;
    }
    close(p1p2[0]);
    close(p1p2[1]);
    close(p2p0[0]);
    fd=open("wc.txt", O_WRONLY | O_CREAT, 0777);
    while(nread=read("wc.txt", buffer, sizeof(buffer))>0){
        write(fd, buffer, nread);
    }
    close(p2p0[0]);
    close(fd);
    return 0;
}
