/*
 * Camera.h
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <cmath>
#include <QtOpenGL>
#include "exception.h"
#include "Vector3D.h"

namespace vhc {

class Camera {

private:
	Vector3D position; //from position
	Vector3D direction; //to position + direction
	Vector3D up;

	double heading; //left/right
	double pitch; //up/down


public:

	Camera(): position(1, 1, 1), direction(1, 0, 0), up(0,0,1), heading(M_PI_4), pitch(-M_PI_4) {};
	virtual ~Camera() {};

	void setView() {
		Vector3D td = direction.rotate(Vector3D::j, pitch).rotate(Vector3D::k, heading);; //tranformed direction
		Vector3D at = position + td;

		gluLookAt(position.getX(), position.getY(), position.getZ(),
				  at.getX(), at.getY(), at.getZ(),
				  up.getX(), up.getY(), up.getZ());
	}

	void addHeading(double h) {
		heading += h;
	}

	void addPitch(double h) {
		pitch += h;
	}


	void move(const Vector3D& moveVector) {
		Vector3D mv = moveVector.rotate(Vector3D::j, pitch).rotate(Vector3D::k, heading);
		position = position + mv;
	}

};

}
#endif /* CAMERA_H_ */
