#include "InputController.h"
#include "stdio.h"

Command GetPlayerInput(InputController *this)
{
    for (size_t i = 0; i < KEYBOARD_BUTTON_COUNT; i++)
    {
        if(IsKeyPressed(this->buttons[i].key)) return this->buttons[i];
    }
    return (Command){.action = 0, .key=0};
}
/*
Command GetAIInput(InputController *this){
    //Ai calculate and return Command
}
*/

void SetAction(InputController *this, KeyboardKey key, ActionsEnums action){
    this->buttons[action].key = key;
}

InputController InputController_Ctr1(Player* p){
    InputController i = {0};
    i.player = p;
    i.GetInput=&GetPlayerInput;
    i.buttons[0].key=KEY_UP;
    i.buttons[0].action=ActionPaddleUpCode;
    i.buttons[1].key=KEY_DOWN;
    i.buttons[1].action=ActionPaddleDownCode;
    i.buttons[2].key=KEY_P;
    i.buttons[2].action=ActionOptionsCode;
    return i;
}

InputController InputController_Ctr2(Player* p){
    InputController i = {0};
    i.player=p;
    i.GetInput=&GetPlayerInput;
    i.buttons[0].key=KEY_W;
    i.buttons[0].action=ActionPaddleUpCode;
    i.buttons[1].key=KEY_S;
    i.buttons[1].action=ActionPaddleDownCode;
    i.buttons[2].key=KEY_PAUSE;
    i.buttons[2].action=ActionOptionsCode;
    return i;
}
