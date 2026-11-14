#if !defined(INPUTCONTROLLER_H)
#define INPUTCONTROLLER_H
#include "Actions.h"
#include "raylib.h"
#include "Player.h"

typedef struct {
	void (*funcptr)(Rectangle* r, float spd);
    int key;
	int actioncode;
} Command;

typedef struct{
	Command ButtonUp;
	Command ButtonDown;
	Command ButtonEsc;
} InputHandler;

void (*funcptr)(Rectangle *r, float spd);

ActionsEnums GetPlayerInput(Player* p);
InputHandler Input_Constructor(GameState);
void SetAction(Command *c);
void SetButtonToPaddleDown(Command *c);
void SetButtonToPaddleUp(Command *c);

#endif // INPUTCONTROLLER_H