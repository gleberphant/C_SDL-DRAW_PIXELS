#define SCENE_HEADER

#include "includes.h"

#ifndef APP_HEADER

    #define APP_HEADER
    #include "headerApp.h"

#endif

#ifndef NODES_HEADER

    #define NODES_HEADER
    #include "headerNodes.h"

#endif


// atributos
typedef enum ACTIONS ACTIONS;
typedef enum BOOLEAN BOOLEAN;

// estruturas de dados
enum ACTIONS{
  QUIT,
  DRAW,
  WAIT,
  NOTHING
};

enum BOOLEAN{
  TRUE = true,
  FALSE = false
};


// funcções
ACTIONS handleEvents();

BOOLEAN updateStatus();

void drawScreen();

void sceneLoop();

void setApp(APP* app);