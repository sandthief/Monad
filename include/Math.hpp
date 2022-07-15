#include <Common.hpp>
#include <Point.hpp>

#ifndef __MATH__HPP
#define __MATH__HPP

float    max(float a,float b);
float    min(float a,float b);
float    length(Point3D v);
Point3D  normalize(Point3D v);
float    normalize(float);
float    dot(Point3D a, Point3D b);
Point3D  cross(Point3D a, Point3D b);
Point3D  closestPointOnLineSegment(Point3D A,Point3D B,Point3D Point);
float    distanceBetween(Point3D a,Point3D b);
Point3D  projectPoint(Point3D origin,float yaw,float pitch,float distance);
float    angleBetween(Point2D a,Point2D b,Point2D c);
Point3D  closestPointOnTriangle(Point3D p, Point3D a,Point3D b,Point3D c);
float    clamp(float n, float min, float max);

#endif
