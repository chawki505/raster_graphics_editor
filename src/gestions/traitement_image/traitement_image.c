//
// Created by chawki on 15/02/19.
//

#include "../../includes.h"

#include "../my_struct_images/my_struct_images.h"
#include "../traitement_fenetre/traitement_fenetre.h"

#include "traitement_image.h"


void close_all_Lwindow(LWindow *gWindows, int nb_window);

/* return le format de l'image passer en parametre*/
char *get_format_image(char *image_name) {

    if (image_name == NULL) {
        return NULL;
    }

    //duplique le nom de l'image dans un argumentslist[0]
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
int load_image(char *path_image) {

    char *path = strdup(path_image);
    char *nom = NULL;
    char *format = NULL;

    char *tmp = strdup(path_image);

    tmp = strstr(tmp, "/");

    if (tmp == NULL) {
        nom = path;
    } else {

        while (tmp != NULL) {
            nom = tmp + 1;
            tmp = strstr(tmp + 1, "/");
        }

    }


    format = get_format_image(nom);

    if (format) {
        structImage *myimage = NULL;

        if (strncmp(format, "bmp", 3) == 0) {
            myimage = createStruct_bmp_format(path, nom, format);
        } else if (strncmp(format, "jpg", 3) == 0) {
            myimage = createStruct_other_format(path, nom, format, IMG_INIT_JPG);
        } else if (strncmp(format, "png", 3) == 0) {
            myimage = createStruct_other_format(path, nom, format, IMG_INIT_PNG);
        } else {
            fprintf(stderr, "format image non correcte\n");
            return 1;
        }

        if (myimage) {
            add_image(myimage);
            fprintf(stdout, "image open %s \n", myimage->name);
        }

    } else {
        fprintf(stderr, "format image non correcte\n");
        return 1;
    }
    return 0;
}


/* fonction pour sauvguarder une image au format png */
int save_image(int id) {
    structImage *image = get_image(id);

    if (image && IMG_SavePNG(image->sprite, "my_image_save.png") == 0) {
        fprintf(stdout, "Image (%s) enregistrer !\n", image->name);
        return 0;
    } else {
        fprintf(stderr, "Erreur de sauvgarde\n");
        return 1;
    }
}

int symv_image(int id) {
    structImage *image = get_image(id);
    if (image == NULL) {
        fprintf(stderr, "Id d'image non présent\n");
        return 1;
    }

    SDL_Surface *old_surface = image->sprite;
    int w = old_surface->w;
    int h = old_surface->h;

    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;

    SDL_Surface *surface = SDL_CreateRGBSurface(0,
                                                w,
                                                h,
                                                32,
                                                old_surface->format->Rmask,
                                                old_surface->format->Gmask,
                                                old_surface->format->Bmask,
                                                old_surface->format->Amask);
    SDL_LockSurface(old_surface);
    SDL_LockSurface(surface);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {


            getPixelColor(image->sprite, i, j, &r, &g, &b, &a);
            pixel = SDL_MapRGBA(surface->format, r, g, b, a);
            setPixelColor(surface, i, h - j - 1, pixel);

        }
    }

    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(old_surface);

    SDL_FreeSurface(old_surface);
    image->sprite = surface;
    return 0;
}

int symh_image(int id) {
    structImage *image = get_image(id);
    if (image == NULL) {
        fprintf(stderr, "Id d'image non présent\n");
        return 1;
    }

    SDL_Surface *old_surface = image->sprite;
    int w = old_surface->w;
    int h = old_surface->h;

    Uint8 r = 0, g = 0, b = 0, a = 0;
    Uint32 pixel = 0;

    SDL_Surface *surface = SDL_CreateRGBSurface(0,
                                                w,
                                                h,
                                                32,
                                                old_surface->format->Rmask,
                                                old_surface->format->Gmask,
                                                old_surface->format->Bmask,
                                                old_surface->format->Amask);
    SDL_LockSurface(old_surface);
    SDL_LockSurface(surface);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {


            getPixelColor(image->sprite, i, j, &r, &g, &b, &a);
            pixel = SDL_MapRGBA(surface->format, r, g, b, a);
            setPixelColor(surface, w - i - 1, j, pixel);

        }
    }

    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(old_surface);

    SDL_FreeSurface(old_surface);
    image->sprite = surface;
    return 0;
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
            getPixelColor(surface, i + ox, j + oy, &r, &g, &b, &a);
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
    int dimX = fx - ox;
    int dimY = fy - oy;
    Uint32 saveColor[dimX][dimY];
    SDL_LockSurface(surface);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            saveColor[i][j] = getPixel(surface, i + ox, j + oy);
        }
    }
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            setPixelColor(surface, i + nx, j + ny, saveColor[i][j]);
        }
    }
    SDL_UnlockSurface(surface);
}

