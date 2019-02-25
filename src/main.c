#include "includes.h"
#include "parsing.h"
#include "traitement_image.h"
#include "traitement_fenetre.h"

#include "my_struct_images.h"

int main(int argc, char *argv[]) {

    /*
     * Initialisation simple
    */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) // Démarrage de la SDL (ici : chargement du système vidéo)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /*
    La SDL est chargée.
    */


    /*
   Lecture de la commande
   */
    while (1) {
        char *ligne = lecture_commande();
        printf("==> votre commande : %s\n", ligne);

        traitement_ligne(ligne);

    }


    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).


    return EXIT_SUCCESS;
}