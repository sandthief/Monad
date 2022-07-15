#ifndef __SPHERE__H
#define __SPHERE__H

#include <Point.hpp>
#include <Math.hpp>
#include <Collision.hpp>

class Sphere  {
	public:
	Point3D center;
	float   radius;
	Sphere();
	Sphere(Point3D,float);
        bool isPointInside(Point3D b);
	Collision testCollision(Point3D a,Point3D b,Point3D c,std::string material);
	Collision testCollision(Sphere b);

};

#endif
