#include <Common.hpp>

using namespace std;
using namespace chaiscript;

Sphere::Sphere() {
}
Sphere::Sphere(Point3D centerIn,float radiusIn) {
	center = centerIn;
	radius = radiusIn;
}

void Sphere::exportToScript() {
	script.add(user_type<Sphere>(),                  "Sphere");
        script.add(constructor<Sphere(Point3D,float)>(), "Sphere");
        script.add(constructor<Sphere()>(),              "Sphere");

        script.add(fun(&Sphere::center),                 "center");
	script.add(fun(&Sphere::radius),                 "radius");

        //script.add(fun(&Sphere::isPointInside),          "isPointInside");

	Collision (Sphere::*testTriangle)(Point3D,Point3D,Point3D,string) = &Sphere::testCollision;
	script.add(fun(testTriangle),                  "testCollision");

	Collision (Sphere::*testSphere)(Sphere) = &Sphere::testCollision;
	script.add(fun(testSphere),                  "testCollision");

}

Collision Sphere::testCollision(Sphere b) {
	Collision out;
	float dist  = distanceBetween(center,b.center);
	float r2 = (radius*2) + (b.radius*2);
	if(dist < r2) {
		out.collided  = true;
		out.direction = normalize(center - b.center);
		out.depth     = abs(dist -r2);

	}
	else
		out.collided = false;
	return out;
}

Collision Sphere::testCollision(Point3D a,Point3D b,Point3D c,string material) {
    Point3D N = normalize(cross(b - a, c - a)); // plane normal
    float dist = dot(center - a, N); // signed distance between sphere and plane

    if(dist < -radius || dist > radius)
      return Collision(); // no intersection

    Point3D point0 = center - N * dist; // projected sphere center on triangle plane

    // Now determine whether point0 is inside all triangle edges:
    Point3D c0 = cross(point0 - a, b - a);
    Point3D c1 = cross(point0 - b, c - b);
    Point3D c2 = cross(point0 - c, a - c);
    bool inside = dot(c0, N) <= 0 && dot(c1, N) <= 0 && dot(c2, N) <= 0;


    float radiussq = radius * radius; // sphere radius squared

    // Edge 1:
    Point3D point1  = closestPointOnLineSegment(a, b, center);
    Point3D v1      = center - point1;
    float distsq1   = dot(v1, v1);
    bool intersects = distsq1 < radiussq;

    // Edge 2:
    Point3D point2  = closestPointOnLineSegment(b, c, center);
    Point3D v2      = center - point2;
    float distsq2   = dot(v2, v2);
    intersects     |= distsq2 < radiussq;

    // Edge 3:
    Point3D point3 = closestPointOnLineSegment(c, a, center);
    Point3D v3     = center - point3;
    float distsq3  = dot(v3, v3);
    intersects    |= distsq3 < radiussq;

    if(inside || intersects) {
        Point3D best_point = point0;
        Point3D intersection_vec;

        if(inside) {
            intersection_vec = center - point0;
        }
        else  {
            Point3D d = center - point1;
            float best_distsq = dot(d, d);
            best_point = point1;
            intersection_vec = d;

            d = center - point2;
            float distsq = dot(d, d);
            if(distsq < best_distsq) {
                distsq = best_distsq;
                best_point = point2;
                intersection_vec = d;
            }

            d = center - point3;
            distsq = dot(d, d);
            if(distsq < best_distsq) {
                distsq = best_distsq;
                best_point = point3;
                intersection_vec = d;
            }
        }

    float len = length(intersection_vec);
    float penetration_depth = radius - len;

    if(penetration_depth < 0.0f)
    	return Collision();

    return Collision(N,penetration_depth,material);
  }
   return Collision();

}
