//
// Created by chawki on 20/02/19.
//

#include "traitement_fenetre.h"


/* fonction qui cree une fenetre SDL */
SDL_Window *create_window() {

    /* Création de la fenêtre */
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow("Application SDL2",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               900,
                               600,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);


    //cas creation de la fenetre
    if (pWindow) {
        return pWindow;

        //cas erreur creation de la fenetre
    } else {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
        free(pWindow);
        return NULL;
    }

}




