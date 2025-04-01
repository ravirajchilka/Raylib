#include "raylib.h"
#include "PhysicsEngine.h"

int main() {
    InitWindow(800, 600, "Chipmunk2D + Raylib");
    SetTargetFPS(60);

    PhysicsEngine physics;  // Create an instance of PhysicsEngine

    while (!WindowShouldClose()) {
        physics.update(1.0f / 60.0f);  // Update physics

        // Get the position of the box from Chipmunk2D
        cpVect box_pos = physics.get_box_position();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ✅ Draw the physics box using Raylib (Rendering in main.cpp)
        DrawRectangle(box_pos.x - 25, box_pos.y - 25, 50, 50, PURPLE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

