#include "raylib.h"
#include "ClientSideUpdate.h"
#include "GameManager.h"
#include "stdio.h"

//state

int GetX(int x) { return x*GetScreenWidth()/100; }
int GetY(int y) { return y*GetScreenHeight()/100; }

void GameInit(){
    InitWindow(screenW, screenH, "Pong");
	SetTargetFPS(fps);
	//maybe set
	
}

void StartGame()
{
	GameData *gamedata;
    GameInit();
    while (!WindowShouldClose())
    {
        //getInput -> lookup command pattern put the player controllers in its own file
		//no need to get input here. just take gamedata and save it somehow
        //pass to gameupdater and receive gamestate
		gamedata = GameUpdate_Update();
        //pass gamestate to renderer

    }  
}

void Render(GameData data)
{
    	// Draw
		BeginDrawing();

		ClearBackground(BLACK);

		if(data.state == Ingame)
		{
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
			
			DrawRectangleRec(player1, WHITE);
			DrawCircleV((Vector2){
				ball.x + ball.width / 2.0f, ball.y + ball.height / 2.0f}, 
				ball.height/2.f, 
				WHITE
			);
			
		}

		EndDrawing();
}