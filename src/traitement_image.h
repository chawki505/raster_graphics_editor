//
// Created by chawki on 15/02/19.
//

#ifndef RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
#define RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H


void print_image_bmp_type(SDL_Window *pWindow, char *path_image);

void print_image_other_type(SDL_Window *pWindow, char *path_image, int type_image);

void open_image(char *path_image);

void print_image(int id);

Uint32 getPixel(SDL_Surface *surface, int x, int y);

void getPixelColor(SDL_Surface *surface, int x, int y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);

void setPixelColor(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif //RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
