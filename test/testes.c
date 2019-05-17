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


void print_ok() {
    green();
    fprintf(stdout, "OK\n");
    reset();
}

void print_ko() {
    red();
    fprintf(stdout, "KO\n");
    reset();
}

//test si la lib sdl est active
void test_init_sdl() {
    //DEBUT TEST

    fprintf(stdout, "TEST Init sdl : ");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        print_ko();
    } else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            yellow();
            printf("Warning: Linear texture filtering not enabled!\n");
            reset();
        }
        print_ok();

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
        print_ok();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        print_ko();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image bmp
void test_create_structe_not_valide_bmp() {

    fprintf(stdout, "TEST create note valide struct image bmp image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_bmp_format("xxxxxx", "xxxxxx", "xxxxxx");

    if (tmp_struct == NULL) {
        print_ok();
    } else {
        print_ko();
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
        print_ok();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        print_ko();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image png
void test_create_structe_not_valide_png() {

    fprintf(stdout, "TEST create note valide struct image png image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("xxxxxx", "xxxxxx", "xxxxxx", IMG_INIT_PNG);

    if (tmp_struct == NULL) {
        print_ok();
    } else {
        print_ko();
        free(tmp_struct);
    }
    SDL_Quit();
}

// teste la creation d'une structure d'une image jpg
void test_create_structe_valide_jpg() {

    fprintf(stdout, "TEST create valide struct image jpg image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("../img/image.jpg", "xxxxxx", "xxxxxx", IMG_INIT_JPG);

    if (tmp_struct != NULL) {
        print_ok();
        SDL_FreeSurface(tmp_struct->sprite);
        free(tmp_struct);
    } else {
        print_ko();
    }

    SDL_Quit();
}

// teste la creation d'une fausse structure d'une image jpg
void test_create_structe_not_valide_jpg() {

    fprintf(stdout, "TEST create note valide struct image jpg image : ");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    structImage *tmp_struct = createStruct_other_format("xxxxxx", "xxxxxx", "xxxxxx", IMG_INIT_JPG);

    if (tmp_struct == NULL) {
        print_ok();
    } else {
        print_ko();
        free(tmp_struct);
    }
    SDL_Quit();
}

int test_parser_0(char *buf) {
    printf("TEST avec '%s' : ", buf);
    if (traitement_ligne(buf) == 0) {
        print_ok();
        return 1;
    } else {
        print_ko();
        return 0;

    }
}

int test_parser_1(char *buf) {
    printf("TEST avec '%s' : ", buf);
    if (traitement_ligne(buf) == 1) {
        print_ok();
        return 1;
    } else {
        print_ko();
        return 0;
    }
}

void test_parser() {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    char buf1[50] = "";
    char buf2[50] = "load";
    char buf3[50] = "load test";
    char buf4[50] = "delete test test";
    char buf5[50] = "delete test";
    char buf6[50] = "show";
    char buf7[50] = "display";
    char buf8[50] = "display 1 1";
    char buf9[120] = "display 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
    char buf10[50] = "save";
    char buf11[50] = "save test";
    char buf12[50] = "symv";
    char buf13[50] = "symv test";
    char buf14[50] = "symh";
    char buf15[50] = "symh test";
    char buf16[50] = "select";
    char buf17[50] = "drawzone";
    char buf18[50] = "drawzone test test test test test";
    char buf19[50] = "rotate";
    char buf20[50] = "rotate test test";
    char buf21[50] = "resize";
    char buf22[50] = "resize test test test";
    char buf23[50] = "fhkjsh fbsqdfjb fsbdefbfj";

    int cpt = 0;

    cpt += test_parser_1(buf1);
    cpt += test_parser_1(buf2);
    cpt += test_parser_0(buf3);
    cpt += test_parser_1(buf4);
    cpt += test_parser_0(buf5);
    cpt += test_parser_0(buf6);
    cpt += test_parser_1(buf7);
    cpt += test_parser_0(buf8);
    cpt += test_parser_0(buf9);
    cpt += test_parser_1(buf10);
    cpt += test_parser_0(buf11);
    cpt += test_parser_1(buf12);
    cpt += test_parser_0(buf13);
    cpt += test_parser_1(buf14);
    cpt += test_parser_0(buf15);
    cpt += test_parser_1(buf16);
    cpt += test_parser_1(buf17);
    cpt += test_parser_0(buf18);
    cpt += test_parser_1(buf19);
    cpt += test_parser_0(buf20);
    cpt += test_parser_1(buf21);
    cpt += test_parser_0(buf22);
    cpt += test_parser_1(buf23);

    printf("\nScore pour test_parser: \033[1;33m%d\033[0m / 23\n", cpt);

    SDL_Quit();
}

void test_error_couleur() {
    int tab[3] = {-25, 300, 158};
    int cpt = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                cpt += errorcolor(tab[i], tab[j], tab[k]);
            }
        }
    }
    printf("Score pour test_error_couleur: \033[1;33m%d\033[0m / 27\n", cpt);

}

void test_error_zone() {
    char good_test[4096][100];
    int cpt = 0;
    int tab[4] = {-1, 5, 10, 15};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                for (int l = 0; l < 4; ++l) {
                    for (int m = 0; m < 4; ++m) {
                        for (int n = 0; n < 4; ++n) {
                            if (errorzone(tab[i], tab[j], tab[k], tab[l], tab[m], tab[n]) == 0) {
                                sprintf(good_test[cpt],
                                        "Avec debut->%dx%d \tfin->%dx%d \tmax->%dx%d \t: \033[1;32m OK \033[0m\n",
                                        tab[i], tab[j], tab[k], tab[l], tab[m], tab[n]);
                                cpt++;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i1 = 0; i1 < cpt; ++i1) {
        printf("%s", good_test[i1]);
    }
}