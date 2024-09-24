#include "raylib.h"
#include <iostream>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

using namespace std;
// Clase BOLA
class Ball{
public:
float x,y;
int speed_x, speed_y;
int radius;

void Draw() {
	DrawCircle(x, y, radius, WHITE);
}
void Update() {
	x += speed_x;
	y += speed_y;

	if(y + radius >= GetScreenHeight() || y - radius <= 0)
	{
		speed_y *= -1;

	}

	if(x + radius >= GetScreenWidth() || x - radius <= 0)
	{
		speed_x *= -1;
	}
}
};

// Clase PALETA
class Paddle {
public:
float x,y;
float width,heigth;
int speed;

void Draw(){
	
}
};

Ball ball;

int main ()

{
	cout << "Starting Game Loop" << endl;
	const int width = 1280;
	const int height = 800;
	InitWindow(width, height, "My pong game");

	SetTargetFPS(60); 

	//Definiendo objeto ball
	ball.radius = 20;
	ball.x = width/2;
	ball.y = height/2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	while(WindowShouldClose() == false) {
		
		BeginDrawing();

		//Updating
		ball.Update();

		//Drawing
		ClearBackground(BLACK); // llena la pantalla del color escogido
		DrawLine(width/2, 0, width/2, height, WHITE);
		ball.Draw();
		DrawCircle(width/2, height/2, 20, WHITE);
		DrawRectangle(10, height/2 - 60, 25, 120, WHITE); // se le resta 60 al yPos pq el rectangulo se dibuja desde la esquina superior izquierda y 60 es la mitad de la altura
		DrawRectangle(width - 25 - 10, height/2 - 60, 25, 120, WHITE); //  se le resta 25 al xPos, porque es el ancho el rect, ademas el margen de 10 que esta en el otro

		EndDrawing();
	}

	CloseWindow();
	return 0;
}