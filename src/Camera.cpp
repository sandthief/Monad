#include <Camera.hpp>

using namespace std;

Camera::Camera() {
  moveVelocity  = 100.0f;
  lookVelocity  = 1;
  yaw           = 0.0f;
  pitch         = 0.0f;
}

void Camera::move(float direction) {
  boundingShape.center   = projectPoint(boundingShape.center, direction + yaw,pitch,moveVelocity);
}
void Camera::update(){
  if(pitch>90)
        pitch=90;
    if(pitch<-90)
        pitch=-90;
    if(yaw<0.0)
        yaw+=360.0;
    if(yaw>360.0)
        yaw-=360;

  glRotatef(-pitch,1,0,0);
  glRotatef(-yaw,0,1,0);
  glTranslatef(-boundingShape.center.x,-(boundingShape.center.y + boundingShape.height/2),-boundingShape.center.z);
}
