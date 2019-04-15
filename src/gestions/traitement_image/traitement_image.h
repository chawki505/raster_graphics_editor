//
// Created by chawki on 15/02/19.
//

#ifndef RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
#define RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H

#include "../../includes.h"


void load_image(char *path_image);

void display_image(int id);

void save_image(int id);

void rotation_image(int id);

void symh_image(int id);

void symv_image(int id);

Uint32 getPixel(SDL_Surface *surface, int x, int y);

void getPixelColor(SDL_Surface *surface, int x, int y, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);

void setPixelColor(SDL_Surface *surface, int x, int y, Uint32 pixel);

void greyColor(SDL_Surface *surface, int ox, int oy, int fx, int fy);

void negatifColor(SDL_Surface *surface, int ox, int oy, int fx, int fy);

void blackAndWhiteColor(SDL_Surface *surface, int ox, int oy, int fx, int fy);

void switchColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int t, int sr, int sg, int sb, int nr, int ng,
                 int nb);

void fillColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int nr, int ng, int nb);

void copyAndPasteColor(SDL_Surface *surface, int ox, int oy, int fx, int fy, int nx, int ny);

void selectRegion(int id);

void drawzone(int id);

void rotation(int id);

int errorzone(int ox, int oy, int fx, int fy, int wmax, int hmax);

int errorcolor(int r, int g, int b);

#endif //RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
