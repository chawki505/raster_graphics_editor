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

    if (mystruc) {

        structImage *liste = my_images;

        if (liste == NULL) {

            mystruc->id = 1;
            my_images = mystruc;
        } else {
            int compteur = 2;
            while (liste->next != NULL) {
                compteur++;
                liste = liste->next;
            }
            if (liste->id == 1)
                compteur = 2;
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

void print_struct(structImage *myStruct) {
    printf("ID:%d\t\tPATH:%s\t\tFORMAT:%s\t\tNAME:%s\n", myStruct->id, myStruct->path, myStruct->format,
           myStruct->name);
}

void print_list_image() {
    structImage *liste = my_images;

    while (liste != NULL) {
        print_struct(liste);
        liste = liste->next;
    }
}

void delete_image(int id) {
    structImage *liste = my_images;
    structImage *tmp = NULL;
    while (liste->next->id != id) {
        liste = liste->next;
    }
    printf("-----------------------------");
    printf("Delete image:\n");
    print_struct(liste->next);
    printf("-----------------------------Done!\n");
    tmp = liste->next;
    liste->next = tmp->next;
    SDL_FreeSurface(tmp->sprite);
    free(tmp);
    liste = liste->next;
    while (liste != NULL) {
        liste->id--;
        liste = liste->next;
    }
    printf("-----------------------------");
    printf("New list:\n");
    print_list_image();
    printf("-----------------------------");
}