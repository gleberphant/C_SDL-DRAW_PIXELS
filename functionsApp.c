#include "headerApp.h"

int initApp(APP* currentApp){
    
    printf("\n ...................................");
    
    // inicialização do SDL
    printf("\n. SDL3_Init ....................");
    
    if(!SDL_Init(SDL_INIT_VIDEO)){
        printf("[ %s ] \n\n", SDL_GetError());
        return 1;
    }

    printf(" [OK] ");

    // criação da janela
    printf("\n. SDL3_CreateWindow ............");
    
    currentApp->window = SDL_CreateWindow(
        "DRAW PIXELS - by Gr4v4t1nh4", 
        resolution_w, 
        resolution_h, 
        0
    );
    
    if( currentApp->window == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    printf(" [OK] ");

    //criar renderer
    printf("\n. SDL3_CreateRenderer ..........");
    currentApp->renderer = SDL_CreateRenderer(currentApp->window, NULL);

    if( currentApp->renderer == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_DestroyWindow(currentApp->window);
        SDL_Quit();
        return 1;
    } 

    printf(" [OK] ");

    //criar BUFFER SURFACE
    printf("\n. SDL3_CreateRGBSurface ........");
    
    currentApp->bufferSurface = SDL_CreateSurface(
        800,
        600, 
        SDL_PIXELFORMAT_RGBA32
    ); 

    if(currentApp->bufferSurface == NULL){
        printf("[ %s ] \n\n", SDL_GetError());
        SDL_DestroyRenderer(currentApp->renderer);
        SDL_DestroyWindow(currentApp->window);
        SDL_Quit();
        return 1;
    }

    printf(" [OK] ");

    // definir tamanho da tela
    printf("\n. SDL3_GetClipRect rectScreen ..");
    
    SDL_GetSurfaceClipRect(currentApp->bufferSurface, currentApp->rectScreen);

    printf(" [OK] ");

    // Limpando o buffer
    printf("\n. SDL3_ClearSurface  ...........");

    SDL_LockSurface(currentApp->bufferSurface);
    
    Uint32* bufferPixels = currentApp->bufferSurface->pixels;
    Uint32 pixelEmpty = SDL_MapSurfaceRGB( currentApp->bufferSurface, 255, 255, 255);

    for(int i = 0 ; i < (currentApp->bufferSurface->h * currentApp->bufferSurface->w)-1; i++){
        
        bufferPixels[i] = pixelEmpty;

    }

    SDL_UnlockSurface(currentApp->bufferSurface);
    
    printf(" [OK] ");

    // Criando textura para desenhar na tela
    printf("\n. SDL_CreateTextureFromSurface .");
    currentApp->screenTexture = SDL_CreateTextureFromSurface(
        currentApp->renderer, 
        currentApp->bufferSurface 
    );
    
    SDL_RenderTexture(
        currentApp->renderer, 
        currentApp->screenTexture, 
        (SDL_FRect *) currentApp->rectScreen, 
        (SDL_FRect *) currentApp->rectScreen
    );
    
    SDL_RenderPresent(currentApp->renderer);
    
    SDL_DestroyTexture(currentApp->screenTexture);
    
    printf(" [OK] ");
    
    // tudo ok retorne 0
    printf("\n ...................................");
    printf("\n");

    

    return 0;

}


void closeApp(APP* currentApp){
    SDL_DestroySurface(currentApp->bufferSurface);
    SDL_DestroyTexture(currentApp->screenTexture);
    SDL_DestroyRenderer(currentApp->renderer);
    SDL_DestroyWindow(currentApp->window);
    SDL_Quit();
}