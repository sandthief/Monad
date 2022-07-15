#ifndef __MAP__H
#define __MAP__H

#include <Common.hpp>
#include <Camera.hpp>
#include <Obj.hpp>
#include <Renderer.hpp>

class Map : public Obj {
	public:
		GLuint               lightmap;
		std::vector<Entity*> entities;

		void load(std::string filename);
	        std::vector<Collision> testCollision(Entity* entity);
		void updateEntities(float gravity);
		void render(Camera* camera);
		void generateLightmap();

};

#endif
