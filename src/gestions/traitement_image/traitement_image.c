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
                //free(pSprite);

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
            h_img = 600;//we define window's width always be 600px
            box = (SDL_Rect) {0, 0, w_img, h_img};// SDL_Point point={pSprite->w/2, pSprite->h/2};
            point = (SDL_Point) {w_img / 2, h_img / 2};
            break;

        case -90:
        case 90:
        case -270:
        case 270:
            h_img = pSprite->w * 600 / pSprite->h;
            w_img = 600;//we define window's width always be 600px
            box = (SDL_Rect) {h_img / 2 - (h_img - w_img / 2),
                              -h_img / 2 + (h_img - w_img / 2),
                              h_img,
                              w_img};// SDL_Point point={pSprite->w/2, pSprite->h/2};
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
            SDL_WINDOW_OPENGL
    );

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

    //free(pSprite);
    SDL_DestroyWindow(pWindow); //Liberation de la ressource occupée par la fenetre
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
}

void setPixelColor(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch (nbOctetsParPixel) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *) p = pixel;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *) p = pixel;
            break;
    }
}

void greyColor(SDL_Surface *surface, int ox, int oy, int fx, int fy) {
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    SDL_LockSurface(surface);
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            getPixelColor(surface, i, j, &r, &g, &b, &a);
            Uint8 grey = (r + g + b) / 3;
            pixel = SDL_MapRGBA(surface->format, grey, grey, grey, 255);// grey mod
            setPixelColor(surface, i, j, pixel);
        }
    }
    SDL_UnlockSurface(surface);
}

void negatifColor(SDL_Surface *surface, int ox, int oy, int fx, int fy) {
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    SDL_LockSurface(surface);
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            getPixelColor(surface, i, j, &r, &g, &b, &a);
            pixel = SDL_MapRGBA(surface->format, 255 - r, 255 - g, 255 - b, a);
            setPixelColor(surface, i, j, pixel);
        }
    }
    SDL_UnlockSurface(surface);
}

void blackAndWhiteColor(SDL_Surface *surface, int ox, int oy, int fx, int fy) {
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    int dimX = fx - ox, dimY = fy - oy;
    Uint8 saveColor[dimX][dimY];
    int somme = 0;
    Uint8 moyenne = 0;
    SDL_LockSurface(surface);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            getPixelColor(surface, i+ox, j+oy, &r, &g, &b, &a);
            Uint8 grey = (r + g + b) / 3;
            saveColor[i][j] = grey;
            somme = somme + grey;
        }
    }
    moyenne = somme / (dimX * dimY);
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            if (saveColor[i - ox][j - oy] <= moyenne) {
                pixel = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
                setPixelColor(surface, i, j, pixel);
            } else {
                pixel = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
                setPixelColor(surface, i, j, pixel);
            }

        }
    }
    SDL_UnlockSurface(surface);
}

void switchColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int t,
                 int sr, int sg, int sb, int nr, int ng, int nb) {
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    SDL_LockSurface(surface);
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            getPixelColor(surface, i, j, &r, &g, &b, &a);
            if (sr - t <= r && r <= sr + t
                && sg - t <= g && g <= sg + t
                && sb - t <= b && b <= sb + t) {
                pixel = SDL_MapRGBA(surface->format, nr, ng, nb, 255);
                setPixelColor(surface, i, j, pixel);
            }
        }
    }
    SDL_UnlockSurface(surface);
}

void fillColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int nr, int ng, int nb) {
    Uint32 pixel = 0;
    SDL_LockSurface(surface);
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            pixel = SDL_MapRGBA(surface->format, nr, ng, nb, 255);
            setPixelColor(surface, i, j, pixel);
        }
    }
    SDL_UnlockSurface(surface);
}

void copyAndPasteColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int nx, int ny) {
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    int dimX = fx-ox;
    int dimY = fy-oy;
    Uint8 saveColor[dimX][dimY][3];
    SDL_LockSurface(surface);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            getPixelColor(surface, i+ox, j+oy, &r, &g, &b, &a);
            saveColor[i][j][0] = r;
            saveColor[i][j][1] = g;
            saveColor[i][j][2] = b;

        }
    }
    for (int i = ox; i < fx; ++i) {
        for (int j = oy; j < fy; ++j) {
            pixel = SDL_MapRGBA(surface->format, saveColor[i-ox][j-oy][0], saveColor[i-ox][j-oy][1], saveColor[i-ox][j-oy][2], 255);
            setPixelColor(surface, i+nx, j+ny, pixel);
        }
    }
    SDL_UnlockSurface(surface);
}

