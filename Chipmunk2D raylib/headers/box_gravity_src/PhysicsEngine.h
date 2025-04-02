#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "chipmunk.h"

class PhysicsEngine {
    public:

        PhysicsEngine();
        ~PhysicsEngine();

        void update(float dt);
        cpVect get_box_position();


    private:

        cpSpace *_space;
        cpBody *_box_body;
        cpShape *_box_shape;

        void _init_physics();

};


#endif
