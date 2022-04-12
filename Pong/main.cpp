#include "raylib.h"
#include <iostream>


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
		DrawRectangleRec(GetRect(), WHITE);
	}

	Rectangle GetRect() {
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
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
	ball.speedX = 300;
	ball.speedY = 300;

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

	const char* winnerText = nullptr;


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

		if (IsKeyDown(KEY_W)) {
			std::cout << "Coordenada y: " << leftPaddle.y << "\n";
			leftPaddle.y -= leftPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_S)) {
			std::cout << "Coordenada y: " << leftPaddle.y << "\n";
			leftPaddle.y += leftPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP)) {
			rightPaddle.y -= rightPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN)) {
			rightPaddle.y += rightPaddle.speedY * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
			leftPaddle.GetRect()))
		{
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
			rightPaddle.GetRect())) 
		{
			if (ball.speedX > 0) 
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		if (ball.x < 0) {
			winnerText = "Right Player Wins!";
		}

		if (ball.x > GetScreenWidth()) {
			winnerText = "Left Player Wins!";
		}

		if (winnerText && IsKeyPressed(KEY_SPACE)) {
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		if (winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth /2  , GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawFPS(10, 10);
		EndDrawing();
	}



	// Esto destruye la ventana cuando se termine de ejecutar
	CloseWindow();
	return 0;
}