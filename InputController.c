/*
    should this be inside a Player object???? I dont know yet.

    Thought: Make the inputcontroller ask the players for input.
    Do this by making use of the vtable. that is, make the player interface take a pointer that
    for example checks for keypressinput or in case of AI, calculates the next move and then return command Key codes.
    so the inputcontroller sends that input to the updater which is a pointer to a function that is invoked.

    So the concrete design question is:
    what are these swappable functions that are inside the vtable so i can use different methods in different modes/situations.
    question that needs to be answered before proceeding.
*/

#include "InputController.h"
#include "raylib.h"
#include "Actions.h"
#include "Player.h"
#include "stdio.h"
#include "GameManager.h"
#include "malloc.h"
#include "GameInitConstants.h"
#include "Actions.h"


Command GetPlayerInput(InputController *this)
{
    for (size_t i = 0; i < KEYBOARD_BUTTON_COUNT; i++)
    {
        if(IsKeyPressed(this->buttons[i].key)) return this->buttons[i];
    }
    return (Command){.action = 0, .key=0};
}

Command GetAIInput(InputController *this){
    //Ai calculate and return Command
}

void SetAction(InputController *this, KeyboardKey key, ActionsEnums action){
    this->buttons[action].key = key;
}