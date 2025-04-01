#include "PhysicsEngine.h"

// Constructor: Initialize Chipmunk2D physics
PhysicsEngine::PhysicsEngine() {
    init_physics();
}

// Destructor: Cleanup Chipmunk2D physics
PhysicsEngine::~PhysicsEngine() {
    cpShapeFree(_box_shape);
    cpBodyFree(_box_body);
    cpSpaceFree(_space);
}

// Internal function to initialize physics
void PhysicsEngine::init_physics() {
    _space = cpSpaceNew();
    cpSpaceSetGravity(_space, cpv(0, 500));  // Gravity

    // Box properties
    cpFloat mass = 1.0;
    cpFloat width = 50.0, height = 50.0;
    cpFloat moment = cpMomentForBox(mass, width, height);

    // Create box body
    _box_body = cpSpaceAddBody(_space, cpBodyNew(mass, moment));
    cpBodySetPosition(_box_body, cpv(400, 100));

    // Create box shape
    _box_shape = cpSpaceAddShape(_space, cpBoxShapeNew(_box_body, width, height, 0.0));
    cpShapeSetFriction(_box_shape, 0.7);
}

// Update physics simulation
void PhysicsEngine::update(float dt) {
    cpSpaceStep(_space, dt);
}

// Get box position
cpVect PhysicsEngine::get_box_position() {
    return cpBodyGetPosition(_box_body);
}
