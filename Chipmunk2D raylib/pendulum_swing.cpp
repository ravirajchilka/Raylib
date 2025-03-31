#include "raylib.h"
#include <chipmunk.h>
#include <cmath>
#include <iostream>

// Define screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Define physics time step
const float TIME_STEP = 1.0f / 60.0f;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum with Chipmunk2D + Raylib");
    SetTargetFPS(60);

    // Initialize Chipmunk2D physics
    cpVect gravity = cpv(0, 1200);  // Increase gravity even more
    cpSpace* space = cpSpaceNew();
    cpSpaceSetGravity(space, gravity);

    // Anchor point for the pendulum (fixed point)
    cpVect anchorPoint = cpv(SCREEN_WIDTH / 2, 100);

    // Create pendulum body (dynamic)
    cpFloat mass = 1.0f;
    cpFloat length = 100.0f;  // Even shorter length for faster swing
    cpFloat radius = 20.0f;   // Ball radius at the end of pendulum
    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
    cpBody* pendulumBody = cpBodyNew(mass, moment);
    cpBodySetPosition(pendulumBody, cpv(anchorPoint.x, anchorPoint.y + length));
    cpSpaceAddBody(space, pendulumBody);

    // Create shape for the pendulum bob
    cpShape* pendulumShape = cpCircleShapeNew(pendulumBody, radius, cpvzero);
    cpShapeSetFriction(pendulumShape, 0.5f);
    cpShapeSetDensity(pendulumShape, 1.0f);
    cpSpaceAddShape(space, pendulumShape);

    // Create pivot joint to attach pendulum to the anchor point
    cpConstraint* pivotJoint = cpPivotJointNew(pendulumBody, cpSpaceGetStaticBody(space), anchorPoint);
    cpSpaceAddConstraint(space, pivotJoint);

    // Give a much stronger initial push (higher angular velocity)
    cpBodySetAngularVelocity(pendulumBody, 20.0f);  // Increased initial velocity even more

    while (!WindowShouldClose()) {
        cpSpaceStep(space, TIME_STEP);

        // Get pendulum position
        cpVect pendulumPos = cpBodyGetPosition(pendulumBody);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw pendulum anchor
        DrawCircleV(Vector2{(float)anchorPoint.x, (float)anchorPoint.y}, 5, RED);

        // Draw pendulum arm
        DrawLineV(Vector2{(float)anchorPoint.x, (float)anchorPoint.y}, 
                  Vector2{(float)pendulumPos.x, (float)pendulumPos.y}, DARKGRAY);

        // Draw pendulum bob
        DrawCircleV(Vector2{(float)pendulumPos.x, (float)pendulumPos.y}, radius, BLUE);

        DrawText("Pendulum Simulation (Chipmunk2D + Raylib)", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    // Cleanup
    cpShapeFree(pendulumShape);
    cpBodyFree(pendulumBody);
    cpConstraintFree(pivotJoint);
    cpSpaceFree(space);
    CloseWindow();

    return 0;
}
