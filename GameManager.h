#if !defined(GAMEMANAGER_H)
#define GAMEMANAGER_H

#include "InputController.h"
#include "raylib.h"
#include "Player.h"

extern const int screenW;
extern const int screenH;
extern const int fps;

typedef struct GameInitStruct;
void StartGame();

typedef enum{
    Ingame,
    Start,
    End,
}GameState;

typedef enum{
    localmp,
    sp,
    srvc,
}GameMode;

typedef struct {
    GameMode mode;
    Rectangle p1;
    Rectangle p2;
    Rectangle ball;
    GameState state;
    
    int score;
}GameData;

//input sources
//these input sources should get the

typedef struct {
    //windowheight...
    //etc..
    int a;
} GameInitStruct;

typedef struct{
    Command cmd[2];
    Player *p;
} InputData;

typedef enum{
    easy,
    hard
}Difficulty;

typedef struct{
    //basically all entities
    Player players[2];
    GameState gamestate;
    Difficulty
}Scene;

#endif // GAMEMANAGER_H