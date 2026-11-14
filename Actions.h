#include "raylib.h"
#if !defined(ACTIONS_H)
#define ACTIONS_H

void OpenOptions();
void PaddleDown(Rectangle*, float);
void PaddleUp(Rectangle*, float);

typedef enum{
    ActionNull = 0,
    ActionPaddleUpCode=1,
    ActionPaddleDownCode=2,
    ActionOptionsCode=3,
}ActionsEnums;


#endif // ACTIONS_H