#include "PhysicsEngine.h"

// Constructor: Initialize Chipmunk2D physics
PhysicsEngine::PhysicsEngine() {
    initPhysics();
}

// Destructor: Cleanup Chipmunk2D physics
PhysicsEngine::~PhysicsEngine() {
    cpShapeFree(boxShape);
    cpBodyFree(boxBody);
    cpSpaceFree(space);
}

// Internal function to initialize physics
void PhysicsEngine::initPhysics() {
    space = cpSpaceNew();
    cpSpaceSetGravity(space, cpv(0, 500));  // Gravity

    // Box properties
    cpFloat mass = 1.0;
    cpFloat width = 50.0, height = 50.0;
    cpFloat moment = cpMomentForBox(mass, width, height);

    // Create box body
    boxBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    cpBodySetPosition(boxBody, cpv(400, 100));

    // Create box shape
    boxShape = cpSpaceAddShape(space, cpBoxShapeNew(boxBody, width, height, 0.0));
    cpShapeSetFriction(boxShape, 0.7);
}

// Update physics simulation
void PhysicsEngine::update(float dt) {
    cpSpaceStep(space, dt);
}

// Get box position
cpVect PhysicsEngine::getBoxPosition() {
    return cpBodyGetPosition(boxBody);
}
