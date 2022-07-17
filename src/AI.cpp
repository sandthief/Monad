#include <AI.hpp>

using namespace std;

AI::AI() {
}

AI::AI(std::string modelName,Capsule capsuleIn) : Entity(modelName,capsuleIn) {

        yaw      = 0;
        team     = ENEMY;
        target   = NULL;
        name     = "zombie";
        agitated = false;
}
void AI::update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {

}

void AI::approachTarget(Entity* other) {
	Point2D a      = other->boundingShape.center.toPoint2D();
	Point2D b      = boundingShape.center.toPoint2D();
	Point2D c      = projectPoint(boundingShape.center,yaw,pitch,vision).toPoint2D();
	float   angle  = angleBetween(a,b,c);
	float distance = distanceBetween(other->boundingShape.center, boundingShape.center);
	if(angle != yaw)
		yaw = yaw + (angle * 0.1);
	//if(distance > (other->boundingShape.radius + boundingShape.radius + 4))
		boundingShape.center = projectPoint(boundingShape.center,yaw,pitch,0.2);

}
