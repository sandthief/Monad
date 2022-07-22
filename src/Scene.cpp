#include <Scene.hpp>

using namespace std;
using namespace chaiscript;

void Scene::exportToScript() {
        script.add(base_class<Obj, Scene>());
        script.add(user_type<Scene>(),                            "Scene");
        script.add(constructor<Scene()>(),                       "Scene");
        script.add(fun(&Scene::load),                            "load");
	script.add(fun(&Scene::addEntity),                       "addEntity");

}

void Scene::addEntity(Entity* added) {
	entities.push_back(added);
}

void Scene::load(std::string filename) {
	Obj::load(filename);


}

void Scene::updateEntities(float gravity) {
	for(int e = 0; e < entities.size(); e++) {
		vector<Collision> collisions = testCollision(entities[e]);
		entities[e]->update(entities,collisions,gravity);
	}
}

void Scene::render(Camera* camera) {
	Obj::render();
	for(int e = 0; e < entities.size(); e++) {
		for(int o = 0; o < entities.size(); o++) {
			if(distanceBetween(entities[o]->boundingShape.center,camera->boundingShape.center) <
			   distanceBetween(entities[e]->boundingShape.center,camera->boundingShape.center)) {
				Entity* tmp = entities[e];
				entities[e] = entities[o];
				entities[o] = tmp;
			}
		}
	}
	for(int e = 0; e < entities.size(); e++) {
		entities[e]->display();
		entities[e]->display2D();
	}
}

vector<Collision> Scene::testCollision(Entity* entity) {
	vector<Collision> out;
	for(int g = 0; g < groups.size(); g++) {
				if(groups[g].material != "outline"  && groups[g].name.find("noCollision") == std::string::npos  ) {
					for(int f = 0; f < groups[g].faces.size(); f++) {
					    OBJFace      face  = groups[g].faces[f];
					    Point3D        a   = verticies[face.vertexIndecies[0]-1];
					    Point3D        b   = verticies[face.vertexIndecies[1]-1];
					    Point3D        c   = verticies[face.vertexIndecies[2]-1];
					    Collision     hit   = entity->boundingShape.testCollision(a,b,c,groups[g].material);
					    if(hit.collided) {
						out.push_back(hit);
					}
				}
			}
	}

	for(int e = 0; e < entities.size(); e++) {
		if(entities[e] != entity) {
			Collision hit = entity->boundingShape.testCollision(entities[e]->boundingShape," ");
			if(hit.collided)
				out.push_back(hit);
		}
	}


    return out;
}
