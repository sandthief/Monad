#include <Point.hpp>

Point2D::Point2D() {
	x = 0;
	y = 0;
}

Point2D::Point2D(float xIn, float yIn) {
	x = xIn;
	y = yIn;
}

Point3D::Point3D() {
	x = 0;
	y = 0;
	z = 0;
}
Point3D::Point3D(float xIn,float yIn,float zIn) {
	x = xIn;
	y = yIn;
	z = zIn;
}

float Point3D::dot(Point3D a, Point3D b) {
	return x * b.x + y * b.y + z * b.z;
}

Point3D Point3D::cross(Point3D b) {
	return Point3D(y * b.z - z * y, z * b.x - x * b.z, x * b.y - y * b.x);
}

float Point3D::distance(Point3D b) {
	 return sqrt(pow(b.x - x, 2) + pow(b.y - y, 2) + pow(b.z - z, 2) * 1.0);
}

Point2D Point3D::toPoint2D() {
	return Point2D(x,z);
}

Point3D Point3D::operator+(Point3D b) {
	return Point3D(x + b.x,y+b.y,z+b.z);
}
Point3D Point3D::operator+(float b) {
    return Point3D(x + b,y+b,z+b);
}
Point3D Point3D::operator-(Point3D b) {
	return Point3D(x - b.x,y-b.y,z-b.z);
}
Point3D Point3D::operator*(float b) {
	return Point3D(x *b,y * b,z * b);
}
Point3D Point3D::operator/(float b) {
	return Point3D(x / b,y / b,z / b);
}
bool Point3D::operator==(Point3D b) {
	if(x == b.x && y == b.y && z == b.z)
        return true;
    return false;
}

bool Point3D::operator!=(Point3D b) {
	if(x == b.x && y == b.y && z == b.z)
        return false;
    return true;
}
