#include "PhysicsEngine.h"

// Constructor
PhysicsEngine::PhysicsEngine() : groundY(550.0f) { // Default ground position
    initPhysics();
}

// Initialize Physics
void PhysicsEngine::initPhysics() {
    // Create the physics space and set gravity
    space = cpSpaceNew();
    cpSpaceSetGravity(space, cpv(0, 1200)); // Gravity pointing downward

    // Box physics properties
    cpFloat mass = 1.0f;
    cpFloat width = 50.0f;
    cpFloat height = 50.0f;
    cpFloat moment = cpMomentForBox(mass, width, height);

    // Create dynamic box body and shape
    boxBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
    boxShape = cpSpaceAddShape(space, cpBoxShapeNew(boxBody, width, height, 0.0));
    
    // Set initial box position and friction
    cpBodySetPosition(boxBody, cpv(400, 100));
    cpShapeSetFriction(boxShape, 0.7);

    // Create static ground body and shape
    groundBody = cpSpaceGetStaticBody(space);
    groundShape = createGroundShape();
}

// Create Ground Shape Helper Function
cpShape* PhysicsEngine::createGroundShape() {
    return cpSpaceAddShape(space,
        cpSegmentShapeNew(groundBody, cpv(0, groundY), cpv(800, groundY), 5)); // Adjust thickness as needed
}

// Set Ground Position
void PhysicsEngine::setGroundPosition(float y) {
    groundY = y;

    if (groundShape) {
        cpSpaceRemoveShape(space, groundShape); // Remove old shape from space
        cpShapeFree(groundShape);              // Free memory of old shape
    }

    groundShape = createGroundShape();         // Create new shape at updated position
    cpShapeSetFriction(groundShape, 0.7);
}

// Update Physics Simulation
void PhysicsEngine::update(float dt) {
    cpSpaceStep(space, dt);
}

// Get Box Position
cpVect PhysicsEngine::getBoxPosition() const {
    return cpBodyGetPosition(boxBody);
}

// Destructor
PhysicsEngine::~PhysicsEngine() {
    if (boxShape) cpShapeFree(boxShape);
    if (boxBody) cpBodyFree(boxBody);
    if (groundShape) cpShapeFree(groundShape);
    if (space) cpSpaceFree(space);
}
