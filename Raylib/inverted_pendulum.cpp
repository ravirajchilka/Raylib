#include <raylib.h>
#include <cmath>

// Screen properties
const int screenWidth = 800;
const int screenHeight = 600;

// Pendulum properties
const float pendulumLength = 200.0f;
const float pendulumMass = 1.0f;
const float gravity = 9.81f;
const float torqueForce = 2.0f; // Torque applied when moving left/right

// Pendulum state
float angle = 0.0f; // Angle from the vertical (in radians)
float angularVelocity = 0.0f;
float angularAcceleration = 0.0f;

// Update pendulum physics
void UpdatePendulum(float dt) {
    // Calculate angular acceleration due to gravity
    float gravityTorque = (gravity / pendulumLength) * sin(angle);

    // Apply torque based on user input
    float appliedTorque = 0.0f;
    if (IsKeyDown(KEY_RIGHT)) {
        appliedTorque = torqueForce;
    } else if (IsKeyDown(KEY_LEFT)) {
        appliedTorque = -torqueForce;
    }

    // Calculate net angular acceleration
    angularAcceleration = gravityTorque + appliedTorque;

    // Update angular velocity and angle
    angularVelocity += angularAcceleration * dt;
    angle += angularVelocity * dt;
}

// Render pendulum
void RenderPendulum() {
    // Calculate pendulum end position
    Vector2 origin = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 end = {
        origin.x + pendulumLength * sin(angle),
        origin.y - pendulumLength * cos(angle)
    };

    // Draw pendulum
    DrawLineV(origin, end, BLACK);
    DrawCircleV(end, 10, RED);
}

// Main function
int main() {
    InitWindow(screenWidth, screenHeight, "Inverted Pendulum Simulation with Continuous Torque");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Update physics
        UpdatePendulum(dt);

        // Render
        BeginDrawing();
            ClearBackground(RAYWHITE);
            RenderPendulum();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}