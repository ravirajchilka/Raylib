#include "PhysicsEngine.h"

//constructor
PhysicsEngine::PhysicsEngine() {
    _init_physics();
}    


//init phyiscs properties
void PhysicsEngine::_init_physics() {
    // create space and set gravity
    _space = cpSpaceNew();
    cpSpaceSetGravity(_space,cpv(0,1200));

    // box physics
    cpFloat mass = 1.0F;
    cpFloat width = 50.0F;
    cpFloat height = 50.0F;
    cpFloat moment = cpMomentForBox(mass,width,height);

    // create box body and shape
    _box_body = cpSpaceAddBody(_space,cpBodyNew(mass,moment));
    _box_shape = cpSpaceAddShape(_space,cpBoxShapeNew(_box_body,width,height,0.0));
    
    //set position and friction
    cpBodySetPosition(_box_body,cpv (400,100));
    cpShapeSetFriction(_box_shape,0.7);
}


//update physics
void PhysicsEngine::update(float dt) {
    cpSpaceStep(_space, dt);
}

// Get box position
cpVect PhysicsEngine::get_box_position() {
    return cpBodyGetPosition(_box_body);
}

//get box positions

//desctructor
PhysicsEngine::~PhysicsEngine() {
    cpShapeFree(_box_shape);
    cpBodyFree(_box_body);
    cpSpaceFree(_space);
}

