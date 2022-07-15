#include <iostream>
#include <Math.hpp>

using namespace std;



float max(float a,float b) {
    if(a > b)
        return a;
    else
        return b;
}

float min(float a,float b) {
    if(a < b)
        return a;
    else
        return b;
}

float length(Point3D v) {
	return sqrt (v.x * v.x + v.y * v.y + v.z * v.z);
}

Point3D normalize(Point3D v) {
	Point3D vb;
	float l = length(v);
	if(0.0f == l) {
		return Point3D(0.0f, 0.0f, 0.0f);
	}
	vb.x = v.x / l;
	vb.y = v.y / l;
	vb.z = v.z / l;
	return vb;
}

static inline float dot(Point3D a, Point3D b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3D cross(Point3D a, Point3D b) {
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return Point3D(x, y, z);
}



Point3D closestPointOnLineSegment(Point3D A,Point3D B,Point3D Point) {
    Point3D AB = B - A;
    float t = dot(Point - A, AB) / dot(AB,AB);
    Point3D tmp = AB * min(max(t,0),1);
    return A + tmp;
}

Point3D closestPointOnTriangle(Point3D p, Point3D a,Point3D b,Point3D c) {
                Point3D ab    = b - a;
                Point3D ac    = c - a;
                Point3D bc    = c - b;

                float snom    = dot(p - a,ac);
                float sdenom  = dot(p - b,a - b);
                float tnom    = dot(p - a,ac);
                float tdenom  = dot(p - c,a - c);

                if(snom <= 0.0f && tnom <= 0.0f)
                        return a;

                float unom    = dot(p - b, bc);
                float udenom  = dot(p - c,b -c);

                if(sdenom <= 0.0f && unom <= 0.0f)
                        return b;
                if(tdenom <= 0.0f && udenom <= 0.0f)
                        return c;

                Point3D n     = cross(b - a, c- a);
                float  vc     = dot(n, cross(a - p,b - p));

                if(vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
                        return a + (ab * (snom / (snom + sdenom)));

                float va      = dot(n, cross(b - p, c - p));

                if(va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
                        return b + (bc * (unom / (unom + udenom)));

                float vb      = dot(n, cross(c - p, a - b));

                if(vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
                        return a + (ac * (tnom / (tnom + tdenom)));

                float u = va / (va + vb + vc);
                float v = vb / (va + vb + vc);
                float w = 1.0f - u -v;
                return a * u + b * v + c * w;


}

float distanceBetween(Point3D a,Point3D b) {
	float A = pow(b.x - a.x,2);
	float B = pow(b.y - a.y,2);
	float C = pow(b.z - a.z,2);
	return sqrt(A + B +C);
}

Point3D  projectPoint(Point3D origin,float yaw,float pitch,float distance) {
	float rad   = yaw*M_PI/180.0;
	 origin.x  -= sin(rad)*distance;
	 origin.z  -= cos(rad)*distance;
              rad   = pitch*M_PI/180.0;
	 origin.y  += sin(rad)*distance;
	return origin;
}
float toDegrees(float radians) {
	return radians * (180.0/M_PI);
}
float angleBetween(Point2D a, Point2D b, Point2D c )
{
    Point2D ab(b.x - a.x, b.y - a.y);
    Point2D cb(b.x - c.x, b.y - c.y);

    float dot = (ab.x * cb.x + ab.y * cb.y); // dot product
    float cross = (ab.x * cb.y - ab.y * cb.x); // cross product

    float alpha = atan2(cross, dot);

    return floor(alpha * 180.0f / M_PI + 0.5);
}

float clamp(float n, float min, float max) {
        if(n < min) return min;
        if(n > max) return max;
        return n;
}
