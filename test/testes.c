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


void test_init_sdl() {

    //DEBUT TEST

    fprintf(stdout, "TEST Init sdl : ");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stdout, "NOT OK\n");
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!\n");
        }
        fprintf(stdout, "OK\n");

        //FIN TEST
        SDL_Quit();
    }
}


void test_create_structe() {

    fprintf(stdout, "TEST create struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_bmp_format("../img/image.bmp", "image.bmp", "image.bm");

    if (tmp_struct != NULL) {
        fprintf(stdout, "OK\n");
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else
        fprintf(stdout, "NOT OK\n");


    SDL_Quit();

}