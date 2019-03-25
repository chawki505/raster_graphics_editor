//
// Created by chawki on 22/02/19.
//

#ifndef GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
#define GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H


typedef enum {
    jpg = 0,
    png = 1,
    bmp = 2,
} formatImage;


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


void printStruct(structImage *myStruct);

void add_image(structImage *mystruc);

structImage *get_image(int id);


#endif //GRAPHICS_EDITOR_MY_STRUCT_IMAGES_H
