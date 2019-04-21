//
// Created by chawki on 22/02/19.
//

#ifndef GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
#define GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H

#include "../../includes.h"


typedef struct structImage {
    int id;
    SDL_Surface *sprite;
    char *path;
    char *name;
    char *format;
    struct structImage *next;
} structImage;


structImage *my_images;


structImage *createStruct_other_format(char *path, char *name, char *format, int type_image);

structImage *createStruct_bmp_format(char *path, char *name, char *format);


void print_struct(structImage *myStruct);

void add_image(structImage *mystruc);

void print_list_image();

void delete_image(int id);

structImage *get_image(int id);


#endif //GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
