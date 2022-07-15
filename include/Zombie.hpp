#ifndef __ZOMBIE__H
#define __ZOMBIE__H
#include <Obj.hpp>
#include <AI.hpp>


class Zombie : public AI {
public:
        sf::Text word;
        sf::Text progress;
        int      index;
        sf::RectangleShape background;
        Model*              deadModel;
        Zombie(std::string modelName,Capsule capsuleIn);

        void update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity);

        void drawText();
        void display();
        void display2D();
        void testLetter(char key);

};

#endif
