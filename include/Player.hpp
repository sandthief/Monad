#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include <Camera.hpp>

class Player : public Camera {
	public:
		Player();

		static void exportToScript();

		void display();
		void move(float direction);
		void update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity);

};

extern bool menuMode;
extern std::map<std::string,bool>  key;

#endif
