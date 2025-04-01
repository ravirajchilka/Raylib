#include "PhysicsEngine.h"

// Constructor: Initialize Chipmunk2D physics
PhysicsEngine::PhysicsEngine() {
    init_physics();
}

// Destructor: Cleanup Chipmunk2D physics
PhysicsEngine::~PhysicsEngine() {
    cpShapeFree(box_shape);
    cpBodyFree(box_body);
    cpSpaceFree(space);
}

// Internal function to initialize physics
void PhysicsEngine::init_physics() {
    space = cpSpaceNew();
    cpSpaceSetGravity(space, cpv(0, 500));  // Gravity

    // Box properties
    cpFloat mass = 1.0;
    cpFloat width = 50.0, height = 50.0;
    cpFloat moment = cpMomentForBox(mass, width, height);

    // Create box body
    box_body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(box_body, cpv(400, 100));

    // Create box shape
    box_shape = cpSpaceAddShape(space, cpBoxShapeNew(box_body, width, height, 0.0));
    cpShapeSetFriction(box_shape, 0.7);
}

// Update physics simulation
void PhysicsEngine::update(float dt) {
    cpSpaceStep(space, dt);
}

// Get box position
cpVect PhysicsEngine::get_box_position() {
    return cpBodyGetPosition(box_body);
}
