#ifndef __COLLISION__H
#define __COLLISION__H

#include <Point.hpp>
#include <ScriptClass.hpp>

class Collision : public ScriptClass {
    public:
        Point3D direction;
        float   depth;
        bool    collided;
        std::string material;

    Collision();
    Collision(Point3D directionIn,float depthIn,std::string materialIn);

    static void exportToScript();
};

#endif
