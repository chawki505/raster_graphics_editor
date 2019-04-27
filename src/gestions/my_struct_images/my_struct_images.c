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

    if (myStruct->sprite == NULL) {
        fprintf(stderr, "ERROR: load image\n");
        free(myStruct);
        return NULL;
    }

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


    if (myStruct->sprite == NULL) {
        fprintf(stderr, "ERROR: load image\n");
        free(myStruct);
        return NULL;
    }

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

    if (liste == NULL) {
        return;
    }

    if (id == 1 && liste->next == NULL) {
        my_images = NULL;
        return;
    }
    int cpt = 1;
    while (liste->next != NULL) {
        liste = liste->next;
        cpt++;
    }
    if (cpt < id) {
        perror("L'id n'est pas présent dans la liste d'images chargées");
        return;
    }

    if (id == 1) {
        my_images = my_images->next;
        liste = my_images;
        int i = 1;
        while (liste != NULL) {
            liste->id = i;
            i++;
            liste = liste->next;
        }
    } else {
        liste = my_images;
        while (liste->next->id != id) {
            liste = liste->next;
        }
        tmp = liste->next;
        liste->next = tmp->next;
        liste = liste->next;
        while (liste != NULL) {
            liste->id = liste->id-1;
            liste = liste->next;
        }
    }


}