#include <raylib.h>

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 600

// Ball Properties
const float ballRadius = 20.0f;
const float gravity = 1000.0f;
const float jumpVelocity = -500.0f; // Negative Y for upward jump
const float moveSpeed = 200.0f;     // Horizontal movement speed
const float groundY = SCREEN_HEIGHT - 50; // Ground Y position

// Ball State
Vector2 ballPosition = { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
Vector2 ballVelocity = { 0.0f, 0.0f };
bool isGrounded = false;

// Update Ball Physics
void UpdateBall(float dt) {
    // Apply gravity
    ballVelocity.y += gravity * dt;

    // Update ball position
    ballPosition.x += ballVelocity.x * dt;
    ballPosition.y += ballVelocity.y * dt;

    // Check collision with the ground
    if (ballPosition.y + ballRadius >= groundY) {
        ballPosition.y = groundY - ballRadius;
        ballVelocity.y = 0.0f;
        isGrounded = true;
    } else {
        isGrounded = false;
    }
}

// Handle Input for Movement and Jumping
void HandleInput() {
    // Horizontal movement
    if (IsKeyDown(KEY_RIGHT)) {
        ballVelocity.x = moveSpeed;
    } else if (IsKeyDown(KEY_LEFT)) {
        ballVelocity.x = -moveSpeed;
    } else {
        ballVelocity.x = 0.0f;
    }

    // Jumping
    if (IsKeyPressed(KEY_UP) && isGrounded) {
        ballVelocity.y = jumpVelocity;
        //isGrounded = false;
    }
}

// Render Ball and Ground with Raylib
void Render() {
    BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw ground line visually
        DrawLine(0, groundY, SCREEN_WIDTH, groundY, BLACK);

        // Draw the dynamic circle (ball)
        DrawCircleV(ballPosition, ballRadius, RED);

    EndDrawing();
}

// Main Function
int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Manual Jumping Logic");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        HandleInput();   // Handle input for movement and jumping
        UpdateBall(GetFrameTime()); // Update ball physics

        Render();        // Render objects using Raylib
    }

    CloseWindow();

    return 0;
}