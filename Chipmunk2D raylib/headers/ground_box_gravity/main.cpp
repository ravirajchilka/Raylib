#include "raylib.h"
#include "PhysicsEngine.h"

int main() {
    InitWindow(800, 600, "Chipmunk2D + Raylib Example");
    SetTargetFPS(60);

    PhysicsEngine physics;

    // Set ground position (move the ground up by 50 pixels)
    physics.setGroundPosition(400.0f);

    while (!WindowShouldClose()) {
        // Update physics engine
        physics.update(1.0f / 60.0f);

        // Get box position from the physics engine
        cpVect boxPos = physics.getBoxPosition();

        // Draw everything
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(boxPos.x - 25, boxPos.y - 25, 50, 50, BROWN); // Draw box centered at its position
         //   DrawLine(0, 500, 800, 500, BLACK); // Draw the ground line at the new position
         float newGroundY = 550.0f; // New ground position
         physics.setGroundPosition(newGroundY); // Update physics
         DrawLine(0, newGroundY, 800, newGroundY, BLACK); // Update visuals
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
