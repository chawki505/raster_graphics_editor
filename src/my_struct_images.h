//
// Created by chawki on 22/02/19.
//

#ifndef GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
#define GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H


#include "includes.h"

typedef enum {
    jpg = 0,
    png = 1,
    bmp = 2,
} formatImage;


typedef struct structImage {
    int id;
    SDL_Window *pWindow;
    char *path;
    char *imageName;
    char *imageType;
    struct structImage *next;
} structImage;


structImage *createStruct(char *pathImage);

void printStruct(structImage *myStruct);


#endif //GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
