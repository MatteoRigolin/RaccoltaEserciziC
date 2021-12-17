#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

void generaNumeri(int numeri[10]){
    for(int i=0; i<10; i++){
        numeri[i]=rand();
    }
}

void sommaNumeri(int numeri[10]){
    for(int i=0; i<9; i++){
        numeri[i]+= numeri[i+1];
    }
}

int main(){
    int canale1[2];
    int canale2[2];
    pipe(canale1);
    pipe(canale2);
    int numeri[10];
    int pid = fork();
    if (pid>0){
        generaNumeri(numeri);
        close(canale1[0]);
        close(canale2[1]);
        write(canale1[1], numeri, sizeof(numeri));
        read(canale2[0], numero, sizeof(int));
    }
    else{
        sommaNumeri(numeri);
    }
}