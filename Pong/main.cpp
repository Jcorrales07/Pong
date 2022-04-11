#include "raylib.h"

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {
		DrawCircle((int) x, (int) y, radius, WHITE);
	}
};

struct Paddle {
	float x, y;
	float speedY;
	float width, height;

	void Draw() {
		DrawRectangle(x - width / 2, y - height / 2, 10, 100, WHITE);
	}
};


int main() 
{
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;

	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5.0f;
	ball.speedX = 150;
	ball.speedY = 150;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = (GetScreenHeight() / 2);
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speedY = 500;

	Paddle rightPaddle;
	rightPaddle.x = (GetScreenWidth() - 50);
	rightPaddle.y = (GetScreenHeight() / 2);
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speedY = 500;

	while (!WindowShouldClose()) 
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;
		}

		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		DrawFPS(10, 10);
		EndDrawing();
	}



	// Esto destruye la ventana cuando se termine de ejecutar
	CloseWindow();
	return 0;
}