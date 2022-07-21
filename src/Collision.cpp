#include <Common.hpp>

using namespace std;
using namespace chaiscript;

Collision::Collision() {
    collided  = false;
    depth     = 0;
    direction = Point3D(0.0f,0.0f,0.0f);
}
Collision::Collision(Point3D directionIn,float depthIn,std::string materialIn) {
    collided  = true;
    depth     = depthIn;
    direction = directionIn;
    material  = materialIn;
}

void Collision::exportToScript() {
        script.add(user_type<Collision>(),                         "Collision");
        script.add(constructor<Collision(Point3D,float,string)>(), "Collision");
        script.add(constructor<Collision()>(),                     "Collision");

        script.add(fun(&Collision::direction),                     "direction");
        script.add(fun(&Collision::depth),                         "depth");
        script.add(fun(&Collision::collided),                      "collided");
        script.add(fun(&Collision::material),                      "material");
}
