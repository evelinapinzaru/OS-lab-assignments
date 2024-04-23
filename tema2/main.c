#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include"dependency.h"

int main(int argc, char *argv[]) {
    struct stat stare;

    // aici se verifica daca numarul de argumente transmise in linia de comanda corespunde conditiei
    if(argc != 3) {
        printf("Acest program trebuie rulat astfel : ./%s nume_director_sursa nume_director_destinatie\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // aici se verifica daca directorul sursa dat in linia de comanda este intr-adevar un director
    stat(argv[1], &stare);
    if(!S_ISDIR(stare.st_mode)) {
        perror("Primul argument nu este un director!");
        exit(EXIT_FAILURE);
    }

    // aici se verifica acelasi lucru, doar ca pentru directorul destinatie dat in linia de comanda
    stat(argv[2], &stare);
    if(!S_ISDIR(stare.st_mode)) {
        perror("Al doilea argument nu este un director!");
        exit(EXIT_FAILURE);
    }

    // apelarea functiei de parcurgere recursiva & procesare a directorului sursa
    parcurge_proceseaza(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
