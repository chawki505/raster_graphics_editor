//
// Created by chawki on 15/02/19.
//

#ifndef RASTER_GRAPHICS_EDITOR_PARSING_H
#define RASTER_GRAPHICS_EDITOR_PARSING_H


#define TAILLE_LIST_ARGS 32


char *lecture_commande();

void creation_liste_arguments(char *saisi_user);

void liberation_arguments();

int get_nb_args();

void traitement_espaces_debut(char *chaine_a_traiter);

void traitement_espaces_fin(char *chaine_a_traiter);

int traitement_ligne(char *chaine_a_traiter);

void display_help();

void clear();


#endif //RASTER_GRAPHICS_EDITOR_PARSING_H
