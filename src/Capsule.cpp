#include <Capsule.hpp>
#include <Sphere.hpp>
#include <iostream>
using namespace std;

Capsule::Capsule() {

}

Point3D Capsule::tip() {
        return Point3D(center.x,center.y + height/2.0f,center.z);
}
Point3D Capsule::base() {
        return Point3D(center.x,center.y - height/2.0f,center.z);
}
Capsule::Capsule(float radiusIn,Point3D centerIn,float heightIn) {
  radius = radiusIn;
  center = centerIn;
  height = heightIn;

}

Collision Capsule::testCollision(Point3D a,Point3D b,Point3D c,string material) {

        Point3D bestPoint = center;

        Point3D point0 = closestPointOnLineSegment(tip(),base(),a);
        Point3D point1 = closestPointOnLineSegment(tip(),base(),b);
        Point3D point2 = closestPointOnLineSegment(tip(),base(),c);

        float dist0 = distanceBetween(a,point0);
        float dist1 = distanceBetween(b,point1);
        float dist2 = distanceBetween(c,point2);

        if(dist0 < dist1) {
                if(dist2 < dist0)
                        bestPoint = point2;
                else
                        bestPoint = point0;
        }
        else {
                if(dist2 < dist1)
                        bestPoint = point2;
                else
                        bestPoint = point1;
        }


        Sphere bestSphere(bestPoint,radius);
        return bestSphere.testCollision(a,b,c,material);
}


Collision Capsule::testCollision(Capsule b,string material) {
        // capsule A:
        Point3D a_LineEndOffset = normal() * radius;
        Point3D a_A = base() + a_LineEndOffset;
        Point3D a_B = tip() - a_LineEndOffset;

        // capsule B:
        Point3D b_LineEndOffset =b.normal() * b.radius;
        Point3D b_A = b.base() + b_LineEndOffset;
        Point3D b_B = b.tip() - b_LineEndOffset;

        // vectors between line endpoints:
        Point3D v0 = b_A - a_A;
        Point3D v1 = b_B - a_A;
        Point3D v2 = b_A - a_B;
        Point3D v3 = b_B - a_B;

        // squared distances:
        float d0 = dot(v0, v0);
        float d1 = dot(v1, v1);
        float d2 = dot(v2, v2);
        float d3 = dot(v3, v3);

        // select best potential endpoint on capsule A:
        Point3D bestA;
        if (d2 < d0 || d2 < d1 || d3 < d0 || d3 < d1)
        {
          bestA = a_B;
        }
        else
        {
          bestA = a_A;
        }

        // select point on capsule B line segment nearest to best potential endpoint on A capsule:
        Point3D bestB = closestPointOnLineSegment(b_A, b_B, bestA);


        // now do the same for capsule A segment:
        bestA = closestPointOnLineSegment(a_A, a_B, bestB);

        Point3D penetration_normal = bestA - bestB;
        float len = length(penetration_normal);
        penetration_normal = penetration_normal / len;  // normalize
        float penetration_depth = radius + b.radius - len;
        bool intersects = penetration_depth > 0.001;

        if(intersects)
                return Collision(penetration_normal,penetration_depth,material);
        return Collision();
}

Vector  Capsule::normal() {
        return normalize(tip() - base());
}
