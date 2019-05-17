//
// Created by chawki on 20/02/19.
//

#include "../../includes.h"
#include "../traitement_image/traitement_image.h"

#include "traitement_fenetre.h"

extern int mode_test;


void init_value_LWindow(LWindow *window) {
    //Initialize non-existant window
    window->mWindow = NULL;
    window->mMouseFocus = false;
    window->mKeyboardFocus = false;
    window->mShown = false;
    window->mWindowID = -1;
    window->mWidth = 0;
    window->mHeight = 0;
}

SDL_Surface *copie_surface(SDL_Surface *surface_a_copier) {

    SDL_Surface *surface_copiee = NULL;
    surface_copiee = SDL_CreateRGBSurface(0, surface_a_copier->w, surface_a_copier->h,
                                          surface_a_copier->format->BitsPerPixel, surface_a_copier->format->Rmask,
                                          surface_a_copier->format->Gmask, surface_a_copier->format->Bmask,
                                          surface_a_copier->format->Amask);

    if (surface_copiee == NULL)
        return NULL;

    SDL_FreeSurface(surface_copiee); // pour libérer la surface
    surface_copiee = NULL;

    return SDL_ConvertSurfaceFormat(surface_a_copier, SDL_PIXELFORMAT_RGBA8888, 0);
}

//init window
bool init_LWindow(LWindow *window, SDL_Surface *surface) {

    window->mMouseFocus = true;
    window->mKeyboardFocus = true;
    window->mWidth = SCREEN_WIDTH;
    window->mHeight = SCREEN_HEIGHT;
    window->mWindow = SDL_CreateWindow("SDL programme", // window title
                                       SDL_WINDOWPOS_CENTERED, // initial X position
                                       SDL_WINDOWPOS_CENTERED, // initial y position
                                       window->mWidth, // width, in pixels
                                       window->mHeight, // height, in pixels
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE // flags
    );

    //Erreur create window
    if (!window->mWindow) {
        if (mode_test == 0)SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
        return false;
    }


    //window->mSurface = surface;
    window->mSurface = copie_surface(surface);
    window->mcurrent_surface = resize_image(window->mSurface, (Uint16) window->mWidth, (Uint16) window->mHeight);

    //erreur create surface
    if (!window->mSurface) {
        if (mode_test == 0)SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load surface: %s", SDL_GetError());
        return false;
    }


    //Grab window identifier
    window->mWindowID = SDL_GetWindowID(window->mWindow);

    //Flag as opened
    window->mShown = true;


    return window->mWindow != NULL && window->mSurface != NULL;
}


void handleEvent_LWindow(LWindow *window, SDL_Event *event) {
//If an event was detected for this window
    if (event->type == SDL_WINDOWEVENT && event->window.windowID == window->mWindowID) {
        //Caption update flag
        bool updateCaption = false;

        switch (event->window.event) {
            //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
                window->mShown = true;
                break;

                //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
                window->mShown = false;
                break;

                //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                window->mWidth = event->window.data1;
                window->mHeight = event->window.data2;
                window->mcurrent_surface = resize_image(window->mSurface, (Uint16) window->mWidth,
                                                        (Uint16) window->mHeight);
                break;

                //Repaint on expose
            case SDL_WINDOWEVENT_EXPOSED:
                break;

                //Mouse enter
            case SDL_WINDOWEVENT_ENTER:
                window->mMouseFocus = true;
                updateCaption = true;
                break;

                //Mouse exit
            case SDL_WINDOWEVENT_LEAVE:
                window->mMouseFocus = false;
                updateCaption = true;
                break;

                //Keyboard focus gained
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                window->mKeyboardFocus = true;
                updateCaption = true;
                break;

                //Keyboard focus lost
            case SDL_WINDOWEVENT_FOCUS_LOST:
                window->mKeyboardFocus = false;
                updateCaption = true;
                break;

                //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
                window->mMinimized = true;
                break;

                //Window maxized
            case SDL_WINDOWEVENT_MAXIMIZED:
                window->mMinimized = false;
                break;

                //Window restored
            case SDL_WINDOWEVENT_RESTORED:
                window->mMinimized = false;
                break;

                //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow(window->mWindow);
                break;
        }

        //Update window caption with new data
        if (updateCaption) {
            char buf[100];
            sprintf(buf,
                    "SDL Window - ID: [%d] "
                    "MouseFocus: [%s] "
                    "KeyboardFocus: [%s]",
                    window->mWindowID,
                    (window->mMouseFocus) ? "On" : "Off",
                    (window->mKeyboardFocus) ? "On" : "Off"
            );
            SDL_SetWindowTitle(window->mWindow, buf);
        }
    }
}


void render_LWindow(LWindow *window) {
    if (!window->mMinimized) {

        SDL_Surface *surface_window = SDL_GetWindowSurface(window->mWindow);

        int w, h;

        SDL_GetWindowSize(window->mWindow, &w, &h);

        SDL_Rect dest = {w / 2 - window->mcurrent_surface->w / 2, // the x location of the rectangle's upper left corner
                         h / 2 - window->mcurrent_surface->h / 2, // the y location of the rectangle's upper left corner
                         0, // the width of the rectangle
                         0}; // the height of the rectangle

        SDL_BlitSurface(window->mcurrent_surface, NULL, surface_window, &dest); // Copie du sprite
        // Mise à jour de la fenêtre pour prendre en compte la copie du sprite
        SDL_UpdateWindowSurface(window->mWindow);
    }
}


void free_LWindow(LWindow *window) {
    if (window->mWindow != NULL) {
        SDL_FreeSurface(window->mSurface);
        SDL_FreeSurface(window->mcurrent_surface);
        SDL_DestroyWindow(window->mWindow);
    }

    window->mWindow = NULL;
    window->mWindowID = -1;
    window->mMouseFocus = false;
    window->mKeyboardFocus = false;
    window->mShown = false;
    window->mWidth = 0;
    window->mHeight = 0;
}






