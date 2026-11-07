#include "GameUpdate.h"
#include "raymath.h"
#include "stdio.h"

const int screenW = 800;
const int screenH = 600;
const int fps = 60;
const float velo = screenH / (2.5f*fps)*1.5;
const Vector2 paddleSpeed = {screenH / (2.5f * fps), screenH / (2.5f * fps)};
Vector2 ballSpeed = paddleSpeed;
int wasHit = 0;

Rectangle player1;
Rectangle ball;

static void GameUpdate_Positions()
{
	//player
	if (player1.y < 0)
		player1.y = 0;

	if (player1.y + player1.height > GetScreenHeight())
		player1.y = GetScreenHeight() - player1.height;

	if (IsKeyDown(KEY_UP))
	{
		player1.y -= paddleSpeed.y;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		player1.y += paddleSpeed.y;
	}

	//ball
	if (ball.x < 0)
	{
		ball.x = GetScreenWidth()/2;
		ball.y = GetScreenHeight()/2;
		ballSpeed = (Vector2){-1.f*velo, 0.f*velo};
		wasHit =0;
	}
	if (ball.x >= (GetScreenWidth() - ball.width))
	{
		ballSpeed.x *= -1;
		wasHit = 0;
	}
	if(ball.y <= 0 || ball.y >= GetScreenHeight() - ball.height)
	{
		ballSpeed.y = -ballSpeed.y;
	}
	
	ball.x += ballSpeed.x;
	ball.y += ballSpeed.y;
	// ball position vector2 +=  direction vector2; ...
}

struct Data GetData(void)
{
	float angleRadians = atan2f(-ballSpeed.y, ballSpeed.x);

	return (struct Data){
		.speed = Vector2Length(ballSpeed),
		.angleDegrees = angleRadians * RAD2DEG,
		.angleRadians = angleRadians,
	};
}

static void GameUpdate_Bounce()
{
	// -35pixel = 0.5
	// +35pixel = 1.5
	// 0pixel = 1
	// 45° / 35pixel =
	// 1.3 deg per pixel

	Vector2 playermidpoint = {player1.x + (player1.width), player1.y + (player1.height/2)};

	float Y_diff = (ball.y+5 - playermidpoint.y);
	float somemulti = 55.f / 35; //bouncemultiplier to pixel ratio
	float bounce_deg = (somemulti * Y_diff) * DEG2RAD;

	if(CheckCollisionRecs(player1, ball) && !wasHit)
	{
		wasHit = 1;
		Vector2 add_vec = {cosf(bounce_deg), sinf(bounce_deg)};
		printf("%f\n: bounce_multi", bounce_deg);
		float speed = sqrtf(ballSpeed.x*ballSpeed.x + ballSpeed.y*ballSpeed.y);
		printf("%f\n", speed);
		ballSpeed =Vector2Normalize(ballSpeed);
		ballSpeed.x *= -1;
		ballSpeed.x += add_vec.x;
		ballSpeed.y += add_vec.y;
		ballSpeed =Vector2Normalize(ballSpeed);
		ballSpeed=Vector2Scale(ballSpeed, velo);
	}
	
	//if(CheckCollisionRecs(player2, ball))
}

void GameUpdate_Update()
{
	GameUpdate_Positions();
	GameUpdate_Bounce();
}

//initialize at runtime
void GameUpdate_Init()
{
	player1 =
		(Rectangle){
			5,
			(screenH / 2.0f) + (70 / 2.0f),
			10,
			70,
	};

	ball =
		(Rectangle){
			screenW / 2.0f,
			screenH / 2.0f,
			10,
			10
	};
}
