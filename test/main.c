//
// Created by chawki on 15/04/19.
//
#include <stdio.h>

#include "testes.h"

int mode_test;

int main() {
    mode_test = 1;

    printf("\n--------------------TEST--------------------\n");
    test_init_sdl();
    printf("--------------------FIN TEST--------------------\n");

    printf("\n--------------------TEST--------------------\n");
    test_parser();
    printf("--------------------FIN TEST--------------------\n");

    printf("\n--------------------TEST--------------------\n");
    test_error_couleur();
    printf("--------------------FIN TEST--------------------\n");

    printf("\n--------------------TEST--------------------\n");
    test_error_zone();
    printf("--------------------FIN TEST--------------------\n");

    printf("\n--------------------TEST--------------------\n");
    test_create_structe_valide_bmp();
    test_create_structe_not_valide_bmp();
    test_create_structe_valide_png();
    test_create_structe_not_valide_png();
    test_create_structe_valide_jpg();
    test_create_structe_not_valide_jpg();
    printf("--------------------FIN TEST--------------------\n");

    printf("\n--------------------TEST--------------------\n");

    test_load_image();

    test_load_image_incorrect_format();

    test_symh();

    test_symv();

    test_rotation();
    printf("--------------------FIN TEST--------------------\n");
    return 0;
}
