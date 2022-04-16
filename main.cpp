#include <iostream>
#include "raylib.h"

//using namespace std;

class Ball
{
    public:
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw()
	{
		DrawCircle((int) x, (int) y, radius, RED);
	}
};

class Paddle
{
    public:
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

int randomValue() {
    int x = GetRandomValue(-1,1);
    if (x < 0) {
        x = -1;
    }
    else {
        x = 1;
    }

    return x;
}

int main()
{
    static int level = 1;
    static bool hasWon = 0;

	InitWindow(800, 600, "PONG");
	//SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);


	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 10;
	ball.speedX = 250 * randomValue();
	ball.speedY = 250 * randomValue();

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 700;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 150;

    char* winnerText = nullptr;

	while (!WindowShouldClose())
	{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W))
		{
		    if (leftPaddle.y > 0) {
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();}

			else {leftPaddle.y = 0;}
		}


		if (IsKeyDown(KEY_S))
		{

			if (leftPaddle.y < GetScreenHeight()) {
			leftPaddle.y += leftPaddle.speed * GetFrameTime();}

			else {leftPaddle.y = GetScreenHeight();}
		}
                    // Infinity
         rightPaddle.y = ball.y;

                   // Single Player

		/*if (rightPaddle.y > ball.y) {
            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (rightPaddle.y < ball.y) {
            rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}*/

                   // Two Players

		/*if (IsKeyDown(KEY_UP))
		{
			rightPaddle.y -= rightPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_DOWN))
		{
			rightPaddle.y += rightPaddle.speed * GetFrameTime();
		}*/

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		if (ball.x < 0)
		{
			winnerText = "PC Wins!";
			if (hasWon) {
                hasWon = false;
			}
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
            if (!hasWon) {
                hasWon = true;
			}
		}
		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;

            if (hasWon) {
                level++;
                rightPaddle.speed += 60;
            }
            else {
                level = 1;
                rightPaddle.speed = 200;
                ball.speedX = 300 * randomValue();
                ball.speedY = 300 * randomValue();
            }


			/*ball.speedX = level * 150 * randomValue();
			ball.speedY = level * 150 * randomValue();*/


			winnerText = nullptr;
		}


		BeginDrawing();
			ClearBackground(BLACK);

			for (int i = 0; i < GetScreenHeight(); i+=15) {
                DrawRectangle(GetScreenWidth()/2, i, 5, 10, WHITE);
			}

			ball.Draw();
			leftPaddle.Draw();
			rightPaddle.Draw();
            DrawText(TextFormat("%i", level), 20, 20, 20, RED);

			if (winnerText)
			{
				int textWidth = MeasureText(winnerText, 60);
				DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
			}



			DrawFPS(50, 50);
		EndDrawing();
		if (IsKeyDown(KEY_ESCAPE)) {CloseWindow(); }
	}



	return 0;
}
