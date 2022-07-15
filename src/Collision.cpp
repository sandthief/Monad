#include <Collision.hpp>

Collision::Collision() {
    collided  = false;
    depth     = 0;
    direction = Point3D(0.0f,0.0f,0.0f);
}
Collision::Collision(Point3D directionIn,float depthIn,std::string materialIn) {
    collided  = true;
    depth     = depthIn;
    direction = directionIn;
    material  = materialIn;
}
