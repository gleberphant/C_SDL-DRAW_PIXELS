#include "includes.h"

#include "headerApp.h"

#include "headerScene.h"

APP app;

int main(int argc, char* argv[]){
         
    initApp(&app);
    
    setApp(&app);

    sceneLoop(&app);

    closeApp(&app);

    return 0;
}



