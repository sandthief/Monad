#ifndef __QUATERNION__H
#define __QUATERNION__H

#include <Math.hpp>
#include <Point.hpp>

class Quaternion {
public:
	float x,y,z,w;

	void       computeW();
	void       normalize();
	Point3D    rotatePoint(Point3D);
	float      dot(Quaternion);
	Quaternion slerp(Quaternion);

	Quaternion(float,float,float);
	Quaternion();
	Quaternion operator * (Point3D);
	Quaternion operator * (Quaternion);
};

#endif
