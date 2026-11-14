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

//default maybe?! no clue if needed at all

InputHandler Input_Constructor(GameState gamestate)
{
    InputHandler i;
	i.ButtonUp.funcptr = &PaddleUp;
	i.ButtonDown.funcptr = &PaddleDown;
    i.ButtonEsc.funcptr = &OpenOptions;

    return i;
}

ActionsEnums GetPlayerInput(Player *p)
{
    if(IsKeyPressed(p->input->ButtonDown.key)) return &p->input->ButtonDown.actioncode;
    if(IsKeyPressed(p->input->ButtonUp.key)) return &p->input->ButtonUp.actioncode;
    if(IsKeyPressed(p->input->ButtonEsc.key)) return &p->input->ButtonEsc.actioncode;
}

void SetAction(Command *c){
    c->funcptr = &OpenOptions;
}
void SetButtonToPaddleDown(Command *c){
    c->funcptr = &PaddleDown;
}
void SetButtonToPaddleUp(Command *c){
    c->funcptr = &PaddleUp;
}