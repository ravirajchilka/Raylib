#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "chipmunk.h"

class PhysicsEngine {
public:
    PhysicsEngine();      // Constructor initializes physics
    ~PhysicsEngine();     // Destructor cleans up physics

    void update(float dt);     // Step the physics simulation
    cpVect getBoxPosition();   // Get the position of the box

private:
    cpSpace* space;
    cpBody* boxBody;
    cpShape* boxShape;

    void initPhysics();  // Internal function to initialize physics
};

#endif
