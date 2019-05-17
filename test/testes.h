//
// Created by chawki on 16/05/19.
//

#ifndef GRAPHICS_EDITOR_TESTES_H
#define GRAPHICS_EDITOR_TESTES_H


void test_init_sdl();

void test_create_structe_valide_bmp();

void test_create_structe_not_valide_bmp();

void test_create_structe_valide_png();

void test_create_structe_not_valide_png();

void test_create_structe_valide_jpg();

void test_create_structe_not_valide_jpg();

int test_parser_0(char *buf);

int test_parser_1(char *buf);

void test_parser();

void test_error_couleur();

void test_error_zone();

void test_load_image();

void test_load_image_incorrect_format();

void test_symh();

void test_symv();

void test_rotation();

#endif //GRAPHICS_EDITOR_TESTES_H
