#include "includes.h"
#include "parsing.h"
#include "traitement_image.h"

int main(int argc, char *argv[]) {

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) // Démarrage de la SDL (ici : chargement du système vidéo)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }

    /*
    La SDL est chargée.
    */

    char *ligne = lecture_commande();
    printf("==> votre commande : %s\n", ligne);


    /* Création de la fenêtre */
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow("Application SDL2",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN);

    //cas creation de la fenetre
    if (pWindow) {

        print_image(pWindow, "../img/image.bmp");

        //cas erreur creation de la fenetre
    } else {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }


    SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).


    return EXIT_SUCCESS;
}