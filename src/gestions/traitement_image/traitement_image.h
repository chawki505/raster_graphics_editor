//
// Created by chawki on 15/02/19.
//

#ifndef RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
#define RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H


int load_image(char *path_image);

int save_image(int id, char *path, char *type);

int symh_image(int id);

int symv_image(int id);

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

int drawzone(int id, int ox, int oy, int fx, int fy);

int rotation(int id);

SDL_Surface *resize_image(SDL_Surface *image, Uint16 w, Uint16 h);

int errorzone(int ox, int oy, int fx, int fy, int wmax, int hmax);

int resize(int id, int w, int h);

int errorcolor(int r, int g, int b);

int run_display(int *tab_id_images, int sizetab);

#endif //RASTER_GRAPHICS_EDITOR_TRAITEMENT_IMAGE_H
