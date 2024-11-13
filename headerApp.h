#define APP_HEADER

#include "includes.h"

#define resolution_w 800
#define resolution_h 600
// estruturas de dados 
typedef struct APP APP;

struct APP{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* bufferSurface;
    SDL_Texture* screenTexture;
    SDL_Rect *rectScreen;
    TTF_Font* defaultFont;
};

// funções
int initApp(APP* currentApp);

void closeApp(APP* appParam);