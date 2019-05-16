//
// Created by chawki on 16/05/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "../src/parsing/parsing.h"
#include "../src/gestions/my_struct_images/my_struct_images.h"
#include "../src/gestions/traitement_fenetre/traitement_fenetre.h"
#include "../src/gestions/traitement_image/traitement_image.h"


#include "testes.h"


//set color red in output
void red() {
    printf("\033[1;31m");
}

//set color green in output
void green() {
    printf("\033[1;32m");
}

//set color yellow in output
void yellow() {
    printf("\033[1;33m");
}

//reset default color
void reset() {
    printf("\033[0m");
}

//test si la lib sdl est active
void test_init_sdl() {
    //DEBUT TEST

    fprintf(stdout, "TEST Init sdl : ");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            yellow();
            printf("Warning: Linear texture filtering not enabled!\n");
            reset();
        }
        green();
        fprintf(stdout, "OK\n");
        reset();

        //FIN TEST
        SDL_Quit();
    }
}

// teste la creation d'une structure d'une image bmp
void test_create_structe_valide_bmp() {

    fprintf(stdout, "TEST create valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_bmp_format("../img/image.bmp", "xxxxxx", "xxxxxx");

    if (tmp_struct != NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image bmp
void test_create_structe_not_valide_bmp() {

    fprintf(stdout, "TEST create note valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_bmp_format("xxxxxx", "xxxxxx", "xxxxxx");

    if (tmp_struct == NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
        free(tmp_struct);
    }
    SDL_Quit();
}

// teste la creation d'une structure d'une image png
void test_create_structe_valide_png() {

    fprintf(stdout, "TEST create valide struct image png image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("../img/image.png", "xxxxxx", "xxxxxx", IMG_INIT_PNG);

    if (tmp_struct != NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image png
void test_create_structe_not_valide_png() {

    fprintf(stdout, "TEST create note valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("xxxxxx", "xxxxxx", "xxxxxx", IMG_INIT_PNG);

    if (tmp_struct == NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
        free(tmp_struct);
    }
    SDL_Quit();
}

// teste la creation d'une structure d'une image jpg
void test_create_structe_valide_jpg() {

    fprintf(stdout, "TEST create valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("../img/image.jpg", "xxxxxx", "xxxxxx", IMG_INIT_JPG);

    if (tmp_struct != NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image jpg
void test_create_structe_not_valide_jpg() {

    fprintf(stdout, "TEST create note valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("xxxxxx", "xxxxxx", "xxxxxx", IMG_INIT_JPG);

    if (tmp_struct == NULL) {
        green();
        fprintf(stdout, "OK\n");
        reset();
    } else {
        red();
        fprintf(stdout, "NOT OK\n");
        reset();
        free(tmp_struct);
    }
    SDL_Quit();
}