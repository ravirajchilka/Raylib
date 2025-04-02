#include "raylib.h"
#include <cstdint>
#include <iostream>

class Box {
	public:
		std::int16_t height,width;
	
		void draw_box(Vector2 &pos) {
			DrawRectangle(pos.x,pos.y,width,height,BLUE);
		}

		void move_box(std::int16_t &velocity, Vector2 &pos) {
			if(pos.x < GetScreenWidth() - width) {
				pos.x += velocity;
			}
		}

		void move_box_back(std::int16_t &velocity, Vector2 &pos) {
			if(pos.x > 0) {
				pos.x -= velocity;
			}
		}

		void move_box_up(std::int16_t &velocity, Vector2 &pos) {
			if(pos.y > 0) {
				pos.y -= velocity;
			}
		}

		void move_box_down(std::int16_t &velocity, Vector2 &pos) {
			if(pos.y < GetScreenHeight() - height) {
				pos.y += velocity;
			}
		}
		
};


int main() {

	InitWindow(800,800,"test");
	SetTargetFPS(60);

	Box box;
	box.height = 60;
	box.width = 80;
	Vector2 pos = {50.0F,50.0F};
	std::int16_t velocity = 10;

	while(!WindowShouldClose()) {

		if(IsKeyDown(KEY_RIGHT)) {
			box.move_box(velocity,pos);	
		}
		if(IsKeyDown(KEY_LEFT)) {
			box.move_box_back(velocity, pos);		
		}
		if(IsKeyDown(KEY_UP)) {
			box.move_box_up(velocity,pos);		
		}
		if(IsKeyDown(KEY_DOWN)) {
			box.move_box_down(velocity, pos);		
		}

		BeginDrawing();
			ClearBackground(LIGHTGRAY);
			box.draw_box(pos);
		EndDrawing();
	}


	CloseWindow();
	return 0;
}

