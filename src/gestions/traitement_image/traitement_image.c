//
// Created by chawki on 15/02/19.
//

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
                free(pSprite);

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

/* fonction pour sauvguarder une image au format png */
void save_image(int id) {
    structImage *image = get_image(id);

    if (image && IMG_SavePNG(image->sprite, "my_image_save.png") == 0) {
        fprintf(stdout, "Image (%s) enregistrer !\n", image->name);
    } else {
        fprintf(stderr, "Erreur de sauvgarde\n");
    }
}

//TODO: a modifier !
/* fonction pour la rotation de l'image par un multiple de 90 */
void rotation_image(int id) {

    structImage *image = get_image(id);

    if (image == NULL) {
        perror("Aucune image chargé pour la rotation\n");
        return;
    }

    SDL_Surface *pSprite = image->sprite;

    SDL_Event event;

    bool quit = false;

    SDL_Renderer *renderer = NULL;
    SDL_Texture *t = NULL;

    int w_img = 0;
    int h_img = 0;

    char *tmp = readline("\nSaisir l'angle de rotation:");

    int angle = (int) strtol(tmp, NULL, 10);

    SDL_Rect box;
    SDL_Point point;

    switch (angle) {
        case -180:
        case 180:
        case 360:
        case -360:
            w_img = pSprite->w * 600 / pSprite->h;
            h_img = 600;                          //we define window's width always be 600px
            box = (SDL_Rect) {0, 0, w_img, h_img}; // SDL_Point point={pSprite->w/2, pSprite->h/2};
            point = (SDL_Point) {w_img / 2, h_img / 2};
            break;

        case -90:
        case 90:
        case -270:
        case 270:
            h_img = pSprite->w * 600 / pSprite->h;
            w_img = 600; //we define window's width always be 600px
            box = (SDL_Rect) {h_img / 2 - (h_img - w_img / 2),
                              -h_img / 2 + (h_img - w_img / 2),
                              h_img,
                              w_img}; // SDL_Point point={pSprite->w/2, pSprite->h/2};
            point = (SDL_Point) {h_img / 2,
                                 w_img / 2};
            break;
        default:
            printf("erreur d'angle\n");
            return;
    }

    SDL_Window *pWindow = SDL_CreateWindow(
            "Image",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            w_img,
            h_img,
            SDL_WINDOW_OPENGL);

    //cas creation de la spirit
    while (!quit) {

        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }

        renderer = SDL_CreateRenderer(pWindow, -1, 0);

        t = SDL_CreateTextureFromSurface(renderer, pSprite);

        SDL_RenderCopyEx(renderer, t, NULL, &box, angle, &point, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(pWindow);
    }

    free(pSprite);
    SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
}