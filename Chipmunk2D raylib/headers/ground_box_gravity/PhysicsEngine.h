#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <chipmunk.h>

class PhysicsEngine {
public:
    PhysicsEngine();               // Constructor to initialize physics engine
    ~PhysicsEngine();              // Destructor to clean up resources

    void setGroundPosition(float y);   // Change the vertical position of the ground
    void update(float dt);             // Update physics simulation step-by-step

    cpVect getBoxPosition() const;     // Get current position of the box

private:
    void initPhysics();                // Initialize Chipmunk2D physics objects and space
    cpShape* createGroundShape();      // Helper function to create a new ground shape

private:
    float groundY;                     // Vertical position of the ground

    cpSpace* space;                    // Chipmunk2D physics space object

    cpBody* boxBody;                   // Dynamic body for the box
    cpShape* boxShape;                 // Shape for the box

    cpBody* groundBody;                // Static body for the ground
    cpShape* groundShape;              // Shape for the ground line segment
};

#endif /* PHYSICS_ENGINE_H */
