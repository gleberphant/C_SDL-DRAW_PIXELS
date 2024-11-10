#include "includes.h"

typedef struct APP APP;
typedef struct PIXEL PIXEL;
typedef struct NODE NODE;

struct APP{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* bufferSurface;
    SDL_Texture* screenTexture;
    SDL_Rect rectScreen;
};

struct PIXEL{
    float posX, posY;
    float colorRed, colorBlue,colorGreen;
};

struct NODE{
    int value;
    struct NODE* next;
};


int initApp(APP* appParam){
    // inicialização do SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("não foi possível iniciar o SDL");
        return 1;
    }

    //criação da janela
    appParam->window = SDL_CreateWindow(
        "titulo",
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        800, 600, 
        0
    );
    
    if( appParam->window == NULL){
        printf("Erro inesperado na criação da janela");
        SDL_Quit();
        return 1;
    }

    //criar renderer
    appParam->renderer = SDL_CreateRenderer(
        appParam->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if( appParam->renderer == NULL){
        printf("Erro inesperado na criação do renderer");
        SDL_DestroyWindow(appParam->window);
        SDL_Quit();
        return 1;
    } 
    
    appParam->bufferSurface = SDL_CreateRGBSurface(0,800,600,32,0,0,0,255);    
    if(appParam->bufferSurface == NULL){
        printf("ERRO inesperado na criação do buffer da tela");
        SDL_DestroyRenderer(appParam->renderer);
        SDL_DestroyWindow(appParam->window);
        SDL_Quit();
    }

    
    appParam->rectScreen.h = appParam->bufferSurface->h;
    appParam->rectScreen.w = appParam->bufferSurface->w;
    appParam->rectScreen.x = 0;
    appParam->rectScreen.y = 0;

    SDL_FillRect(appParam->bufferSurface, &appParam->rectScreen, SDL_MapRGB(appParam->bufferSurface->format, 255, 255, 255));

    // tudo ok retorne 0
    return 0;

}


void closeApp(APP* appParam){
    SDL_FreeSurface(appParam->bufferSurface);
    SDL_DestroyTexture(appParam->screenTexture);
    SDL_DestroyRenderer(appParam->renderer);
    SDL_DestroyWindow(appParam->window);
}