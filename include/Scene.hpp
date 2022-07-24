#ifndef __SCENE__H
#define __SCENE__H

#include <Camera.hpp>
#include <Obj.hpp>
#include <Renderer.hpp>
#include <chaiscript/chaiscript.hpp>

class Scene : public Obj {
	public:

		std::vector<Entity*> entities;
		static void exportToScript();
		virtual void load(std::string filename);
		void addEntity(Entity* added);
	        virtual std::vector<Collision> testCollision(Entity* entity);
		void updateEntities(float gravity);
		void render(Camera* camera);
		void renderRecursive(Camera* camera,int passes);


};

#endif
