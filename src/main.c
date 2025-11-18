/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	const int screenWidth = 800;
	const int screenHeight = 450;

	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(screenWidth, screenHeight, "Platformer");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");
	Texture charactersAtlas = LoadTexture("characters.png");

	Vector2 ballPosition = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
	Vector2 ballSpeed = {5.0f, 4.0f};
	const int ballRadius = 20;
	float gravity = 0.2f;

	bool useGravity = true;
	bool pause = 0;
	int frameCounter = 0;

	SetTargetFPS(60);
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		if (IsKeyPressed(KEY_G)) useGravity = !useGravity;
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;

		if (!pause) {

			ballPosition.x += ballSpeed.x;
			ballPosition.y += ballSpeed.y;

			if (useGravity) ballSpeed.y += gravity;

			if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
			if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -0.95f;

		} else frameCounter++;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(RAYWHITE);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		// draw our texture to the screen
		DrawTexture(wabbit, 400, 200, WHITE);
		DrawTexture(charactersAtlas, 500, 200,WHITE);

		DrawCircleV(ballPosition, (float)ballRadius, MAROON);

		if (useGravity) DrawText("GRAVITY: ON (Press G to disable)", 10, GetScreenHeight() - 50, 20, DARKGREEN);
    else DrawText("GRAVITY: OFF (Press G to enable)", 10, GetScreenHeight() - 50, 20, RED);

		// On pause, we draw a blinking message
		if (pause && ((frameCounter/30)%2)) DrawText("PAUSED", 350, 200, 30, GRAY);

		DrawFPS(10, 10);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);
	UnloadTexture(charactersAtlas);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
