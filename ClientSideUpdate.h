
#if !defined(CLIENTSIDEUPDATE_H)
#define CLIENTSIDEUPDATE_H
#include "raylib.h"

extern Rectangle player1;
extern Rectangle ball;

typedef struct{
	int a;
} GameInitStruct;

typedef struct {
	float speed;
	float angleDegrees;
	float angleRadians;
}LogData;

typedef struct {
	//function pointers
	//for handing over to updater
	//so he invokes functions needed
	//for singleplayer mode, like AI next move eval method
}VtableGameMode;

GameData* GameUpdate_Update();
void GameUpdate_Init(GameInitStruct);
LogData GetData(void);
#endif // CLIENTSIDEUPDATE_H
