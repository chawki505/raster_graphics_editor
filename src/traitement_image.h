//
// Created by chawki on 15/02/19.
//

#ifndef RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
#define RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H


void print_image_bmp_type(SDL_Window *pWindow, char *path_image);

void print_image_other_type(SDL_Window *pWindow, char *path_image, int type_image);

void open_image(char *path_image);

void print_image(int id);

void rotation_image(int id);


#endif //RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
