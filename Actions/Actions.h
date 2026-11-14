#include "raylib.h"
#if !defined(ACTIONS_H)
#define ACTIONS_H

void OpenOptions(Rectangle*);
void PaddleDown(Rectangle*);
void PaddleUp(Rectangle*);

typedef enum{
    ActionPaddleUpCode=991111,
    ActionPaddleDownCode=991112,
    ActionOptionsCode=991113,
}ActionsEnums;


#endif // ACTIONS_H