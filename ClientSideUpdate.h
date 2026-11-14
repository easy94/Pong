
#if !defined(CLIENTSIDEUPDATE_H)
#define CLIENTSIDEUPDATE_H
#include "raylib.h"
#include "InputController.h"
#include "stdio.h"
#include "ClientSideUpdate.h"
#include "raymath.h"
#include "GameManager.h"
#include "GameInitConstants.h"
#include "Actions.h"
#include "Player.h"

typedef struct {
	float speed;
	float angleDegrees;
	float angleRadians;
}LogData;

typedef struct {
    Rectangle p1;
    Rectangle p2;
    Rectangle ball;
    int score;
}GameData;

typedef enum {
    diffi_null=0,
    easy=1,
    hard,

    difficultycount
}Difficulty;
/*
typedef struct{
    //basically all entities
    Player players[2];
    GameState gamestate;
    GameMode mode;
    Difficulty Aidifficulty;
    InputController *player_ctrlr;
    InputController *ai_ctrlr;
    void (*sendDataToInterface)();
}Scene;
*/

void GameUpdate_Update();
void GameUpdate_Init();
LogData GetData(void);
void Render();
#endif // CLIENTSIDEUPDATE_H
