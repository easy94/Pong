#if !defined(INPUTCONTROLLER_H)
#define INPUTCONTROLLER_H
#include "Actions.h"
#include "raylib.h"
#include "GameManager.h"
#include "Player.h"
#define KEYBOARD_BUTTON_COUNT 6

typedef struct {
	KeyboardKey key;
	int action;
} Command;

typedef struct {
	Command buttons[KEYBOARD_BUTTON_COUNT];
	Command(*GetInput)(InputController* this);
} InputController;

void (*funcptr)(Rectangle *r, float spd);

Command GetPlayerInput(InputController* this);
Command GetAIInput(InputController* this);
void SetAction(InputController* this, KeyboardKey, ActionsEnums);

#endif // INPUTCONTROLLER_H