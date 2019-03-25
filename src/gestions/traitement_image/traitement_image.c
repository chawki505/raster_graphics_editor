//
// Created by chawki on 15/02/19.
//


#include "../../includes.h"
#include "../traitement_fenetre/traitement_fenetre.h"
#include "../my_struct_images/my_struct_images.h"

#include "traitement_image.h"

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
void load_image(char *path_image) {

    char *tmp = strdup(path_image);

    tmp = strstr(tmp, "/");

    char *nom_image = tmp;

    while (tmp != NULL) {
        nom_image = tmp + 1;
        tmp = strstr(tmp + 1, "/");
    }

    char *format = get_format_image(nom_image);

    if (format) {
        structImage *myimage = NULL;

        if (strncmp(format, "bmp", 3) == 0) {
            myimage = createStruct_bmp_format(path_image, nom_image, format);

        } else if (strncmp(format, "jpg", 3) == 0) {
            myimage = createStruct_other_format(path_image, nom_image, format, IMG_INIT_JPG);
        } else if (strncmp(format, "png", 3) == 0) {
            myimage = createStruct_other_format(path_image, nom_image, format, IMG_INIT_PNG);
        }

        if (myimage) {
            add_image(myimage);
            fprintf(stdout, "image open %s \n", myimage->name);
        }
    } else {
        fprintf(stderr, "format image non correcte\n");
    }
}


/* print image in window if exist*/
void display_image(int id) {

    structImage *image = get_image(id);

    if (image) {

        /*
     Creatation d'une fenetre
     */
        SDL_Window *pWindow = create_window();

        if (pWindow) {

            SDL_Event event;
            bool quit = false;
            SDL_Surface *pSprite = image->sprite;


            if (pSprite) {

                while (!quit) {
                    SDL_WaitEvent(&event);

                    switch (event.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                    }

                    SDL_Surface *surface_window = SDL_GetWindowSurface(pWindow);

                    int w, h;
                    SDL_GetWindowSize(pWindow, &w, &h);

                    SDL_Rect dest = {w / 2 - pSprite->w / 2, h / 2 - pSprite->h / 2, 0, 0};
                    SDL_BlitSurface(pSprite, NULL, surface_window, &dest); // Copie du sprite

                    SDL_UpdateWindowSurface(
                            pWindow); // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
                }

                //SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite

                //cas erreur creation du spirit
            } else {
                fprintf(stdout, "Échec de chargement de l'image (%s)\n", SDL_GetError());
            }
            SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
        }
    } else {
        fprintf(stdout, "Échec de chargement de l'image (id non existant)\n");
    }
}
