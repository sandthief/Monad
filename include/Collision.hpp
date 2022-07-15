#ifndef __COLLISION__H
#define __COLLISION__H
#include <Common.hpp>
#include <Point.hpp>

class Collision {
    public:
        Point3D direction;
        float   depth;
        bool    collided;
        std::string material;

    Collision();
    Collision(Point3D directionIn,float depthIn,std::string materialIn);
};

#endif
