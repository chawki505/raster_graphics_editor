//
// Created by chawki on 15/02/19.
//

#include "parsing.h"
#include "../gestions/traitement_image/traitement_image.h"
#include "../gestions/my_struct_images/my_struct_images.h"


char *argumentslist[TAILLE_LIST_ARGS];

extern void clear();

//methode pour creer un liste des arguments de la commande donner en entrer
void creation_liste_arguments(char *saisi_user) {
    int compteur = 0;
    int longueur = 0;
    char *separateur = " ";


    //init tab argument
    for (int i = 0; i < TAILLE_LIST_ARGS; ++i) {
        argumentslist[i] = NULL;
    }

    //renvoi le nombre de caractere avant le separateur espace
    longueur = strcspn(saisi_user, separateur);

    //copier le premier element comme etant la commande principale
    argumentslist[compteur] = strndup(saisi_user, longueur);

    //incrementé le compteur pour la suite
    saisi_user = saisi_user + longueur;

    compteur++;

    while (strlen(saisi_user) > 0) {
        if (saisi_user[0] == ' ') saisi_user++; //avancer si le premier caractere est un espace
        longueur = strcspn(saisi_user, separateur); //calculer la taille du mot avant le separateur
        argumentslist[compteur] = strndup(saisi_user, longueur); // decouper la chaine et la mettre dans le tab des args
        saisi_user = saisi_user + longueur; //avancer la chaine de saisi
        ++compteur;
    }
}

//vider la memoire des arguments
void liberation_arguments() {
    int compteur = 0;
    while (compteur < TAILLE_LIST_ARGS && argumentslist[compteur] != NULL) {
        free(argumentslist[compteur]);
        compteur++;
    }
}

//retourne le nombre d'argument dans le tab des arguments
int get_nb_args() {
    int compteur = 0;

    while (argumentslist[compteur] != NULL) {
        compteur++;
    }
    return compteur;
}

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
    return readline("Graphics editor> ");
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

    creation_liste_arguments(ligne_a_traiter);


    if (strncmp(argumentslist[0], "load", strlen("load")) == 0) {

        if (get_nb_args() == 2)
            load_image(argumentslist[1]);
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");


    } else if (strncmp(argumentslist[0], "delete", strlen("delete")) == 0) {

        if (get_nb_args() == 2)
            delete_image(strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "show", strlen("show")) == 0) {

        print_list_image();

    } else if (strncmp(argumentslist[0], "display", strlen("display")) == 0) {

        if (get_nb_args() == 2)
            display_image((int) strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "save", strlen("save")) == 0) {

        if (get_nb_args() == 2)
            save_image(strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "symv", 4) == 0) {

        if (get_nb_args() == 2)
            symv_image((int) strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "symh", 4) == 0) {

        if (get_nb_args() == 2)
            symh_image((int) strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
    } else if (strncmp(argumentslist[0], "select", strlen("select")) == 0) {

        if (get_nb_args() == 2)
            selectRegion(strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "drawzone", strlen("drawzone")) == 0) {

        if (get_nb_args() == 2)
            drawzone(strtol(argumentslist[1], NULL, 10));
        else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "rotate", strlen("rotate")) == 0) {

        if (get_nb_args() == 3) {
            int r = strtol(argumentslist[2], NULL, 10);
            while (r > 0) {
                rotation(strtol(argumentslist[1], NULL, 10));
                r = r - 1;
            }
        } else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");


    } else if (strncmp(argumentslist[0], "resize", strlen("resize")) == 0) {

        if (get_nb_args() == 4) {
            int id_image = strtol(argumentslist[1], NULL, 10);
            int w = strtol(argumentslist[2], NULL, 10);
            int h = strtol(argumentslist[3], NULL, 10);

            resize(id_image, w, h);
        } else
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");

    } else if (strncmp(argumentslist[0], "clear", strlen("clear")) == 0) {

        clear();

    } else if (strncmp(argumentslist[0], "exit", strlen("exit")) == 0) {

        SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
        liberation_arguments();
        exit(EXIT_SUCCESS);

    } else {


        fprintf(stderr, "Commande : %s inconnue\n", ligne_a_traiter);
    }

    liberation_arguments();
}