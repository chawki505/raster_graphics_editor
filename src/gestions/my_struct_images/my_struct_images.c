//
// Created by chawki on 22/02/19.
//

#include "../../includes.h"

#include "my_struct_images.h"

extern int mode_test;

//fonction qui cree une structure de type png ou jpg
structImage *createStruct_other_format(char *path, char *name, char *format, int type_image) {
    structImage *myStruct = malloc(sizeof(structImage));

    if (myStruct == NULL) {
        if (mode_test == 0)perror("promblème allocation image struct\n");
        return NULL;
    }

    IMG_Init(type_image);//init SDL_image
    init_value_struct(path, name, format, myStruct);
    myStruct->sprite = IMG_Load(path); //load other format image

    if (myStruct->sprite == NULL) {
        if (mode_test == 0)fprintf(stderr, "ERROR: load image\n");
        free(myStruct);
        return NULL;
    }

    return myStruct;
}

//fonction qui cree une structure de type bmp
structImage *createStruct_bmp_format(char *path, char *name, char *format) {
    structImage *myStruct = malloc(sizeof(structImage));

    if (myStruct == NULL) {
        if (mode_test == 0)perror("promblème allocation image struct\n");
        return NULL;
    }

    init_value_struct(path, name, format, myStruct);

    myStruct->sprite = SDL_LoadBMP(path); //load bitmap image


    if (myStruct->sprite == NULL) {
        if (mode_test == 0)fprintf(stderr, "ERROR: load image\n");
        free(myStruct);
        return NULL;
    }

    return myStruct;
}

//fonction init valeure structure
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
            if (liste->id == 1)compteur = 2;
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

//afficher les données d'une structure
void print_struct(structImage *myStruct) {
    printf("ID:%d\t\tPATH:%s\t\tFORMAT:%s\t\tNAME:%s\n", myStruct->id, myStruct->path, myStruct->format,
           myStruct->name);
}

//affiche la liste des images chargé
void print_list_image() {
    structImage *liste = my_images;

    while (liste != NULL) {
        print_struct(liste);
        liste = liste->next;
    }
}

//suprimme une image de la liste
int delete_image(int id) {
    structImage *liste = my_images;
    structImage *tmp = NULL;

    if (liste == NULL || id == 0) {
        if (mode_test == 0)
            fprintf(stdout, "L'id (%d) n'est pas présent dans la liste d'images chargées ou id faux ou liste vide\n",
                    id);
        return 1;
    }

    if (id == 1 && liste->next == NULL) {
        SDL_FreeSurface(liste->sprite);
        free(liste);
        my_images = NULL;

        if (mode_test == 0)fprintf(stdout, "image suprimer !\n");
        return 0;
    }

    int cpt = 1;

    while (liste->next != NULL) {
        liste = liste->next;
        cpt++;
    }

    if (cpt < id) {
        if (mode_test == 0)fprintf(stdout, "L'id (%d) n'est pas présent dans la liste d'images chargées\n", id);
        return 1;
    }

    if (id == 1) {
        liste = my_images;
        SDL_FreeSurface(liste->sprite);
        free(liste);
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
            liste->id = liste->id - 1;
            liste = liste->next;
        }

        SDL_FreeSurface(tmp->sprite);
        free(tmp);
    }
    if (mode_test == 0)fprintf(stdout, "image suprimer !\n");
    return 0;
}