/*
 * Camera.cc
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#include "Camera.h"

namespace vhc {

Camera::Camera(): position(1, 1, 1), direction(-1, 0, 0), up(0,0,1), heading(M_PI_4), pitch(-M_PI_4) {};

Camera::~Camera() {};

void Camera::setView() {
	Vector3D td = direction.rotate(Vector3D::j, pitch).rotate(Vector3D::k, heading);; //tranformed direction
	Vector3D at = position + td;

	gluLookAt(position.getX(), position.getY(), position.getZ(),
			at.getX(), at.getY(), at.getZ(),
			up.getX(), up.getY(), up.getZ());
}

void Camera::addHeading(double h) {
	heading += h;
}

void Camera::addPitch(double h) {
	pitch += h;
	if (pitch <= -M_PI_2) pitch = -M_PI_2 + 0.001;
	if (pitch >= M_PI_2) pitch = M_PI_2 - 0.001;
}


void Camera::move(const Vector3D& moveVector) {
	Vector3D mv = moveVector.rotate(Vector3D::j, pitch).rotate(Vector3D::k, heading);
	position = position + mv;
}

Vector3D Camera::getPosition() const {return position;}
double Camera::getHeading() const {return heading;}
double Camera::getPitch() const {return pitch;}


} //vhc
