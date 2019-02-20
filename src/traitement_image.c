//
// Created by chawki on 15/02/19.
//

#include "includes.h"
#include "traitement_image.h"


void print_image(SDL_Window *pWindow, char *path_image) {

    SDL_Surface *pSprite = NULL;
    pSprite = SDL_LoadBMP(path_image); //load bitmap image


    //cas creation de la spirit
    if (pSprite) {

        SDL_Rect dest = {640 / 2 - pSprite->w / 2, 480 / 2 - pSprite->h / 2, 0, 0};
        SDL_BlitSurface(pSprite, NULL, SDL_GetWindowSurface(pWindow), &dest); // Copie du sprite

        SDL_UpdateWindowSurface(pWindow); // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
        SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voit la fenêtre */

        SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

        //cas erreur creation du spirit
    } else {
        fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
    }

}


