#include <Zombie.hpp>

using namespace std;
Zombie::Zombie(std::string modelName,Capsule capsuleIn) : AI( modelName,capsuleIn) {
                yaw   = 90;
                FOV   = 90;
                index = 0;
                dead  = false;
                /*
                word.setFont(horrorFont);
                progress.setFont(horrorFont);
                // set the string to display
                word.setString("Computer");


                deadModel = new Obj();
		deadModel->load("zombie_dead.obj");*/
}
void Zombie::testLetter(char letter) {
        if(tolower(word.getString()[index]) == letter) {
                progress.setString(word.getString().substring(0,index+1));
                index++;
        }
        if(word.getString() == progress.getString()) {
                dead =true;
                target->target = NULL;
        }
}
void Zombie::update(std::vector<Entity*> entities,std::vector<Collision> collisions,float gravity) {
        if(target == NULL) {
          for(int e = 0; e < entities.size(); e++) {
            if(entities[e] != this){
              if(entities[e]->team != team  && entities[e]->team != OBJECT ) {
                if(entities[e]->canSee(this,NULL)) {
                  target  = entities[e];
                }
              }
            }
          }
        }
        else if (!dead) {
                if(canSee(target,NULL))
                        approachTarget(target);
                if(!target->canSee(this,NULL)) {
                        target = NULL;
                }
        }
        else if (dead && target == this){
                target->target = NULL;
                // menuMode = false;
        }



        Entity::update(entities,collisions,gravity);


        //AI::update(entities,collisions,gravity);
}

void Zombie::display2D() {



        if(target != NULL && !dead) {
                if(target->target == this){
                        background.setFillColor(sf::Color::Black);
                        word.setFillColor(sf::Color::Red);
                        progress.setFillColor(sf::Color::Yellow);
                }
                else {
                        background.setFillColor(sf::Color(0,0,0,150));
                        word.setFillColor(sf::Color(255,0,0,150));
                }
                drawText();
        }
}

void Zombie::drawText() {
/*
        GLint viewport[4];
        GLdouble modelview[16];
        GLdouble viewVector[3];
        GLdouble projection[16];

        GLdouble winX, winY, winZ;//2D point

        //get the matrices
        glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

        viewVector[0]=modelview[8];
        viewVector[1]=modelview[9];
        viewVector[2]=modelview[10];

        glGetDoublev( GL_PROJECTION_MATRIX, projection );
        glGetIntegerv( GL_VIEWPORT, viewport );

        int   res           = gluProject(boundingShape.center.x,boundingShape.center.y+ (boundingShape.height/2),boundingShape.center.z,modelview,projection,viewport,&winX,&winY,&winZ);
        float distance      = distanceBetween(target->boundingShape.center,boundingShape.center);
        float characterSize = 32.00f*(100.0f/distance);
        float wordWidth     = word.getLocalBounds().width;
        float wordHeight    = word.getLocalBounds().height;
        float left          = winX-(wordWidth/2);
        float top           = window->getSize().y-winY;
        float border        = characterSize/30;
        float margin        = characterSize/10;



        word.setCharacterSize(characterSize);
        word.setPosition(left,top);

        progress.setPosition(left,top+wordHeight);
        progress.setCharacterSize(characterSize);

        background.setPosition(left-margin,top+(margin * 1.2));
        background.setSize(sf::Vector2f(wordWidth + (margin*2),(wordHeight* 2)+ (margin*2)));
        background.setOutlineThickness(border);
        background.setOutlineColor(sf::Color::White);

        window->pushGLStates();
        window->draw(background);
        window->draw(word);
        window->draw(progress);
        window->popGLStates();*/

}

void Zombie::display() {
        glPushMatrix();
        glTranslatef(boundingShape.center.x,boundingShape.center.y,boundingShape.center.z);
        glRotatef(pitch,1.0,0.0,0.0);
        glRotatef(yaw,0.0,1.0,0.0);

        if(dead) {
                if(deadModel!= NULL) {
                        deadModel->render();

                }
        }
        else {
                if(model != NULL)
                        model->render();
        }

        glPopMatrix();

}
