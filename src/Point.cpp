#include <Common.hpp>

using namespace std;
using namespace chaiscript;

Point2D::Point2D() {
	x = 0;
	y = 0;
}

Point2D::Point2D(float xIn, float yIn) {
	x = xIn;
	y = yIn;
}

void Point2D::exportToScript() {
    script.add(user_type<Point2D>(),                "Point2D");
    script.add(constructor<Point2D(float,float)>(), "Point2D");
    script.add(constructor<Point2D()>(),            "Point2D");
    script.add(fun(&Point2D::x),                    "x");
    script.add(fun(&Point2D::y),                    "y");
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

void Point3D::exportToScript() {
    script.add(user_type<Point3D>(),                      "Point3D");
    script.add(constructor<Point3D(float,float,float)>(), "Point3D");
    script.add(constructor<Point3D()>(),                  "Point3D");
    script.add(fun(&Point3D::x),                          "x");
    script.add(fun(&Point3D::y),                          "y");
    script.add(fun(&Point3D::z),                          "z");

    script.add(fun(&Point3D::toPoint2D),                  "toPoint2D");
    script.add(fun(&Point3D::distance),                   "distance");
    script.add(fun(&Point3D::dot),                        "dot");
    script.add(fun(&Point3D::cross),                      "cross");

    // There's got to be a better way than this
    Point3D (Point3D::*addFloat)(float) = &Point3D::operator+;
    script.add(fun(addFloat),                  "+");

    Point3D (Point3D::*addPoint)(Point3D) = &Point3D::operator+;
    script.add(fun(addPoint),                  "+");

    Point3D (Point3D::*subPoint)(Point3D) = &Point3D::operator-;
    script.add(fun(subPoint),                  "-");

    script.add(fun(&Point3D::operator==),      "==");
    script.add(fun(&Point3D::operator!=),      "!=");
    script.add(fun(&Point3D::operator*),       "*");
    script.add(fun(&Point3D::operator/),       "/");
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
