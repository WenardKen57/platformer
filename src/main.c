/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

typedef struct {
	Vector2 position;
	Vector2 velocity;
	Rectangle bounds;
	bool isGrounded;
} Player;

typedef struct {
	Rectangle bounds;
} Platform;

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

	Player player = {
		(Vector2){50.0f, 50.0f},
		(Vector2) {0.0f, 0.0f},
		(Rectangle) {50.0f, 50.0f, 30.0f, 60.0f},
		false
	};

	Platform platform = { (Rectangle) {0.0f, 400.0f, 800.0f, 50.0f}};

	float playerSpeed = 10.0f;

	float gravity = 0.2f;
	bool useGravity = true;
	bool pause = 0;

	SetTargetFPS(60);
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		if (IsKeyPressed(KEY_SPACE)) pause = !pause;

		if (!pause) {
			player.velocity.y += gravity;
			player.position.y += player.velocity.y;

			player.bounds.y = player.position.y;
			player.bounds.x = player.position.x;

			if (CheckCollisionRecs(player.bounds, platform.bounds)) {

				Rectangle overlap = GetCollisionRec(player.bounds, platform.bounds);

				if (player.bounds.y < platform.bounds.y) {

					player.position.y -= overlap.height;

					player.velocity.y = 0;

					player.isGrounded = true;
				}

			} else {

				if (IsKeyPressed(KEY_D)) player.velocity.x +=	

			}
		}
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		// draw some text using the default font
		DrawText("Hello Raylib", 200,200,20,WHITE);

		DrawRectangleRec(player.bounds, GREEN);
		DrawRectangleRec(platform.bounds, RED);

		DrawFPS(10, 10);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
