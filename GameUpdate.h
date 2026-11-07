#include "raylib.h"

#if !defined(_GAMEUPDATE_)
#define _GAMEUPDATE_

extern const int screenW;
extern const int screenH;
extern const int fps;

extern Rectangle player1;
extern Rectangle ball;

struct Data {
	float speed;
	float angleDegrees;
	float angleRadians;
};

void GameUpdate_Update();
void GameUpdate_Init();
struct Data GetData(void);
#endif // _GAMEUPDATE_
