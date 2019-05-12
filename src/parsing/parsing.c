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
int traitement_ligne(char *ligne_a_traiter) {
    traitement_espaces_debut(ligne_a_traiter);
    traitement_espaces_fin(ligne_a_traiter);

    creation_liste_arguments(ligne_a_traiter);

    if (strncmp(argumentslist[0], "load", strlen("load")) == 0) {
        if (get_nb_args() == 2)
            load_image(argumentslist[1]);
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "delete", strlen("delete")) == 0) {
        if (get_nb_args() == 2)
            delete_image(strtol(argumentslist[1], NULL, 10));
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "show", strlen("show")) == 0) {
        print_list_image();

    } else if (strncmp(argumentslist[0], "display", strlen("display")) == 0) {
        if (get_nb_args() >= 2) {
            if (get_nb_args() - 1 >= TAILLE_LIST_ARGS) {
                fprintf(stderr, "vous ne pouvez pas afficher plus de %d fenetres en meme temp\n", TAILLE_LIST_ARGS);
                return 1;
            }
            int tab_id_images[TAILLE_LIST_ARGS];
            int compteur = 0;
            for (int i = 1; i < get_nb_args(); ++i) {
                int id = strtol(argumentslist[i], NULL, 10);
                if (get_image(id) != NULL) {
                    tab_id_images[compteur] = id;
                    compteur++;
                } else {
                    fprintf(stderr, "Erreur id image: id %s n'existe pas\n ", argumentslist[i]);
                }
            }
            run_display(tab_id_images, compteur);

        } else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "save", strlen("save")) == 0) {
        if (get_nb_args() == 2)
            save_image(strtol(argumentslist[1], NULL, 10));
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "symv", 4) == 0) {
        if (get_nb_args() == 2)
            symv_image((int) strtol(argumentslist[1], NULL, 10));
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "symh", 4) == 0) {
        if (get_nb_args() == 2)
            symh_image((int) strtol(argumentslist[1], NULL, 10));
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "select", strlen("select")) == 0) {
        if (get_nb_args() == 6 || get_nb_args() == 2) {
            int id = strtol(argumentslist[1], NULL, 10);
            structImage *image = get_image(id);
            if (image == NULL) {
                fprintf(stderr, "Id d'image non présent\n");
                return 1;
            }
            int ox = 0;
            int oy = 0;
            int fx = image->sprite->w;
            int fy = image->sprite->h;

            if (get_nb_args() == 6) {
                ox = strtol(argumentslist[2], NULL, 10);
                oy = strtol(argumentslist[3], NULL, 10);
                fx = strtol(argumentslist[4], NULL, 10);
                fy = strtol(argumentslist[5], NULL, 10);
            }
            if (errorzone(ox, oy, fx, fy, image->sprite->w, image->sprite->h) == 1) {
                return 1;
            }
            char *ligne = "";
            do {
                if (strlen(ligne) == 0) {

                } else if (strncmp(argumentslist[0], "cut", 3) == 0) {
                    if (get_nb_args() > 1) {
                        fillColor(image->sprite, ox, oy, fx, fy, 255, 255, 255);
                    } else {
                        fillColor(image->sprite, ox, oy, fx, fy, 0, 0, 0);
                    }
                } else if (strncmp(argumentslist[0], "fill", 4) == 0) {
                    if (get_nb_args() == 4) {
                        int r = strtol(argumentslist[1], NULL, 10),
                                g = strtol(argumentslist[2], NULL, 10),
                                b = strtol(argumentslist[3], NULL, 10);
                        if (errorcolor(r, g, b) == 0) {
                            fillColor(image->sprite, ox, oy, fx, fy, r, g, b);
                        }
                    } else {
                        fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
                    }
                } else if (strncmp(argumentslist[0], "copy", 4) == 0) {
                    if (get_nb_args() == 3) {
                        int nx = strtol(argumentslist[1], NULL, 10);
                        int ny = strtol(argumentslist[2], NULL, 10);
                        if (nx + fx > image->sprite->w || ny + fy > image->sprite->h || nx < 0 || ny < 0) {
                            perror("zone de copie non disponible");
                        } else {
                            copyAndPasteColor(image->sprite, ox, oy, fx, fy, nx, ny);
                        }
                    } else {
                        fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
                    }
                } else if (strncmp(argumentslist[0], "grey", 4) == 0) {
                    greyColor(image->sprite, ox, oy, fx, fy);
                } else if (strncmp(argumentslist[0], "bw", 2) == 0) {
                    blackAndWhiteColor(image->sprite, ox, oy, fx, fy);
                } else if (strncmp(argumentslist[0], "switch", 6) == 0) {
                    if (get_nb_args() == 8) {
                        int sr = strtol(argumentslist[1], NULL, 10);
                        int sg = strtol(argumentslist[2], NULL, 10);
                        int sb = strtol(argumentslist[3], NULL, 10);
                        int nr = strtol(argumentslist[4], NULL, 10);
                        int ng = strtol(argumentslist[5], NULL, 10);
                        int nb = strtol(argumentslist[6], NULL, 10);
                        int t = strtol(argumentslist[7], NULL, 10);
                        if (errorcolor(sr, sg, sb) == 0 && errorcolor(nr, ng, nb) == 0) {
                            switchColor(image->sprite, ox, oy, fx, fy, t, sr, sg, sb, nr, ng, nb);
                        }
                    } else {
                        fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
                    }
                } else if (strncmp(argumentslist[0], "neg", 3) == 0) {
                    negatifColor(image->sprite, ox, oy, fx, fy);
                } else {
                    printf("Commande inconnue");
                }
                printf("\nGraphics editor>%dx%d>%dx%d>%s", ox, oy, fx, fy, image->name);
                ligne = readline(">");
                traitement_espaces_debut(ligne);
                traitement_espaces_fin(ligne);
                creation_liste_arguments(ligne);
            } while (strncmp(argumentslist[0], "exit", 4) != 0);
        } else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "drawzone", strlen("drawzone")) == 0) {
        if (get_nb_args() == 6)
            drawzone(strtol(argumentslist[1], NULL, 10),
                     strtol(argumentslist[2], NULL, 10),
                     strtol(argumentslist[3], NULL, 10),
                     strtol(argumentslist[4], NULL, 10),
                     strtol(argumentslist[5], NULL, 10));
        else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "rotate", strlen("rotate")) == 0) {
        if (get_nb_args() == 3) {
            int r = strtol(argumentslist[2], NULL, 10) % 4;
            while (r > 0) {
                rotation(strtol(argumentslist[1], NULL, 10));
                r = r - 1;
            }
        } else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "resize", strlen("resize")) == 0) {

        if (get_nb_args() == 4) {
            int id_image = strtol(argumentslist[1], NULL, 10);
            int w = strtol(argumentslist[2], NULL, 10);
            int h = strtol(argumentslist[3], NULL, 10);

            resize(id_image, w, h);
        } else {
            fprintf(stderr, "Erreur nombre d'arguments dans la commande\n");
            return 1;
        }

    } else if (strncmp(argumentslist[0], "clear", strlen("clear")) == 0) {
        clear();

    } else if (strncmp(argumentslist[0], "help", strlen("help")) == 0) {
        display_help();

    } else if (strncmp(argumentslist[0], "exit", strlen("exit")) == 0) {
        SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
        liberation_arguments();
        while (my_images != NULL) {
            delete_image(1);
        }
        exit(EXIT_SUCCESS);

    } else {
        fprintf(stderr, "Commande : %s inconnue\n", ligne_a_traiter);
        return 1;
    }

    liberation_arguments();
    return 0;
}


