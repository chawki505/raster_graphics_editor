//
// Created by chawki on 15/02/19.
//

#include "parsing.h"
#include "../gestions/traitement_image/traitement_image.h"

extern void clear();

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
    return readline("\nGraphics editor> ");
}


void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
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

    } else if (strncmp(tmp, "rotation", 8) == 0) {
        rotation_image((int) strtol(tmp + 9, NULL, 10));

    } else if (strncmp(tmp, "save", 4) == 0) {

        save_image(atoi(tmp + 5));

    } else if (strncmp(tmp, "select", 6) == 0) {
        selectRegion(atoi(tmp + 7));

    } else if (strncmp(tmp, "drawzone", 8) == 0) {

        drawzone(atoi(tmp + 9));

    } else if (strncmp(tmp, "rotate", 6) == 0) {
        int r;
        printf("nb de rotation: ");
        scanf("%d", &r);
        while (r > 0) {
            rotation(atoi(tmp + 7));
            r = r - 1;
        }

    } else if (strncmp(tmp, "clear", 5) == 0) {
        clear();
    } else if (strncmp(tmp, "exit", 4) == 0) {
        SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
        exit(EXIT_SUCCESS);

    } else {
        fprintf(stderr, "\nCommande : %s inconnue ou incomplete\n", tmp);
    }


    free(tmp);


}