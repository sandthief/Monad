#ifndef __SCENE__H
#define __SCENE__H

#include <Common.hpp>
#include <Camera.hpp>
#include <Obj.hpp>
#include <Renderer.hpp>

class Scene : public Obj {
	public:

		std::vector<Entity*> entities;
		static void exportToScript();
		void load(std::string filename);
		void addEntity(Entity* added);
	        std::vector<Collision> testCollision(Entity* entity);
		void updateEntities(float gravity);
		void render(Camera* camera);


};

#endif
