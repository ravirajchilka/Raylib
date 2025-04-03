#include "raylib.h"
#include <iostream>
#include <chrono>
#include <thread>

class Ball {
public:
    float radius;
    Vector2 pos;
    Color color;
    float velocity;
    float velocityY;
    float gravity;

    Ball(float x, float y, float r, Color c)
        : pos{x, y}, radius{r}, color{c}, velocity(5), velocityY(0), gravity(0.5f) {}

    void draw_ball() {
        DrawCircleV(pos, radius, color);
    }

    void move_ball_forward() {
        pos.x += velocity;
    }

    void move_ball_backward() {
        pos.x -= velocity;
    }

    void ball_jump() {
        if (pos.y >= GetScreenHeight() - 100) { // Ensures ball is on the ground
            velocityY = -10.0f;
            std::thread(&Ball::reset_jump, this).detach(); // Reset mechanism in thread
        }
    }

    void update(float groundY) {
        velocityY += gravity;
        pos.y += velocityY;

        if (pos.y >= groundY - radius) {
            pos.y = groundY - radius;
            velocityY = 0;
        }
    }

private:
    void reset_jump() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
};

class Ground {
public:
    float groundY;

    Ground(float y) : groundY(y) {}

    void draw_ground() {
        DrawRectangle(0, groundY, GetScreenWidth(), 80, BROWN);
    }
};

int main() {
    InitWindow(800, 600, "Jump Simulation");
    SetTargetFPS(60);

    float groundY = GetScreenHeight() - 80;
    Ball ball(100, groundY - 20, 20, RED);
    Ground ground(groundY);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) {
            ball.move_ball_forward();
        }
        if (IsKeyDown(KEY_LEFT)) {
            ball.move_ball_backward();
        }
        if (IsKeyPressed(KEY_UP)) {
            ball.ball_jump();
        }

        ball.update(groundY);

        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        ball.draw_ball();
        ground.draw_ground();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
