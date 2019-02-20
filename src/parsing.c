//
// Created by chawki on 15/02/19.
//

#include "includes.h"
#include "parsing.h"

/*supprime les espaces dans le debut de la chaine si existe*/
void traitement_espaces_debut(char *chaine_a_traiter) {
    char *nouvelle_chaine = chaine_a_traiter;
    while (nouvelle_chaine[0] == ' ') {
        ++nouvelle_chaine;
    }
    memmove(chaine_a_traiter, nouvelle_chaine, strlen(nouvelle_chaine) + 1);
}

/*supprime les espaces dans la fin de la chaine si existe*/
void traitement_espaces_fin(char *chaine_a_traiter) {
    while (chaine_a_traiter[strlen(chaine_a_traiter) - 1] == ' ') {
        chaine_a_traiter[strlen(chaine_a_traiter) - 1] = '\0';
    }
}


/* lecture des ligne saisi */
char *lecture_commande() {
    char *tmp = NULL;

    tmp = readline("Graphics editor> ");

    return tmp;
}


/* traite la ligne saisi par l'utilisateur */
void traitement_ligne(char *ligne_a_traiter) {


}