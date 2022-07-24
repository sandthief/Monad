#include <Common.hpp>

using namespace std;
using namespace chaiscript;

bool menuMode = false;
Player::Player() {
        boundingShape = Capsule( /* radius */ 16,Point3D(0.0f,100.0f,0.0f),/* height */ 20);
	team          = FRIENDLY;
        target        = NULL;

}

void Player::exportToScript() {
        script.add(base_class<Entity, Player>());
        script.add(user_type<Player>(),                            "Player");
}

void Player::display() {

}

void Player::move(float direction) {
    velocity.z = velocity.z + ((-cos((direction + yaw) * (M_PI/180.0f)) * moveVelocity) * ticks);
    velocity.x = velocity.x + ((-sin((direction + yaw) * (M_PI/180.0f)) * moveVelocity)  * ticks);
    if(onLadder)
        velocity.y = velocity.y + ((sin((pitch) * (M_PI/180.0f)) * moveVelocity) * ticks);
}

void Player::update(vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {
                if(!menuMode) {
                        Point2D position = window->getMousePosition();
                        yaw   +=lookVelocity*(window->width()/2-position.x);
                        pitch += lookVelocity*(window->height()/2-position.y);
                        window->setMousePosition(Point2D(window->width()/2,window->height()/2));

                        //Looking
                	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                                pitch   += ticks * lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
                        	yaw += ticks * lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed( sf::Keyboard::K)){
                        	pitch -= ticks * lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                                yaw -= ticks * lookVelocity;
                        }

                        if(onGround)
                                moveVelocity = 200.0f;
                        else if(onLadder)
                                moveVelocity = 150.0f;
                        else
                                moveVelocity = 10.0f;

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                                move(0);
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                                move(90);
                        }
                        if(sf::Keyboard::isKeyPressed( sf::Keyboard::S)){
                                move(180);
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                                move(270);
                        }

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                                if(onGround)
                                        velocity.y = velocity.y + ((moveVelocity * 10) * ticks);
                        }
                }

    Camera::update();
    Entity::update(entities,collisions,gravity);
}
