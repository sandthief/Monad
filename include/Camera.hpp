#ifndef __CAMERA__H
#define __CAMERA__H

#include <Math.hpp>
#include <Entity.hpp>

class Camera : public Entity {
  public:
    float   moveVelocity;
    float   lookVelocity;

    Camera();
    virtual void move(float direction);
    void update();
};

#endif
