#if !defined(PLAYER_H)
#define PLAYER_H
#include "raylib.h"
typedef struct{
	Rectangle paddle;
	InputHandler input;
}Player;

Player* Player_ctr_L();
Player* Player_ctr_R();

#endif // PLAYER_H