//
// Created by chawki on 22/02/19.
//

#include "includes.h"
#include "my_struct_images.h"


structImage *createStruct2(char *path, char *name, char *format) {
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


structImage *createStruct(char *pathImage) {
    structImage *myStruct = malloc(sizeof(structImage));
    if (myStruct == NULL) {
        perror("promblème allocation");
        return NULL;
    }
    char *buffer = pathImage;
    char *search = strstr(buffer, "/");
    if (search == NULL) {
        char *format = strstr(buffer, ".");
        if (format == NULL) {
            perror("probleme de format");
            return NULL;
        }
        char *name = strndup(buffer, strlen(buffer) - strlen(format));

        myStruct->id = 1;
        myStruct->path = "";
        myStruct->name = name;
        myStruct->format = format + 1;
        myStruct->next = NULL;

    } else {
        char *pred = NULL;
        while (search != NULL) {
            pred = strndup(search, strlen(search));
            search = strstr(search + 1, "/");
        }
        if (pred == NULL) {
            perror("erreur dans boucle");
            return NULL;
        }
        char *format = strstr(pred, ".");
        if (format == NULL) {
            perror("probleme de format");
            return NULL;
        }
        char *name = strndup(pred, strlen(pred) - strlen(format));

        myStruct->id = 1;
        myStruct->path = strndup(pathImage, strlen(pathImage) - strlen(pred));
        myStruct->name = name + 1;
        myStruct->format = format + 1;
        myStruct->next = NULL;
    }
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

