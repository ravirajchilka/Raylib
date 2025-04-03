/*

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

*/


#include <raylib.h>
#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>

constexpr std::int16_t SCREEN_WIDTH = 1700;
constexpr std::int16_t SCREEN_HEIGHT = 800;
const Vector2 ball_init_pos = {150.0F, SCREEN_HEIGHT - 150.0F};

class Ball {
    public : 
        Vector2 pos = ball_init_pos;
        std::int8_t radius = 0;
        std::int8_t velocity = 0;
        Color color = RED;
		bool is_jumping = false;

        void draw_ball() {
            DrawCircle(pos.x,pos.y,static_cast<float>(radius),color);
        }

		void move_forward(std::int8_t time) {
			pos.x += velocity;
		}

		void move_backward() {
			pos.x -= velocity;
		}

		void ball_jump_and_reset(std::int8_t air_time) {
			is_jumping = true;
			for(std::int8_t i = 0; i <= 20; i++) {
				pos.y -= 5;
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
			
			std::this_thread::sleep_for(std::chrono::milliseconds(air_time));

			for(std::int8_t i = 0; i <= 20; i++) {
				pos.y += 5;
				std::this_thread::sleep_for(std::chrono::milliseconds(16));
			}
			pos.y = ball_init_pos.y;
			is_jumping = false;
		}

};

int main() {
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"test");
    SetTargetFPS(60);
    
	Ball ball;
	ball.radius = 10;
	ball.velocity = 5;

    while(!WindowShouldClose()) {
 
 	   	// events
		if(IsKeyDown(KEY_RIGHT)) {
			//ball.move_forward();
			std::thread(&Ball::move_forward,&ball,20).detach();
		}
		if(IsKeyDown(KEY_LEFT)) {
			ball.move_backward();
		}
		if(IsKeyDown(KEY_UP)) {
			if(!ball.is_jumping) {
				std::thread(&Ball::ball_jump_and_reset,&ball,50).detach();
			}
		}
    	// updates 
    	// drawing

       BeginDrawing();
			ClearBackground(LIGHTGRAY);
			ball.draw_ball();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

