#include "raylib.h"

int main() {
    // Initialize Raylib window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rotating Vertical Strip");

    // Strip properties
    Vector2 center = Vector2{screenWidth / 2.0f, screenHeight / 2.0f}; // Center of the strip
    float stripWidth = 20.0f;   // Width of the strip
    float stripHeight = 100.0f; // Height of the strip
    float rotationAngle = 0.0f; // Initial rotation angle

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update rotation angle based on key input
        if (IsKeyDown(KEY_RIGHT)) rotationAngle += 1.0f; // Rotate clockwise
        if (IsKeyDown(KEY_LEFT)) rotationAngle -= 1.0f; // Rotate counterclockwise

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(center.x - stripWidth / 2, center.y - stripHeight / 2,stripHeight/2,RED);

        // Define the rectangle (strip)
        Rectangle strip = Rectangle{center.x - stripWidth / 2, center.y - stripHeight / 2, stripWidth, stripHeight};

        // Draw the rectangle rotated around its center
        DrawRectanglePro(strip, Vector2{strip.width / 2, strip.height / 2}, rotationAngle, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}


