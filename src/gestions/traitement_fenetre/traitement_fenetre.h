//
// Created by chawki on 20/02/19.
//

#ifndef GRAPHICS_EDITOR_TRAITEMENT_FENETRE_H
#define GRAPHICS_EDITOR_TRAITEMENT_FENETRE_H



//Screen dimension constants
#define  SCREEN_WIDTH 900
#define  SCREEN_HEIGHT 600


typedef struct LWindow {
    //Window data
    SDL_Window *mWindow;
    SDL_Surface *mSurface;
    SDL_Surface *mcurrent_surface;
    int mWindowID;

    //Window dimensions
    int mWidth;
    int mHeight;

    //Window focus
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mMinimized;
    bool mShown;

} LWindow;


//Intializes internals
void init_value_LWindow(LWindow *);

//Creates window
bool init_LWindow(LWindow *, SDL_Surface *);

//Handles window events
void handleEvent_LWindow(LWindow *, SDL_Event *);


//Shows windows contents
void render_LWindow(LWindow *);

//Deallocates internals
void free_LWindow(LWindow *);

#endif //GRAPHICS_EDITOR_TRAITEMENT_FENETRE_H
