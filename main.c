#include <stdio.h>
#include "functions.c"



typedef enum BOOLEAN BOOLEAN;

enum BOOLEAN{
  TRUE = true,
  FALSE = false
};

typedef enum ACTIONS ACTIONS;

enum ACTIONS{
  QUIT,
  DRAW,
  WAIT,
  NOTHING
};

APP myApp;
ACTIONS actionGlobal = NOTHING;


ACTIONS handleEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_QUIT)
        {
            return QUIT;
        }

        if (event.type == SDL_KEYUP)
        {
            if( event.key.keysym.sym == SDLK_ESCAPE){
                return QUIT;
            }

        }
        

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            return DRAW;
        }

        if(event.type == SDL_MOUSEBUTTONUP)
        {
            return WAIT;
        }

    }

    return NOTHING;
    

}


BOOLEAN updateStatus(ACTIONS actionParam){
    int mousePosX, mousePosY;

    if(actionParam != NOTHING){   actionGlobal = actionParam;}

    switch(actionGlobal){
        case QUIT:
            return FALSE;

        case DRAW:
            
            SDL_GetMouseState(&mousePosX, &mousePosY);

            SDL_LockSurface(myApp.bufferSurface);
            
            Uint32* bufferPixels = myApp.bufferSurface->pixels;

            for(int i = -2; i <3 ; i++){
                for(int j = -2; j <3 ; j++){
                    bufferPixels[((mousePosY+i)*800) + (mousePosX+j)] = SDL_MapRGB(myApp.bufferSurface->format, 0,0,0);
                    
                }
            }
            

            SDL_UnlockSurface(myApp.bufferSurface);
            
            return TRUE;

        case WAIT:
            return TRUE;
        
        case NOTHING:
            return TRUE;
    }
    
    return TRUE;
}

void drawScreen(){
    
    myApp.screenTexture = SDL_CreateTextureFromSurface(myApp.renderer, myApp.bufferSurface);
    SDL_RenderCopy(myApp.renderer,myApp.screenTexture, &myApp.rectScreen, &myApp.rectScreen);
    SDL_RenderPresent(myApp.renderer);
    SDL_DestroyTexture(myApp.screenTexture);
}
void mainLoop(){
    BOOLEAN running = TRUE;    
    

    while(running == TRUE) {
        running = updateStatus(handleEvents());

        drawScreen();
    }
}

int main(int argc, char* argv[]){
    
    
    
    initApp(&myApp);
    mainLoop();
    closeApp(&myApp);
    return 0;
}



