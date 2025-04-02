#include "raylib.h"
#include <cstdint>
#include <iostream>

class Box {
public:
    std::int16_t height, width;
    bool jumping = false;
    float verticalVelocity = 0.0f;
    
    void draw_box(Vector2 &pos) {
        DrawRectangle(pos.x, pos.y, width, height, BLUE);
    }

    void move_box(std::int16_t velocity, Vector2 &pos) {
        if (pos.x < GetScreenWidth() - width) {
            pos.x += velocity;
        }
    }

    void move_box_back(std::int16_t velocity, Vector2 &pos) {
        if (pos.x > 0) {
            pos.x -= velocity;
        }
    }

    void jump(std::int16_t velocity, Vector2 &pos) {
        if (!jumping) { 
            jumping = true;
            verticalVelocity = -velocity * 3.0f; // Initial strong jump impulse
        }
    }

    void apply_gravity(Vector2 &pos, float gravity) {
        if (jumping) {
            pos.y += verticalVelocity;
            verticalVelocity += gravity; // Gravity pulls down

            // Stop jumping when reaching the ground
            if (pos.y >= GetScreenHeight() - height) {
                pos.y = GetScreenHeight() - height;
                jumping = false;
                verticalVelocity = 0;
            }
        }
    }
};

int main() {
    InitWindow(800, 800, "Jump Fix");
    SetTargetFPS(60);

    Box box;
    box.height = 60;
    box.width = 80;
    Vector2 pos = {100.0F, 740.0F}; // Start at ground level
    std::int16_t velocity = 10;
    float gravity = 1.0f; // Simulated gravity

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) {
            box.move_box(velocity, pos);
        }
        if (IsKeyDown(KEY_LEFT)) {
            box.move_box_back(velocity, pos);
        }
        if (IsKeyPressed(KEY_UP)) { // Only jump on key press, not key hold
            box.jump(velocity, pos);
        }

        box.apply_gravity(pos, gravity); // Apply gravity every frame

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            box.draw_box(pos);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
