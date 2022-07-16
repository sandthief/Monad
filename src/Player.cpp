#include <Player.hpp>
#include <Zombie.hpp>
#include <GUI.hpp>
using namespace std;

bool menuMode = false;
Player::Player() {
        boundingShape = Capsule( /* radius */ 16,Point3D(0.0f,0.0f,0.0f),/* height */ 30);
	team          = FRIENDLY;
        target        = NULL;

}

void Player::display() {

}

void Player::move(float direction) {
    velocity.z = velocity.z + (-cos((direction + yaw) * (M_PI/180.0f)) * moveVelocity);
    velocity.x = velocity.x + (-sin((direction + yaw) * (M_PI/180.0f)) * moveVelocity);
    if(onLadder)
        velocity.y = velocity.y + sin((pitch) * (M_PI/180.0f));
}

void Player::update(vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {
                if(!window->menuMode()) {
                        Point2D position = window->getMousePosition();
                        yaw   +=lookVelocity*(window->width()/2-position.x);
                        pitch += lookVelocity*(window->height()/2-position.y);
                        window->setMousePosition(Point2D(window->width()/2,window->height()/2));

                        //Looking
                	if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                                pitch   += lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
                        	yaw += lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed( sf::Keyboard::K)){
                        	pitch -= lookVelocity;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
                                yaw -= lookVelocity;
                        }

                        if(onGround)
                                moveVelocity = 2.0f;
                        else if(onLadder)
                                moveVelocity = 0.5f;
                        else
                                moveVelocity = 0.1f;

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
                                        velocity.y = velocity.y + 10;
                        }
                }

    Camera::update();
    Entity::update(entities,collisions,gravity);
}

void Player::jump() {
        velocity.y = velocity.y + 2;
}
