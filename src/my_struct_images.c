//
// Created by chawki on 22/02/19.
//

#include "my_struct_images.h"


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
        myStruct->imageName = name;
        myStruct->imageType = format + 1;
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
        myStruct->imageName = name + 1;
        myStruct->imageType = format + 1;
        myStruct->next = NULL;

    }
    return myStruct;

}

void printStruct(structImage *myStruct) {
    printf("%d\n%s\n%s\n%s", myStruct->id, myStruct->path, myStruct->imageType, myStruct->imageName);
}
