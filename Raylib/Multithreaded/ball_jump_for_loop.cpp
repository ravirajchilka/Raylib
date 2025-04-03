#include <raylib.h>
#include <thread>
#include <chrono>
#include <iostream>

// Ball structure
struct Ball {
    Vector2 position;
    float radius;
    bool isJumping;
};

// Global variables
Ball ball = { {400, 340}, 20, false };

// Function to handle ball jumping asynchronously
void BallJump(int airTimeMs) {
    ball.isJumping = true;

    // Move the ball upward
    for (int i = 0; i < 20; ++i) { // Simulate upward motion
        ball.position.y -= 5; // Move up
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    // Wait in the air for the specified duration
    std::this_thread::sleep_for(std::chrono::milliseconds(airTimeMs));

    // Move the ball downward
    for (int i = 0; i < 20; ++i) { // Simulate downward motion
        ball.position.y += 5; // Move down
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    ball.position.y = 340; // Reset position to ground level
    ball.isJumping = false;
}

int main() {
    // Initialize Raylib
    InitWindow(800, 600, "Ball Jump with Async");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Handle input for jumping
        if (IsKeyPressed(KEY_SPACE) && !ball.isJumping) {
            // Start the jump in a separate thread
            std::thread(BallJump, 50).detach(); // Detach to avoid blocking
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(ball.position, ball.radius, BLUE); // Draw the ball

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
