#include "raylib.h"
#include <iostream>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

using namespace std;

int player_score = 0;
int cpu_score = 0;

// Clase BOLA
class Ball{
public:
float x,y;
int speed_x, speed_y;
int radius;

void Draw() {
	DrawCircle(x, y, radius, WHITE);
}
void ResetBall(){
	x = GetScreenWidth()/2;
	y = GetScreenHeight()/2;

	int speed_choices[2] = {-1,1};
	speed_x *= speed_choices[GetRandomValue(0,1)];
	speed_y *= speed_choices[GetRandomValue(0,1)];
}
void Update() {
	x += speed_x;
	y += speed_y;

	if(y + radius >= GetScreenHeight() || y - radius <= 0)
	{
		speed_y *= -1;
		
	}

	if(x + radius >= GetScreenWidth()){
		cpu_score ++;
		ResetBall();
	}
	
	if (x - radius <= 0)
	{
		player_score ++;
		ResetBall();
	}
}
};

// Clase PALETA
class Paddle {

protected:

void LimitMovement() {

	if (y <= 0)
	{
		y = 0;
	}
	if (y + pHeigth >= GetScreenHeight())
	{
		y = GetScreenHeight() - pHeigth; // se resta pHeight, pq el rectangulo se dibuja desde la esquina superior izquierda
	}
}

public:
float x,y;
float pWidth,pHeigth;
int speed;

void Draw(){
	DrawRectangle(x,y,pWidth,pHeigth, WHITE);
}

void Update(){
	if (IsKeyDown(KEY_W)||IsKeyDown(KEY_UP))
	{
		y = y - speed;
	}
	if (IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN))
	{
		y += speed;
	}
	LimitMovement();
	
}
};

// Clase PALETA CPU

class CpuPaddle: public Paddle{
	public:
	void Update(int ball_y)
	{
		if(y + pHeigth/2 > ball_y){
			y -= speed;
		}
		if(y + pHeigth/2 <= ball_y)
		{
			y += speed;
		}
		LimitMovement();
	}
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main ()

{
	cout << "Starting Game Loop" << endl;
	const int width = 1280;
	const int height = 800;
	InitWindow(width, height, "My pong game");

	SetTargetFPS(60); 

	//Inicializando objeto ball
	ball.radius = 20;
	ball.x = width/2;
	ball.y = height/2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	//Inicializando objeto player
	player.pWidth = 25;
	player.pHeigth = 120;
	player.x = width-player.pWidth-10;
	player.y = height/2-player.pHeigth/2;
	player.speed = 6;

	//Inicializando objeto cpu
	cpu.pWidth = 25;
	cpu.pHeigth = 120;
	cpu.x =10;
	cpu.y = height/2 - cpu.pHeigth/2;
	cpu.speed = 6;

	while(WindowShouldClose() == false) {
		
		BeginDrawing();

		//Updating
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//Colission checking
		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y},ball.radius, Rectangle{player.x, player.y, player.pWidth, player.pHeigth}))
		{
			ball.speed_x *= -1;

		}

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y},ball.radius, Rectangle{cpu.x, cpu.y, cpu.pWidth, cpu.pHeigth}))
		{
			ball.speed_x *= -1;

		}

		//Drawing
		ClearBackground(BLACK); // llena la pantalla del color escogido
		DrawLine(width/2, 0, width/2, height, WHITE);
		ball.Draw();
		DrawCircle(width/2, height/2, 20, WHITE);
		player.Draw();
		cpu.Draw();
		DrawText(TextFormat("%i",cpu_score), width/4 -20, 20, 80, WHITE);
		DrawText(TextFormat("%i",player_score), 3*width/4 -20, 20, 80, WHITE);


		EndDrawing();
	}

	CloseWindow();
	return 0;
}