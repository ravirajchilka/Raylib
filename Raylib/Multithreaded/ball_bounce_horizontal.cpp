#include <raylib.h>
#include <thread>
#include <atomic>
#include <chrono>

// Global variables
std::atomic<bool> running(true);
std::atomic<bool> updateLogic(false); // Flag to signal when to update logic

// Function to manage timer-based updates in a separate thread
void TimerThread(int intervalMs) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
        updateLogic = true; // Signal the main loop to update game logic
    }
}

int main() {
    // Initialize Raylib
    InitWindow(800, 600, "Timer-Based Game Logic");
    SetTargetFPS(60);

    // Start the timer thread (interval: 16ms for ~60 updates per second)
    std::thread timerThread(TimerThread, 16);

    Vector2 ballPosition = {400, 300};
    float ballSpeed = 5.0f;

    while (!WindowShouldClose()) {
        // Update game logic only when the timer signals it
        if (updateLogic.exchange(false)) { // Reset flag and check if true
            // Example game logic: move the ball horizontally
            ballPosition.x += ballSpeed;

            // Bounce the ball off screen edges
            if (ballPosition.x > GetScreenWidth() || ballPosition.x < 0) {
                ballSpeed = -ballSpeed;
            }
        }

        // Render the game
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(ballPosition, 20, BLUE);
        EndDrawing();
    }

    // Stop the timer thread safely before exiting
    running = false;
    timerThread.join();

    CloseWindow();
    return 0;
}
