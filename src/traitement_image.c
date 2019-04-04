//
// Created by chawki on 15/02/19.
//
#include <inttypes.h>

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

        structImage *myimage = createStruct2(path_image, nom_image, format);
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


}


/* fonction pour afficher une image dans une fenetre (version bmp) */
void print_image_bmp_type(SDL_Window *pWindow, char *path_image) {
    Uint8 r=0, g=0, b=0, a=0;
    SDL_Event event;
    bool quit = false;
    SDL_Surface *pSprite = NULL;
    pSprite = SDL_LoadBMP(path_image); //load bitmap image


    //cas creation de la spirit
    if (pSprite) {
        SDL_LockSurface(pSprite);
        Uint32 pixel = SDL_MapRGBA(pSprite->format, 0, 0, 255, 255);
        SDL_GetRGBA(pixel, pSprite->format, &r, &g, &b, &a);
        /*printf("pixel:%d\trouge:%d\tvert:%d\tbleu:%d\ttransparence:%d\n", (unsigned int) pixel, (unsigned int) r,
               (unsigned int) g, (unsigned int) b, (unsigned int) a);*/
        for (int i = 0; i < pSprite->w; ++i) {
            for (int j = 0; j < pSprite->h; ++j) {
                getPixelColor(pSprite,i,j,&r, &g, &b, &a);
                Uint8 grey = (r+g+b)/3;
                pixel = SDL_MapRGBA(pSprite->format, grey, grey, grey, grey);
                //pixel = SDL_MapRGBA(pSprite->format, 255-r, 255-g, 255-b, a);
                setPixelColor(pSprite,i,j,pixel);
            }
        }


        SDL_UnlockSurface(pSprite);
        SDL_Surface *surface = SDL_GetWindowSurface(pWindow);
        int w, h;
        SDL_GetWindowSize(pWindow, &w, &h);
        SDL_Rect dest = {w / 2 - pSprite->w / 2, h / 2 - pSprite->h / 2, 0, 0};
        SDL_BlitSurface(pSprite, NULL, surface, &dest); // Copie du sprite

        SDL_UpdateWindowSurface(pWindow); // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
        while (!quit) {
            SDL_WaitEvent(&event);

            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        //cas erreur creation du spirit
    } else {
        fprintf(stdout, "Échec de chargement du sprite (%s)\n", SDL_GetError());
    }

    SDL_FreeSurface(pSprite); // Libération de la ressource occupée par le sprite
}


Uint32 getPixel(SDL_Surface *surface, int x, int y) {
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch (nbOctetsParPixel) {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *) p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *) p;
        default:
            return 0;
    }
}

void getPixelColor(SDL_Surface *surface, int x, int y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a) {
    Uint32 pixel = getPixel(surface, x, y);
    SDL_GetRGBA(pixel, surface->format, r, g, b, a);
    /*printf("pixel:%d\trouge:%d\tvert:%d\tbleu:%d\ttransparence:%d\n", (unsigned int) pixel, (unsigned int) *r,
           (unsigned int) *g, (unsigned int) *b, (unsigned int) *a);*/
}

void setPixelColor(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

