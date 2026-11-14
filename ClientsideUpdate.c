/*
	the updater (this file) needs the definitions in order to understand what to do with the function pointers that got send to him
	this is especially true if it becomes a multiplayer server and needs to handle input.
	I think that means that the declarations get send 
*/
#include "stdio.h"
#include "ClientSideUpdate.h"
#include "raymath.h"
#include "GameManager.h"
#include "GameInitConstants.h"
#include "Actions.h"
#include "Player.h"

#define bounce_ratio 30.f / 35 // maximum of added 30° at the paddle edge
#define ball_speed_multi 1.5f
#define VELO GetScreenHeight() / (3*FPS)
#define PLAYERCOUNT 2

float velo;
Vector2 paddleSpeed;
Vector2 ballSpeed;
int wasHit = 0;


Player player1;
Rectangle ball;
Player player2;
Vector2 playermidpoint;
InputData* inputdata[2];

/*
	HandleInput() doesnt make sense for two reasons:
	The input interface should expose a method that tells me exactly which Command
	the player invoked, not which key it pressed. This is because in order to have the
	player freely change his keyboard bindings, i will not wanna know it on the server
	for example which bindings the player has set up. Therefore i need this function to
	return a KEYCODE integer, which the server uses to invoke methods.
	So im thinking to eventually put all actions in one library that
	the gameserver later can use and client side software also.
	vtable also to distinguish between MP and SP!
*/

/// @brief This method only calculates mandatory game running state. Clientside state like menu is calculated somewhere else. When gamemode is running, this must be called!
/// @param inputdata 
/// @return 
GameData* CalcGameState(InputData inputdata[2]) //[0]::= player1, [1]::= player2 convention
{
	for (size_t i = 0; i < PLAYERCOUNT; i++)
	{
		switch (inputdata[i].cmd->actioncode)
		{
			case ActionPaddleDownCode:
				PaddleDown(inputdata[i].p);
			break;
			case ActionPaddleUpCode:
				PaddleDown(inputdata[i].p);
			default: ; //do nothing when no input was pressed;
			break;
		}
	}

	GameUpdate_Positions();
	GameUpdate_Bounce();
}

static void GameUpdate_Positions()
{

	// ball
	if (ball.x < 0)
	{
		ball.x = GetScreenWidth() / 2;
		ball.y = GetScreenHeight() / 2;
		ballSpeed = (Vector2){-1.f * velo * ball_speed_multi, 0.f * velo};
		wasHit = 0;
	}
	if (ball.x >= (GetScreenWidth() - ball.width))
	{
		ballSpeed.x *= -1;
		wasHit = 0;
	}
	if (ball.y <= 0 || ball.y >= GetScreenHeight() - ball.height)
	{
		ballSpeed.y = -ballSpeed.y;
	}

	ball.x += ballSpeed.x;
	ball.y += ballSpeed.y;
	// ball position vector2 +=  direction vector2; ...
}

// Logging
LogData GetData(void)
{
	float angleRadians = atan2f(-ballSpeed.y, ballSpeed.x);

	return (LogData){
		.speed = Vector2Length(ballSpeed),
		.angleDegrees = angleRadians * RAD2DEG,
		.angleRadians = angleRadians,
	};
}

static void GameUpdate_Bounce()
{
	// calculate the added angle value, bounce_ratio determines max angle value
	float Y_diff = (ball.y + 5 - playermidpoint.y);
	float bounce_angle = (bounce_ratio * Y_diff) * DEG2RAD;

	if (CheckCollisionRecs(player1.paddle, ball) && !wasHit)
	{
		if ((ball.x + ball.width > player1.paddle.x + player1.paddle.width))
		{
			// player1 lose anyway. not good enough to hit it after it passed your frontside
		}
		wasHit = 1;
		ballSpeed.x *= -1;
		ballSpeed = Vector2Rotate(ballSpeed, bounce_angle);
	}
	// if(CheckCollisionRecs(player2, ball))
}

GameData* GameUpdate_Update()
{
	while (!WindowShouldClose)
	{
		inputdata[0] = GetPlayerInput(&player1);
		inputdata[1] = GetPlayerInput(&player2);
		CalcGameState(inputdata);
	}

	return;
}

// initialize at runtime
void GameUpdate_Init(GameInitStruct data)
{
	player1 = *Player_ctr_L();
	player2 = *Player_ctr_R();

	ball = (Rectangle){
		screenW / 2.0f,
		screenH / 2.0f,
		10,
		10
	};
	ballSpeed = Vector2Scale((Vector2){-1, 0}, velo * ball_speed_multi);
	velo = VELO;
	paddleSpeed = (Vector2){VELO, VELO};
	playermidpoint = (Vector2){player1.paddle.x + (player1.paddle.width), player1.paddle.y + (player1.paddle.height / 2)};
}
