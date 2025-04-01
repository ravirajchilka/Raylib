#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "chipmunk.h"

class PhysicsEngine {
public:
    PhysicsEngine();      // Constructor initializes physics
    ~PhysicsEngine();     // Destructor cleans up physics

    void update(float dt);     // Step the physics simulation
    cpVect get_box_position();   // Get the position of the box

private:
    cpSpace* space;
    cpBody* box_body;
    cpShape* box_shape;

    void init_physics();  // Internal function to initialize physics
};

#endif
