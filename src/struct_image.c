//
// Created by antony on 22/02/19.
//

#include "includes.h"

typedef enum {
    jpg = 0,
    png = 1,
    bmp = 2,
} formatImage;


typedef struct struct_image {
    int id;
    SDL_Window *pWindow;
    char *path;
    char *imageName;
    formatImage imageType;
    struct struct_image *next;
} struct_image;

