#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include <Common.hpp>
#include <Camera.hpp>

class Player : public Camera {
	public:
		Player();
		void display();
		void move(float direction);
		void jump();
		void update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity);
};

extern bool typingMode;
extern std::map<std::string,bool>  key;

#endif
