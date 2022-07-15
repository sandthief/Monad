#ifndef __ENTITY__H
#define __ENTITY__H

#include <Common.hpp>
#include <Point.hpp>
#include <Capsule.hpp>
#include <Model.hpp>

class Map;
class Player;

enum Team {
	ENEMY,
	FRIENDLY,
	OBJECT
};

class Entity {
	public:
		bool        onGround;
		bool        onLadder;
		bool     dead;
		float       yaw,pitch;
		Team        team;
		std::string name;
		Model*      model;
		Capsule     boundingShape;
		Point3D     velocity;


		float       yawToGoal;
		float       FOV = 180;
		float    vision = 500;
		Entity*  target;

		Entity();
		Entity(std::string,Capsule capsuleIn);

		void         processCollisions(std::vector<Collision> collisions);
		virtual void update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity);
		virtual void display();
		virtual void display2D();
		virtual void init();
		virtual bool canSee(Entity* other,Map* mapIn);
};

#endif