void display_help() {
    fprintf(stdout, "\nListe des commandes disponibles :\n"
                    "\n"
                    "- exit : quite l' application\n"
                    "\n"
                    "- load pathfile : charge une image et lui donne un id\n"
                    "\n"
                    "- delete id : décharge l'image lié à id\n"
                    "\n"
                    "- save id [path] [name] [type] : sauvegarde l'image lié à id\n"
                    "\n"
                    "- show : affiche toutes les informations des images chargés\n"
                    "\n"
                    "- display id : affiche l'image lié à id\n"
                    "\n"
                    "- symv id : applique une symétrie verticale à l'image lié à id\n"
                    "\n"
                    "- symh id : applique une symétrie horizontale à l'image lié à id\n"
                    "\n"
                    "- rotate id nb : affectue nb rotation vers la gauche à l'image lié à id\n"
                    "\n"
                    "- drawzone id [width_origin=(default:0)] [height_origin=(default:0)] [width_end=(default:max)] [height_end=(default:max)] : modifie la zone de dessin l'image lié à id en fonction du point supérieur gauche (width_origine, height_origine) et du point inferieur bas (width_end, height_end)\n"
                    "\n"
                    "- resize id width height : modifie la résolution de l'image lié à id en fonction de width et height\n"
                    "\n"
                    "- select id [width_origin=(default:0)] [height_origin=(default:0)] [width_end=(default:max)] [height_end=(default:max)] : selection une partie de l'image lié à id en fonction du point supérieur gauche (width_origine, height_origine) et du point inferieur bas (width_end, height_end) afin défectuer les action suivantes :\n"
                    "\n"
                    "\t- cut [reverse=1]: remplace la zone par du noir ou du blanc si l'option reverse est utilisé\n"
                    "\n"
                    "\t- copy position_x position_y : copy la zone dans une autre zone d'origine le point supérieur gauche (position_x, position_y)\n"
                    "\n"
                    "\t- fill r g b : rempli la zone d'un melange de couleur rgb, attention r, g et b doit etre compris entre 0 et 255\n"
                    "\n"
                    "\t- switch r g b nr ng nb t : recherhe dans la zone les pixels ayant pour couleur un mélange de couleur r g b avec une tolérence -/+ t et les modifies par une mélange de couleur nr ng nb\n"
                    "\n"
                    "\t- neg : applique une filtre négatif sur la zone\n"
                    "\n"
                    "\t- bw : applique une filtre noir et blanc sur la zone\n"
                    "\n"
                    "\t- grey : applique une filtre gris sur la zone\n"
                    "\n"
                    "\t- exit : déselection la zone"
                    "\n\n");
}
