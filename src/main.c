//
// Created by chawki chouib on 2019-02-08.
//

#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO); // Démarrage de la SDL (ici : chargement du système vidéo)

    /*
    La SDL est chargée.
    Vous pouvez mettre ici le contenu de votre programme
    */

   SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).


    return 0;
}