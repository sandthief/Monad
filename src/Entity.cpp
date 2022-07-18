#include <Map.hpp>
#include <MD5.hpp>

using namespace std;

Entity::Entity() {
	team = OBJECT;
}

Entity::Entity(std::string modelName,Capsule capsuleIn) {
	yaw    = 0.0f;
	pitch  = 0.0f;
	team = OBJECT;
	name = "object";

	boundingShape = capsuleIn;
	if (modelName.find(".obj") != std::string::npos) {
    		model = new Obj();
		model->load(modelName);
	}
	else if (modelName.find(".md5mesh") != std::string::npos) {
	    	model = new MD5Model();
		model->load(modelName);
	}
}



void Entity::init() {

}

void Entity::processCollisions(std::vector<Collision> collisions) {
	for(int c = 0; c < collisions.size(); c++) {
		float x = collisions[c].direction.x * collisions[c].depth;
		float y = collisions[c].direction.y * collisions[c].depth;
		float z = collisions[c].direction.z * collisions[c].depth;

		if(collisions[c].material == "ladder") {
			onLadder = true;
		}
		else
			velocity = velocity + Point3D(x,y,z);

		Vector A(collisions[c].direction);
		Vector B(0.0f,1.0f,0.0f);

		float dotProduct = dot(A,B);
		float angle      = acos(dotProduct) * 180/M_PI;
		if(angle < 60.0f){
			onGround = true;
		}


	}

	if(velocity.x != 0.0f || velocity.y != 0.0f || velocity.z != 0.0f) {
		float speed = ticks * 10;
		boundingShape.center = boundingShape.center + (velocity * speed);
		velocity = velocity -  (velocity * speed);
	}
}

void Entity::update(vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {
	onGround = false;
	onLadder = false;
	processCollisions(collisions);
	if(!onLadder)
		velocity.y = velocity.y + (gravity * ticks);
}

void Entity::display() {
	glPushMatrix();
	glTranslatef(boundingShape.center.x,boundingShape.center.y,boundingShape.center.z);
	glRotatef(pitch,1.0,0.0,0.0);
	glRotatef(yaw,0.0,1.0,0.0);

	if(model != NULL)
		model->render();

	glPopMatrix();

}

void Entity::display2D() {

}


bool Entity::canSee(Entity* other, Map* map) {
  float distance = distanceBetween(other->boundingShape.center, boundingShape.center);
	if(distance < vision) {
		Point2D a      = other->boundingShape.center.toPoint2D();
		Point2D b      = boundingShape.center.toPoint2D();
		Point2D c      = projectPoint(boundingShape.center,yaw,pitch,vision).toPoint2D();
		float   angle  = angleBetween(a,b,c);
		if(abs(angle) < (FOV/2))
			return true;
	}
	return false;
}
