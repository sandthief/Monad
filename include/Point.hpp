#ifndef __POINT__H
#define __POINT__H

#include <ScriptClass.hpp>
#include <math.h>

class Point2D : public ScriptClass  {
public:
	float x,y;
	Point2D();
	Point2D(float xIn, float yIn);

	static void exportToScript();
};

class Point3D {
public:
	float x,y,z;
	Point3D();
	Point3D(float,float,float);

	static void    exportToScript();
	       Point2D toPoint2D();
	       float   distance(Point3D b);
               float   dot(Point3D a, Point3D b);
               Point3D cross(Point3D b);

	Point3D operator+(Point3D b);
    Point3D operator+(float b);
	Point3D operator-(Point3D b);
    bool    operator==(Point3D b);
    bool    operator!=(Point3D b);
    Point3D operator*(float b);
    Point3D operator/(float b);


};

#define Vector Point3D
#endif
