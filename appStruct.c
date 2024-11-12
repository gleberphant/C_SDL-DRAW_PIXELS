#include "includes.h"

typedef struct APP APP;


struct APP{
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* bufferSurface;
    SDL_Texture* screenTexture;
    SDL_Rect* rectScreen;
    TTF_Font* defaultFont;
};

int initApp(APP* appParam){
    
    printf("\n ..................................");
    
    // inicialização do SDL
    printf("\n. SDL_Init ....................");
    
    if(!SDL_Init(SDL_INIT_VIDEO)){
        printf("[ %s ] \n\n", SDL_GetError());
        return 1;
    }
    printf(" [OK] ");

    //criação da janela
    printf("\n. SDL_CreateWindow ............");
    appParam->window = SDL_CreateWindow("DRAW PIXELS", 800, 600, 0);
    
    if( appParam->window == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf(" [OK] ");

    //criar renderer
    printf("\n. SDL_CreateRenderer ..........");
    appParam->renderer = SDL_CreateRenderer(appParam->window, NULL);

    if( appParam->renderer == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_DestroyWindow(appParam->window);
        SDL_Quit();
        return 1;
    } 

    printf(" [OK] ");

    //criar BUFFER SURFACE
    printf("\n. SDL_CreateRGBSurface ........");
    
    appParam->bufferSurface = SDL_CreateSurface(800,600, SDL_PIXELFORMAT_RGBA32); 

    if(appParam->bufferSurface == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_DestroyRenderer(appParam->renderer);
        SDL_DestroyWindow(appParam->window);
        SDL_Quit();
        return 1;
    }

    printf(" [OK] ");

    // definir tamanho da tela
    printf("\n. SDL_GetClipRect rectScreen ..");
    
    SDL_GetSurfaceClipRect(appParam->bufferSurface, appParam->rectScreen);

    printf(" [OK] ");

    // Limpando o buffer
    printf("\n. SDL_LockSurface  ............");

    SDL_LockSurface(appParam->bufferSurface);
    
    Uint32* bufferPixels = appParam->bufferSurface->pixels;
  
    Uint32 pixelEmpty = SDL_MapSurfaceRGB( appParam->bufferSurface, 255, 255, 255);

    for(int i = 0 ; i < (appParam->bufferSurface->h * appParam->bufferSurface->w)-1; i++){
        
        bufferPixels[i] = pixelEmpty;

    }
    SDL_UnlockSurface(appParam->bufferSurface);
    printf(" [OK] ");
    
    // tudo ok retorne 0
    printf("\n ..................................");
    printf("\n");
    return 0;

}


void closeApp(APP* appParam){
    SDL_DestroySurface(appParam->bufferSurface);
    SDL_DestroyTexture(appParam->screenTexture);
    SDL_DestroyRenderer(appParam->renderer);
    SDL_DestroyWindow(appParam->window);
    SDL_Quit();
}