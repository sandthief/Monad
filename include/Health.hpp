#include <Entity.hpp>

using namespace std;

class Health : public Entity {
public:
        Health(Point3D position);
        void update(vector<Entity*> entities,std::vector<Collision> collisions,float gravity);
};
