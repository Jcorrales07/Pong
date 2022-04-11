#include "raylib.h"

int main() 
{
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	float ballX = GetScreenWidth() / 2.0f;
	float ballY = GetScreenHeight() / 2.0f;
	float ballRadius = 5.0f;
	float ballSpeedX = 150;
	float ballSpeedY = 150;

	while (!WindowShouldClose()) 
	{
		ballX += ballSpeedX * GetFrameTime();
		ballY += ballSpeedY * GetFrameTime();

		if (ballY < 0) {
			ballY = 0;
			ballSpeedY *= -1;
		}

		if (ballY > GetScreenHeight()) {
			ballY = GetScreenHeight();
			ballSpeedY *= -1;
		}

		DrawWindowItems(ballX, ballY, ballRadius);
	}



	// Esto destruye la ventana cuando se termine de ejecutar
	CloseWindow();
	return 0;
}

void DrawWindowItems(float ballX, float ballY, float ballRadius) {
	BeginDrawing();
	ClearBackground(BLACK);

	DrawCircle((int)ballX, (int)ballY, ballRadius, WHITE);
	DrawRectangle(50, (GetScreenHeight() / 2 - 50), 10, 100, WHITE);
	DrawRectangle((GetScreenWidth() - 50 - 10), (GetScreenHeight() / 2 - 50), 10, 100, WHITE);

	DrawFPS(10, 10);
	EndDrawing();
}