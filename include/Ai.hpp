#ifndef __AI__H
#define __AI__H

#include <Common.hpp>
#include <Entity.hpp>

class AI : public Entity {
        public:
                bool     agitated;

                AI();
                AI(std::string modelName,Capsule capsuleIn);
                virtual void update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity);
                void approachTarget(Entity* other);
};

#endif
