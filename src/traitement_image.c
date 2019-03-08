//
// Created by chawki on 15/02/19.
//

#include "includes.h"
#include "traitement_fenetre.h"
#include "traitement_image.h"
#include "my_struct_images.h"


/* return le format de l'image passer en parametre*/
char *get_format_image(char *image_name) {

    if (image_name == NULL) {
        return NULL;
    }

    //duplique le nom de l'image dans un tmp
    char *tmp = strdup(image_name);

    //creer un pointeur sur le .
    char *format = strstr(tmp, ".");

    //si null ==> image name faux
    if (format == NULL) {
        return NULL;
    }

    //return extention sans le . du debut
    return (format + 1);
}


/* fonction pour ouvrire une image et l'afficher dans une fenetre*/
void open_image(char *path_image) {

    char *tmp = strdup(path_image);

    tmp = strstr(tmp, "/");

    char *nom_image = tmp;
    while (tmp != NULL) {
        nom_image = tmp + 1;
        tmp = strstr(tmp + 1, "/");
    }

    char *format = get_format_image(nom_image);

    if (format) {

        structImage *myimage = createStruct(path_image, nom_image, format);
        if (myimage) {
            add_image(myimage);
            fprintf(stdout, "image open %s \n", myimage->name);
        }
    } else {
        fprintf(stderr, "format image non correcte\n");
    }
}

/* print image in window if exist*/
void print_image(int id) {

    structImage *image = get_image(id);

    if (image) {

        /*
     Creatation d'une fenetre
     */
        SDL_Window *pWindow = create_window();

        if (pWindow) {
            if (strncmp(image->format, "png", 3) == 0)
                print_image_other_type(pWindow, image->path, IMG_INIT_PNG);//Afficher une image dans la fenetre
            else if (strncmp(image->format, "jpg", 3) == 0)
                print_image_other_type(pWindow, image->path, IMG_INIT_JPG);//Afficher une image dans la fenetre
            else if (strncmp(image->format, "bmp", 3) == 0)
                print_image_bmp_type(pWindow, image->path);//Afficher une image dans la fenetre

            else {
                fprintf(stdout, "Échec : format image non pris en charge !\n");
            }

            SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
        }

    }
}

/* fonction pour sauvguarder une image au format png */
void save_image(int id) {
    structImage *image = get_image(id);

    if (image && IMG_SavePNG(image->spirite, "my_image.png") == 0) {
        fprintf(stdout, "Image (%s) enregistrer ", image->name);
    } else {
        fprintf(stderr, "Erreur de sauvgarde\n");
    }
}


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



