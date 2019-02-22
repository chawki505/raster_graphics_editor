#include "includes.h"
#include "parsing.h"
#include "traitement_image.h"
#include "traitement_fenetre.h"

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
    char *ligne = lecture_commande();
    printf("==> votre commande : %s\n", ligne);


    /*
   Creatation d'une fenetre
   */
    SDL_Window *pWindow = create_window();


    if (pWindow) {
        print_image_other_type(pWindow, ligne, IMG_INIT_JPG);//Afficher une image dans la fenetre
        SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
    }

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).


    return EXIT_SUCCESS;
}