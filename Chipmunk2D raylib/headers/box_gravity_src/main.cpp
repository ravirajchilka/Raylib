#include "raylib.h"
#include "PhysicsEngine.h"


int main() {
	InitWindow(800,600,"chipmunk2d+raylib");
	SetTargetFPS(60);

	PhysicsEngine physics;

	while(!WindowShouldClose()) {
		physics.update(1.0F/60.0F);	

		auto box_pos = physics.get_box_position();

		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawRectangle(box_pos.x,box_pos.y,50,50,BROWN);
		EndDrawing();

	}

	return 0;
}


