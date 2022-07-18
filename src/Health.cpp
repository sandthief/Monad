#include <Health.hpp>


Health::Health(Point3D position) : Entity("resources/models/health.obj",Capsule(10,position,10)) {

}

void Health::update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {
        Entity::update(entities,collisions,gravity);

        yaw = yaw + (300* ticks);
        if(yaw == 360)
                yaw = 0;
}
