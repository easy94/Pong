#include "raylib.h"
#if !defined(ACTIONS_H)
#define ACTIONS_H

void OpenOptions(Rectangle*);
void PaddleDown(Rectangle*);
void PaddleUp(Rectangle*);

typedef enum{
    ActionNull = 0,
    ActionPaddleUpCode=1,
    ActionPaddleDownCode=2,
    ActionOptionsCode=3,
}ActionsEnums;


#endif // ACTIONS_H