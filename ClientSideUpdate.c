#include "ClientSideUpdate.h"

#define bounce_ratio 30.f / 35 // maximum of added 30° at the paddle edge
#define ball_speed_multi 1.5f
#define VELO GetScreenHeight() / (3*FPS)
#define PLAYERCOUNT 2

float velo;
Vector2 paddleSpeed;
Vector2 ballSpeed;
int wasHit = 0;

InputController p1_ctrl;
InputController p2_ctrl;

Player players[2];
Command inputdata[2];
Vector2 playermidpoint[2];

Rectangle ball;
GameData data;

int GetX(int x) { return x*GetScreenWidth()/100; }
int GetY(int y) { return y*GetScreenHeight()/100; }

static void GameInit(){
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Pong");
	SetTargetFPS(FPS);
}

static void GameUpdate_Bounce()
{
	// calculate the added angle value, bounce_ratio determines max angle value
	for (size_t i = 0; i < PLAYERCOUNT; i++)
	{
		
		float Y_diff = (ball.y + 5 - playermidpoint[i].y);
		float bounce_angle = (bounce_ratio * Y_diff) * DEG2RAD;
		
		if (CheckCollisionRecs(players[i].paddle, ball) && !wasHit)
		{
			if ((ball.x + ball.width > players[i].paddle.x + players[i].paddle.width))
			{
				// player1 lose anyway. not good enough to hit it after it passed your frontside
			}
			wasHit = 1;
			ballSpeed.x *= -1;
			ballSpeed = Vector2Rotate(ballSpeed, bounce_angle);
		}
	}
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

/// @brief This method only calculates mandatory game running state. Clientside state like menu is calculated somewhere else. When gamemode is running, this must be called!
/// @param inputdata 
/// @return 
void CalcGameState() //[0]::= player1, [1]::= player2 convention
{
	for (size_t i = 0; i < PLAYERCOUNT; i++)
	{
		switch (inputdata[i].action)
		{
			case ActionPaddleDownCode:
				PaddleDown(&players[i].paddle, velo);
			break;
			case ActionPaddleUpCode:
				PaddleUp(&players[i].paddle, velo);
			break;
			default: //do nothing when no input was pressed;
			break;
		}
	}

	GameUpdate_Positions();
	GameUpdate_Bounce();


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

void GameUpdate_Update()
{
	GameInit();
	GameUpdate_Init();
	while (!WindowShouldClose())
	{
		inputdata[0] = GetPlayerInput(&p1_ctrl);
		inputdata[1] = GetPlayerInput(&p2_ctrl);
		CalcGameState();
		Render();
	}
}

void GameUpdate_Init()
{
	Player player1 = Player_ctr_L();
	Player player2 = Player_ctr_R();
	players[0] = player1;
	players[1] = player2;

	p1_ctrl = InputController_Ctr1(&players[0]);
	p2_ctrl = InputController_Ctr2(&players[1]);

	ball = (Rectangle){
		SCREENWIDTH / 2.0f,
		SCREENHEIGHT / 2.0f,
		10,
		10
	};

	velo = VELO;
	ballSpeed = Vector2Scale((Vector2){-1, 0}, velo * ball_speed_multi);
	paddleSpeed = (Vector2){VELO, VELO};
	Vector2 playermidpoint1 = (Vector2){player1.paddle.x + (player1.paddle.width), player1.paddle.y + (player1.paddle.height / 2)};
	Vector2 playermidpoint2 = (Vector2){player1.paddle.x + (player1.paddle.width), player1.paddle.y + (player1.paddle.height / 2)};
	playermidpoint[0] = playermidpoint1;
	playermidpoint[1] = playermidpoint2;

	/*
		scene = (Scene)
		{
			.Aidifficulty = diffi_null,
			.ai_ctrlr = NULL,
			.player_ctrlr = &(InputController){
			.GetInput=&GetPlayerInput,
			.buttons={ActionNull, ActionPaddleUpCode, ActionPaddleDownCode, ActionOptionsCode}},
			.gamestate=Start,
			.mode = localmp,
			.sendDataToInterface=NULL
		};
	*/
}

void Render()
{
		BeginDrawing();

		ClearBackground(BLACK);

			//logging
			if (IsKeyDown(KEY_UP))
			{
				DrawText("UP", GetX(45),GetY(5), 15, WHITE);
			}
			if (IsKeyDown(KEY_DOWN))
			{
				DrawText("DOWN", GetX(45), GetY(5), 15, WHITE);
			}
			char buf[100];
			sprintf(buf, "%fdeg, %frad, %fspeed", GetData().angleDegrees, GetData().angleRadians, GetData().speed);
			DrawText(buf, GetX(45), GetY(8), 10, WHITE);
			
			DrawRectangleRec(players[0].paddle, WHITE);
			DrawRectangleRec(players[1].paddle, WHITE);
	
			DrawCircleV((Vector2){
				ball.x + ball.width / 2.0f, ball.y + ball.height / 2.0f}, 
				ball.height/2.f, 
				WHITE
			);	

		EndDrawing();
}