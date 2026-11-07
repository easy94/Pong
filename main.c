#include "stdio.h"
#include "raylib.h"
#include "GameUpdate.h"

// global variables
int pause = 0;

int main(void)
{


	InitWindow(screenW, screenH, "Pong");
	SetTargetFPS(fps);
	GameUpdate_Init();

	while (!WindowShouldClose())
	{
		// Update
		if(!pause){
			GameUpdate_Update();
		}
		else
		{
			//some menu screen
			//define some space and register clicks inside it
		}

//------------------------------------------------------

		// Draw
		BeginDrawing();

		ClearBackground(BLACK);

		//logging
		if (IsKeyDown(KEY_UP))
		{
			DrawText("UP", GetScreenWidth() - 50, GetScreenHeight() - 50, 20, WHITE);
		}
		if (IsKeyDown(KEY_DOWN))
		{
			DrawText("DOWN", GetScreenWidth() - 50, GetScreenHeight() - 50, 20, WHITE);
		}
		char buf[100];
		sprintf(buf, "%fdeg, %frad, %fspeed", GetData().angleDegrees, GetData().angleRadians, GetData().speed);
		DrawText(buf, GetScreenHeight()/2, GetScreenHeight()/2, 20, WHITE);

		DrawRectangleRec(player1, WHITE);
		DrawCircleV((Vector2){
			ball.x + ball.width / 2.0f, ball.y + ball.height / 2.0f}, 
			ball.height/2.f, 
			WHITE
		);

		EndDrawing();
	}

	return 0;
}
