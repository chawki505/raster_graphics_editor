//
// Created by chawki on 22/02/19.
//

#include "my_struct_images.h"


void init_value_struct(char *path, char *name, char *format, structImage *myStruct);

structImage *createStruct_other_format(char *path, char *name, char *format, int type_image) {
    structImage *myStruct = malloc(sizeof(structImage));

    if (myStruct == NULL) {
        perror("promblème allocation image struct\n");
        return NULL;
    }

    IMG_Init(type_image);//init SDL_image
    init_value_struct(path, name, format, myStruct);
    myStruct->sprite = IMG_Load(path); //load other format image

    return myStruct;
}


structImage *createStruct_bmp_format(char *path, char *name, char *format) {
    structImage *myStruct = malloc(sizeof(structImage));

    if (myStruct == NULL) {
        perror("promblème allocation image struct\n");
        return NULL;
    }

    init_value_struct(path, name, format, myStruct);
    myStruct->sprite = SDL_LoadBMP(path); //load bitmap image

    return myStruct;
}

void init_value_struct(char *path, char *name, char *format, structImage *myStruct) {
    myStruct->id = 1;
    myStruct->path = path;
    myStruct->name = name;
    myStruct->format = format;
    myStruct->next = NULL;
}

/* insertion image vers la fin*/
void add_image(structImage *mystruc) {

    int compteur = 1;

    if (mystruc) {

        structImage *liste = my_images;

        if (liste == NULL) {

            mystruc->id = compteur;
            my_images = mystruc;
        } else {

            while (liste->next != NULL) {

                compteur++;
                liste = liste->next;
            }
            if (compteur == 1) {
                compteur++;
            }

            mystruc->id = compteur;
            liste->next = mystruc;
        }
    }
}

/* return image struc if exist else null*/
structImage *get_image(int id) {

    structImage *liste = my_images;

    while (liste != NULL && liste->id != id) {
        liste = liste->next;
    }
    return liste ? liste : NULL;
}

void printStruct(structImage *myStruct) {
    printf("%d\n%s\n%s\n%s", myStruct->id, myStruct->path, myStruct->format, myStruct->name);
}

