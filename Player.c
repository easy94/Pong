#include "Player.h"

Player Player_ctr_L()
{
    Player p= {0};
    p.paddle = (Rectangle){
        10, 
		(GetScreenHeight() / 2.0f) + (70 / 2.0f),
		10,
		70,
    };
    return p;
}

Player Player_ctr_R()
{
    Player p = {0};
    p.paddle = (Rectangle){
        GetScreenWidth() - 10,
		(GetScreenHeight() / 2.0f) + (70 / 2.0f),
		10,
		70,
    };
    return p;
}