
#include "headerScene.h"

// variavies
ACTIONS actionGlobal = NOTHING;
APP* current_app = NULL;
BOOLEAN running = TRUE;    
SDL_Event event;

// funções
ACTIONS handleEvents(){
    
    while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_EVENT_QUIT)
        {
            return QUIT;
        }

        if (event.type == SDL_EVENT_KEY_UP)
        {
            if( event.key.key == SDLK_ESCAPE){
                return QUIT;
            }

        }
        

        if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            return DRAW;
        }

        if(event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        {
            return WAIT;
        }

    }

    return actionGlobal;    

}


BOOLEAN updateStatus(){
    float mousePosX, mousePosY;

    switch(actionGlobal){
        case QUIT:
            running = FALSE;
            return TRUE;

        case DRAW:
            
            SDL_GetMouseState(&mousePosX, &mousePosY);

            SDL_LockSurface(current_app->bufferSurface);
            
            Uint32* bufferPixels = current_app->bufferSurface->pixels;
            Uint32 pixelColored =  SDL_MapSurfaceRGB(current_app->bufferSurface, 0,0,0);

            for(int i = -2; i <3 ; i++){
                for(int j = -2; j <3 ; j++){

                    bufferPixels[(((int)mousePosY+i)*800) + ((int)mousePosX+j)] = pixelColored;
                    
                }
            }
            
            SDL_UnlockSurface(current_app->bufferSurface);
            
            return TRUE;

        case WAIT:
            return FALSE;
        
        case NOTHING:
            return FALSE;
    }
    
    return FALSE;
}

void drawScreen(){
    
    current_app->screenTexture = SDL_CreateTextureFromSurface( current_app->renderer, current_app->bufferSurface );
    SDL_RenderTexture(current_app->renderer,current_app->screenTexture, (SDL_FRect *) current_app->rectScreen, (SDL_FRect *)current_app->rectScreen);
    
    SDL_RenderPresent(current_app->renderer);
    SDL_DestroyTexture(current_app->screenTexture);
}


void sceneLoop(){

    
    
    while(running == TRUE) {
        
        actionGlobal = handleEvents();
        
        if(updateStatus() == TRUE){
            drawScreen();
        }
    }

}

void setApp(APP* appParam){
    current_app = appParam;
}