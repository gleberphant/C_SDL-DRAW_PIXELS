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
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("[ %s ] \n\n", SDL_GetError());
        return 1;
    }
    printf(" [OK] ");

    //criação da janela
    printf("\n. SDL_CreateWindow ............");
    appParam->window = SDL_CreateWindow("DRAW PIXELS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    
    if( appParam->window == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    printf(" [OK] ");

    //criar renderer
    printf("\n. SDL_CreateRenderer ..........");
    appParam->renderer = SDL_CreateRenderer(appParam->window, -1, SDL_RENDERER_ACCELERATED);

    if( appParam->renderer == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_DestroyWindow(appParam->window);
        SDL_Quit();
        return 1;
    } 

    printf(" [OK] ");

    //criar BUFFER SURFACE
    printf("\n. SDL_CreateRGBSurface ........");
    appParam->bufferSurface = SDL_CreateRGBSurface(0,800,600,32,0,0,0,255);    
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
    
    SDL_GetClipRect(appParam->bufferSurface, appParam->rectScreen);

    printf(" [OK] ");

    // Limpando o buffer
    printf("\n. SDL_LockSurface  ............");

    SDL_LockSurface(appParam->bufferSurface);
    
    Uint32* bufferPixels = appParam->bufferSurface->pixels;
  
    Uint32 pixelEmpty = SDL_MapRGB( appParam->bufferSurface->format, 255, 255, 255);

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
    SDL_FreeSurface(appParam->bufferSurface);
    SDL_DestroyTexture(appParam->screenTexture);
    SDL_DestroyRenderer(appParam->renderer);
    SDL_DestroyWindow(appParam->window);
    SDL_Quit();
}