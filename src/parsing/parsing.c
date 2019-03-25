//
// Created by chawki on 15/02/19.
//

#include "../includes.h"
#include "parsing.h"
#include "../gestions/traitement_image/traitement_image.h"

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

    traitement_espaces_debut(ligne_a_traiter);
    traitement_espaces_fin(ligne_a_traiter);

    char *tmp = strdup(ligne_a_traiter);

    if (strncmp(tmp, "load", 4) == 0 && strlen(tmp) > 5) {

        load_image(tmp + 5);

    } else if (strncmp(tmp, "display", 7) == 0) {

        display_image((int) strtol(tmp + 8, NULL, 10));


    } else if (strncmp(tmp, "exit", 4) == 0) {
        SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
        exit(EXIT_SUCCESS);

    } else {
        fprintf(stderr, "Commande : %s inconnue ou incomplete\n", tmp);
    }


}