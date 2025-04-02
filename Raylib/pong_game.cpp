#include "raylib.h"
#include <iostream>
#include <cstdint>

constexpr std::int16_t screen_width = 1280;
constexpr std::int16_t screen_height = 800;

class Ball {
	public:
		float x_pos,y_pos;
		std::int16_t x_speed, y_speed;
		std::int16_t radius;	
	
		Ball() = default;

		void draw() {
			DrawCircle(x_pos,y_pos,radius,WHITE);
		}

		void update() {
			x_pos += x_speed;
			y_pos += y_speed;

			if(x_pos + radius >= screen_width || x_pos - radius <= 0) {
				x_speed *= -1;
			}
			if(y_pos + radius >= screen_height || y_pos - radius <= 0) {
				y_speed *= -1;
			}
		}
};

class Paddle {
	public:
		float x,y;
		float width, height;
		std::int16_t speed;

		Paddle() = default;
		
		void draw() {
			DrawRectangle(x,y,width,height,GREEN);
		}

		void update() {
			if(IsKeyDown(KEY_UP)) {
				y -= speed;
			}
			if(IsKeyDown(KEY_DOWN)) {
				y += speed;
			}

			if(y + height >= screen_height) {
				y = screen_height - height;
			}
			if(y <= 0) {
				y = 0;
			}
			limitMovement(); 
		}


	protected:		
		void limitMovement() {
			if(y + height >= screen_height) {
				y = screen_height - height;
			}
			if(y <= 0) {
				y = 0;
			}
		}

};

class CPUpaddle : public Paddle {
	public:

		void update(std::int16_t ball_y) {
			if(y + height/2 > ball_y) {
				y -= speed;
			}
			if(y + height/2 <= ball_y) {
				y += speed;
			}

			limitMovement();
		}
};

int main() {
	InitWindow(screen_width, screen_height, "My Pong Game!");
	SetTargetFPS(60);

	Ball ball;
	ball.radius = 10;
	ball.x_pos = screen_width/2;
	ball.y_pos = screen_height/2;
	ball.x_speed = 7;
	ball.y_speed = 7;

	Paddle player;
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height/2 - player.height/2;
	player.speed = 6;

	CPUpaddle cpu_paddle;
	cpu_paddle.width = 25;
	cpu_paddle.height = 120;
	cpu_paddle.x = 10;
	cpu_paddle.y = screen_height/2 - cpu_paddle.height/2;
	cpu_paddle.speed = 7;

	while(!WindowShouldClose()) {
		BeginDrawing();
		    // udpate
			ball.update();
			cpu_paddle.update(ball.y_pos);
			player.update();

			// check for collisions
			if(CheckCollisionCircleRec(Vector2{ball.x_pos, ball.y_pos}, ball.radius, Rectangle{player.x,player.y,player.width,player.height})) {
				ball.x_speed *= -1;
			}

			if(CheckCollisionCircleRec(Vector2{ball.x_pos,ball.y_pos},
			ball.radius, Rectangle{cpu_paddle.x, cpu_paddle.y, cpu_paddle.width, cpu_paddle.height})) {
				ball.x_speed *= -1;
			}

			// draw
			ClearBackground(BLACK);
			player.draw();
			cpu_paddle.draw();
			ball.draw();
			DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
