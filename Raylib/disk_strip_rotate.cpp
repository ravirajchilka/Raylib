#include "raylib.h"

int main() {
    // Initialize Raylib window
    const int screen_width = 800;
    const int screen_height = 600;
    InitWindow(screen_width, screen_height, "Rotating Vertical Strip");

    // Strip properties
    Vector2 center = Vector2{screen_width / 2.0f, screen_height / 2.0f}; // Center of the strip
    float strip_width = 20.0f;   // Width of the strip
    float strip_height = 100.0f; // Height of the strip
    float rotation_angle = 0.0f; // Initial rotation angle

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update rotation angle based on key input
        if (IsKeyDown(KEY_RIGHT)) rotation_angle += 1.0f; // Rotate clockwise
        if (IsKeyDown(KEY_LEFT)) rotation_angle -= 1.0f; // Rotate counterclockwise

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(center.x - strip_width / 2, center.y - strip_height / 2,strip_height/2,RED);

        // Define the rectangle (strip)
        Rectangle strip = Rectangle{center.x - strip_width / 2, center.y - strip_height / 2, strip_width, strip_height};

        // Draw the rectangle rotated around its center
        DrawRectanglePro(strip, Vector2{strip.width / 2, strip.height / 2}, rotation_angle, BLUE);
     	
		// Draw the rectangle rotated around its center
 		DrawRectanglePro(strip, Vector2{strip.width / 2, strip.height / 4}, rotation_angle, BLACK);


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

