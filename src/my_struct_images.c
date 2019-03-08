//
// Created by chawki on 22/02/19.
//

#include "includes.h"
#include "my_struct_images.h"


structImage *createStruct(char *path, char *name, char *format) {
    structImage *myStruct = malloc(sizeof(structImage));

    if (myStruct == NULL) {
        perror("promblème allocation");
        return NULL;
    }

    myStruct->id = 1;
    myStruct->path = path;
    myStruct->name = name;
    myStruct->format = format;
    myStruct->next = NULL;


    return myStruct;
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

