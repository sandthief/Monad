#include <Quaternion.hpp>

Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
void Quaternion::normalize() {
  float mag = sqrt ((x * x) + (y * y) + (z * z) + (w * w));

  if (mag > 0.0f) {

      float oneOverMag = 1.0f / mag;

      x *= oneOverMag;
      y *= oneOverMag;
      z *= oneOverMag;
      w *= oneOverMag;
    }
}

Quaternion Quaternion::operator * (Quaternion b) {
	Quaternion out;
 	out.w = (w * b.w) - (x * b.x) - (y * b.y) - (z * b.z);
  	out.x = (x * b.w) + (w * b.x) + (y * b.z) - (z * b.y);
  	out.y = (y * b.w) + (w * b.y) + (z * b.x) - (x * b.z);
  	out.z = (z * b.w) + (w * b.z) + (x * b.y) - (y * b.x);
	return out;
}

Quaternion Quaternion::operator * (Point3D b) {
	Quaternion out;
	out.w = - (x * b.x) - (y * b.y) - (z * b.z);
  	out.x =   (w * b.x) + (y * b.z) - (z * b.y);
  	out.y =   (w * b.y) + (z * b.x) - (x * b.z);
  	out.z =   (w * b.z) + (x * b.y) - (y * b.x);
	return out;
}

void Quaternion::computeW() {
	float t = 1.0f - (x * x) - (y * y) - (z * z);

  	if (t < 0.0f)
    		w = 0.0f;
  	else
    		w = -sqrt (t);
}

Point3D Quaternion::rotatePoint (Point3D point)
{
  Quaternion inverse;

  inverse.x = -x;
  inverse.y = -y;
  inverse.z = -z;
  inverse.w =  w;

  inverse.normalize();
  Quaternion temp = *this * point;
  Quaternion out  = temp * inverse;
  return Point3D(out.x,out.y,out.z);
}
