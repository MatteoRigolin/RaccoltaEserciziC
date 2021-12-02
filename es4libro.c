/**
    @file   es4libro.c
    @author Matteo Rigolin
    @brief  esercizio 4 del libro
    @date   29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

/**
* @brief    struct Persona_T: struct che rappresenta una persona con un nome e un cognome
* @param    char nome[20]: nome della persona
* @param    char cognome[20]: cognome della persona
*/

typedef struct{
    char nome[20];
    char cognome[20];
} Persona_T;

/**
* @fn       int main()
* @brief    funzione che crea un processo figlio, il padre legge il nome e il cognome della persona che si vuole aggiungere al file di testo, poi converte le stringhe inserite dall'utente lasciando l'iniziale maiuscola e il resto minuscolo, la nuova persona viene poi aggiunta al file e il figlio stampa schermo il suo nome e cognome
*/

int main(int argc, char *argv[]){
    FILE* stream;
    int pid;
    Persona_T persona;
    if(argc!=2){
        printf("Errore negli argomenti");
        exit(0);
    }
    stream=fopen("input.txt", "w");
    if(stream==NULL){
        printf("Il file non è stato trovato");
        exit(1);
    }
    pid=fork();
    if(pid==0){
        sleep(5);
        char *stringa;
        fscanf(stream, "%s", stringa);
        printf("%s", stringa);
        exit(2);
    }
    else{
        printf("Inserisci il nome della persona: ");
        scanf("%s", persona.nome);
        printf("Inserisci il cognome della persona: ");
        scanf("%s", persona.cognome);
        persona.nome[0]=toupper(persona.nome[0]);
        persona.cognome[0]=toupper(persona.cognome[0]);
        for(int i=1; i< strlen(persona.nome); i++){
          persona.nome[i]=tolower(persona.nome[i]);
        }
        for(int i=1; i< strlen(persona.cognome); i++){
          persona.cognome[i]=tolower(persona.cognome[i]);
        }
        fprintf(stream, "%s %s", persona.nome, persona.cognome);
        fclose(stream);
        remove(argv[1]);
        wait(&pid);      
    }
    return 0;
}