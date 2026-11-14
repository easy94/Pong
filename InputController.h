#if !defined(INPUTCONTROLLER_H)
#define INPUTCONTROLLER_H
#include "raylib.h"
#include "Actions.h"
#include "Player.h"
#define KEYBOARD_BUTTON_COUNT 6

typedef struct {
	KeyboardKey key;
	int action;
} Command;

typedef struct InputController {
	Player* player;
	Command buttons[KEYBOARD_BUTTON_COUNT];
	Command (*GetInput)(struct InputController* this);
} InputController;

Command GetPlayerInput(InputController* this);
Command GetAIInput(InputController* this);
void SetAction(InputController* this, KeyboardKey, ActionsEnums);
InputController InputController_Ctr1(Player* p);
InputController InputController_Ctr2(Player* p);


#endif // INPUTCONTROLLER_H