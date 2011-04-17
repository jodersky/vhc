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

	Camera();
	virtual ~Camera() {};

	void setView();

	void addHeading(double h);

	void addPitch(double h);


	void move(const Vector3D& moveVector);

	Vector3D getPosition() const;
	double getHeading() const;
	double getPitch() const;

};

}
#endif /* CAMERA_H_ */
