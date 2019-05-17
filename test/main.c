//
// Created by chawki on 15/04/19.
//
#include <stdio.h>

#include "testes.h"


int main() {
    printf("file test \n");

    test_init_sdl();

    test_parser();

    test_error_couleur();

    test_error_zone();

    test_create_structe_valide_bmp();

    test_create_structe_not_valide_bmp();

    test_create_structe_valide_png();

    test_create_structe_not_valide_png();

    test_create_structe_valide_jpg();

    test_create_structe_not_valide_jpg();

    return 0;
}