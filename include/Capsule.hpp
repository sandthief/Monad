#ifndef __CAPSULE__H
#define __CAPSULE__H

#include <string>
#include <Collision.hpp>
#include <Math.hpp>
#include <ScriptClass.hpp>


class Capsule : public ScriptClass {
  public:
    Point3D center;
    float   radius;
    float   height;

    Point3D tip();
    Point3D base();
    Vector  normal();
    Capsule();
    Capsule(float radiusIn,Point3D centerIn,float hightIn);

    static void exportToScript();

    Collision testCollision(Point3D a,Point3D b,Point3D c,std::string material);
    Collision testCollision(Capsule other,std::string material);
};

#endif