int drawzone(int id, int ox, int oy, int fx, int fy) {
    structImage *image = get_image(id);
    if (image == NULL) {
        fprintf(stderr, "Id d'image non présent\n");
        return 1;
    }
    int dimX = fx - ox;
    int dimY = fy - oy;
    if (errorzone(ox, oy, fx, fy, image->sprite->w, image->sprite->h) == 1
        || dimX < 0 || dimY < 0) {
        return 1;
    }
    Uint32 pixel = 0;
    SDL_Surface *surface = SDL_CreateRGBSurface(0, dimX, dimY, 32,
                                                image->sprite->format->Rmask,
                                                image->sprite->format->Gmask,
                                                image->sprite->format->Bmask,
                                                image->sprite->format->Amask);
    SDL_LockSurface(surface);
    SDL_LockSurface(image->sprite);
    for (int i = 0; i < dimX; ++i) {
        for (int j = 0; j < dimY; ++j) {
            pixel = getPixel(image->sprite, i + ox, j + oy);
            setPixelColor(surface, i, j, pixel);
        }
    }
    SDL_UnlockSurface(image->sprite);
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(image->sprite);
    image->sprite = surface;
    return 0;
}

int rotation(int id) {
    structImage *image = get_image(id);
    if (image == NULL) {
        fprintf(stderr, "Id d'image non présent\n");
        return 1;
    }
    Uint32 pixel = 0;
    SDL_Surface *old_surface = image->sprite;

    int w = old_surface->w;
    int h = old_surface->h;

    SDL_LockSurface(old_surface);

    SDL_Surface *surface = SDL_CreateRGBSurface(0,
                                                h,
                                                w,
                                                32,
                                                old_surface->format->Rmask,
                                                old_surface->format->Gmask,
                                                old_surface->format->Bmask,
                                                old_surface->format->Amask);
    SDL_LockSurface(surface);
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            pixel = getPixel(image->sprite, i, j);
            setPixelColor(surface, j, w - i - 1, pixel);
        }
    }
    SDL_UnlockSurface(old_surface);
    SDL_UnlockSurface(surface);
    SDL_FreeSurface(old_surface);
    image->sprite = surface;
    return 0;
}

int errorzone(int ox, int oy, int fx, int fy, int wmax, int hmax) {
    if (ox < 0 || oy < 0 || ox > wmax || oy > hmax || ox > fx || oy > fy || fx > wmax || fx > hmax) {
        perror("Valeurs de positionnement incorrects");
        return 1;
    }
    return 0;
}

int errorcolor(int r, int g, int b) {
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        perror("Valeurs de couleur incorrects");
        return 1;
    }
    return 0;
}


void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {

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


SDL_Surface *resize_image(SDL_Surface *image, Uint16 w, Uint16 h) {

    if (image && w && h) {

        SDL_Surface *new_image = SDL_CreateRGBSurface(image->flags, w, h, image->format->BitsPerPixel,
                                                      image->format->Rmask, image->format->Gmask, image->format->Bmask,
                                                      image->format->Amask);

        double _stretch_factor_x = ((double) (w) / (double) (image->w));
        double _stretch_factor_y = ((double) (h) / (double) (image->h));

        //Run across all Y pixels.
        for (Sint32 y = 0; y < image->h; y++)
            //Run across all X pixels.
            for (Sint32 x = 0; x < image->w; x++)
                //Draw _stretch_factor_y pixels for each Y pixel.
                for (Sint32 o_y = 0; o_y < _stretch_factor_y; ++o_y)
                    //Draw _stretch_factor_x pixels for each X pixel.
                    for (Sint32 o_x = 0; o_x < _stretch_factor_x; ++o_x)

                        setPixel(new_image,
                                 (Sint32) (_stretch_factor_x * x) + o_x,
                                 (Sint32) (_stretch_factor_y * y) + o_y,
                                 getPixel(image, x, y)
                        );
        return new_image;
    } else {
        perror("Erreur resize image !\n");
        return NULL;
    }
}


int resize(int id, int w, int h) {

    structImage *image = get_image(id);

    if (image) {
        SDL_Surface *new_image = resize_image(image->sprite, w, h);

        if (new_image) {
            SDL_FreeSurface(image->sprite);
            image->sprite = new_image;
            fprintf(stdout, "Image redimensionner avec succès !\n");
        }
    } else {
        fprintf(stdout, "Échec de chargement de l'image (id non existant)\n");
        return 1;
    }
    return 0;
}


void close_all_Lwindow(LWindow *gWindows, int nb_window) {
    //Destroy windows
    for (int i = 0; i < nb_window; ++i) {
        free_LWindow(&gWindows[i]);
    }
}


int run_display(int *tab_id_images, int sizetab) {

    //init value of tab window
    int nb_window = sizetab;

    //Our custom windows
    LWindow gWindows[nb_window];


    for (int i = 0; i < nb_window; ++i) {
        init_value_LWindow(&gWindows[i]);
    }


    //Initialize the windows
    for (int i = 0; i < nb_window; ++i) {
        structImage *myimage = get_image(tab_id_images[i]);
        if (init_LWindow(&gWindows[i], myimage->sprite))
            fprintf(stdout, "Window %d created\n", i + 1);
    }

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;

    //While application is running
    while (!quit) {

        //Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            //User requests quit
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            //Handle window events
            for (int i = 0; i < nb_window; ++i) {
                handleEvent_LWindow(&gWindows[i], &event);
            }
        }


        //Update all windows
        for (int i = 0; i < nb_window; ++i) {
            render_LWindow(&gWindows[i]);
        }

        //Check all windows
        bool allWindowsClosed = true;

        for (int i = 0; i < nb_window; ++i) {
            if (gWindows[i].mShown) {
                allWindowsClosed = false;
                break;
            }
        }

        //Application closed all windows
        if (allWindowsClosed) {
            quit = true;
        }
    }

    //Free resources
    close_all_Lwindow(gWindows, nb_window);


    return 0;
}