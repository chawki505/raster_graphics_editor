#include "includes.h"
#include "parsing/parsing.h"


bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!\n");
        }
    }

    return success;
}


int main(int argc, char *argv[]) {

    /*
     * Initialisation sdl
    */
    if (!init()) // Démarrage de la SDL (ici : chargement du système vidéo)
    {
        fprintf(stderr, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return EXIT_FAILURE;
    }


    /*
   Lecture de la commande
   */
    while (1) {
        char *ligne = lecture_commande();
        traitement_ligne(ligne);
        free(ligne);
    }
}