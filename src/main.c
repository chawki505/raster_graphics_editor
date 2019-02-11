#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

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

        SDL_Surface *pSprite = NULL;
        pSprite = SDL_LoadBMP("../img/image.bmp"); //load bitmap image


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

        //cas erreur creation de la fenetre
    } else {
        fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
    }

    SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).


    return EXIT_SUCCESS;
}