void selectRegion(int id){
    structImage *image = get_image(id);
    int ox,oy,fx,fy;
    printf("Saisir le point x d'origine :");
    scanf("%d",&ox);
    printf("Saisir le point y d'origine :");
    scanf("%d",&oy);
    printf("Saisir le point x de fin :");
    scanf("%d",&fx);
    printf("Saisir le point y de fin :");
    scanf("%d",&fy);
    char *ligne="";
    char *tmp=NULL;
    do{
        if(strlen(ligne)==0){
            printf("Initialisation");
        }else if(strncmp(tmp, "cut", 3) == 0){
           fillColor(image->sprite,ox,oy,fx,fy,0,0,0);
        }else if(strncmp(tmp, "fill", 4) == 0){
            int r,g,b;
            printf("niveau de rouge [0-255] :");
            scanf("%d",&r);
            printf("niveau de vert [0-255] :");
            scanf("%d",&g);
            printf("niveau de bleu [0-255] :");
            scanf("%d",&b);
            fillColor(image->sprite,ox,oy,fx,fy,r,g,b);
        }else if(strncmp(tmp, "copy", 4) == 0){
            int nx,ny;
            printf("Saisir le point x d'origine de la copie:");
            scanf("%d",&nx);
            printf("Saisir le point y d'origine de la copie:");
            scanf("%d",&ny);
            copyAndPasteColor(image->sprite,ox,oy,fx,fy,nx,ny);
        }else if(strncmp(tmp, "grey", 4) == 0){
            greyColor(image->sprite,ox,oy,fx,fy);
        }else if(strncmp(tmp, "bw", 2) == 0){
            blackAndWhiteColor(image->sprite,ox,oy,fx,fy);
        }else if(strncmp(tmp, "switch", 6) == 0) {
            int sr, sg, sb, nr, ng, nb, t;
            printf("niveau de rouge recherché [0-255] :");
            scanf("%d", &sr);
            printf("niveau de vert recherché [0-255] :");
            scanf("%d", &sg);
            printf("niveau de bleu recherché [0-255] :");
            scanf("%d", &sb);
            printf("niveau de tolérence:");
            scanf("%d", &t);
            printf("niveau de rouge modifié [0-255] :");
            scanf("%d", &nr);
            printf("niveau de vert modifié [0-255] :");
            scanf("%d", &ng);
            printf("niveau de bleu modifié [0-255] :");
            scanf("%d", &nb);
            switchColor(image->sprite, ox, oy, fx, fy, t, sr, sg, sb, nr, ng, nb);
        }else if(strncmp(tmp, "neg", 3) == 0){
            negatifColor(image->sprite,ox,oy,fx,fy);
        }else{
            printf("Commande inconnue");
        }
        display_image(id);
        ligne = readline("\nGraphics editor>region>");
        tmp = strdup(ligne);
    }while(strncmp(tmp, "exit", 4) != 0);
}

void drawzone(int id){
    structImage *image = get_image(id);
    int ox,oy,fx,fy;
    printf("Saisir le point x d'origine :");
    scanf("%d",&ox);
    printf("Saisir le point y d'origine :");
    scanf("%d",&oy);
    printf("Saisir le point x de fin :");
    scanf("%d",&fx);
    printf("Saisir le point y de fin :");
    scanf("%d",&fy);
    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;
    int dimX = fx-ox;
    int dimY = fy-oy;
    Uint8 saveColor[dimX][dimY][3];

    SDL_LockSurface(image->sprite);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            getPixelColor(image->sprite, i+ox, j+oy, &r, &g, &b, &a);
            saveColor[i][j][0] = r;
            saveColor[i][j][1] = g;
            saveColor[i][j][2] = b;

        }


    }
    SDL_UnlockSurface(image->sprite);

    SDL_Surface *surface = SDL_CreateRGBSurface(0, dimX, dimY, 32, 0, 0, 0, 0);
    SDL_LockSurface(surface);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            pixel = SDL_MapRGBA(surface->format, saveColor[i][j][0], saveColor[i][j][1], saveColor[i][j][2], 255);
            setPixelColor(surface, i, j, pixel);
        }
    }
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(image->sprite);
    image->sprite=surface;

}