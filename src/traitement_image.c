//
// Created by chawki on 15/02/19.
//

#include <stdbool.h>
#include "includes.h"
#include "traitement_image.h"


/* fonction pour afficher une image dans une fenetre (version png et jpg) */
void print_image_other_type(SDL_Window *pWindow, char *path_image, int type_image) {


    IMG_Init(type_image);//init SDL_image
    SDL_Event event; //var pour la gestion des evenement
    bool quit = false; // var bool pour quitter la boucle
    SDL_Surface *pSprite = NULL; // var sprite pour charger l'image
    pSprite = IMG_Load(path_image); //load bitmap image chargement de l'image

    //cas creation de la spirit
    if (pSprite) {


        while (!quit) {
            SDL_WaitEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }

            int w, h;
            SDL_GetWindowSize(pWindow, &w, &h); // recuperer les dimensions de la fenetre

            SDL_Rect dest = {w / 2 - pSprite->w / 2, h / 2 - pSprite->h / 2, 0, 0};
            SDL_BlitSurface(pSprite, NULL, SDL_GetWindowSurface(pWindow), &dest); // Copie du sprite
            SDL_UpdateWindowSurface(pWindow); // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
        }

        SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite


        //cas erreur creation du spirit
    } else {
        fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
    }

    IMG_Quit();



    /*
    //IMG_Init(IMG_INIT_JPG);

    bool quit = false;
    SDL_Event event;

    SDL_Renderer *renderer = SDL_CreateRenderer(pWindow, -1, 0);
    SDL_Surface *image = SDL_LoadBMP("../img/image.bmp");
    //SDL_Surface *image = IMG_Load("../img/image2.jpg");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    while (!quit) {
        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }

        //SDL_Rect dstrect = { 5, 5, 320, 240 };
        //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);

    //IMG_Quit();
    */

}


/* fonction pour afficher une image dans une fenetre (version bmp) */
void print_image_bmp_type(SDL_Window *pWindow, char *path_image) {

    SDL_Event event;
    bool quit = false;
    SDL_Surface *pSprite = NULL;
    pSprite = SDL_LoadBMP(path_image); //load bitmap image

    //cas creation de la spirit
    if (pSprite) {
        while (!quit) {
            SDL_WaitEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }

            SDL_Surface *surface = SDL_GetWindowSurface(pWindow);
            int w, h;
            SDL_GetWindowSize(pWindow, &w, &h);
            SDL_Rect dest = {w / 2 - pSprite->w / 2, h / 2 - pSprite->h / 2, 0, 0};
            SDL_BlitSurface(pSprite, NULL, surface, &dest); // Copie du sprite

            SDL_UpdateWindowSurface(pWindow); // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
        }

        SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

        //cas erreur creation du spirit
    } else {
        fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
    }

}

