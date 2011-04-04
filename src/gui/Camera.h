/*
 * Camera.h
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <math.h>
#include <QtOpenGL>
#include "exception.h"

class Camera {

private:

public:

	double r;
	double theta;
	double phi;

	Camera(double r, double theta, double phi): r(r), theta(theta), phi(phi) {};
	virtual ~Camera() {};


	void setView() {
		double eyeX, eyeY, eyeZ;
		toCarthesian(r, theta, phi, eyeX, eyeY, eyeZ);
		gluLookAt(eyeX,eyeY,eyeZ,
				0,0,0,
				0,1,0);
	}


	static double sign(double value) {return (value > 0) - (value < 0);}

	static void toSpherical(double x, double y, double z, double& r, double&theta, double& phi) {
		r = sqrt(x * x + y * y + z * z);
		if (r == 0) {
			theta = 0;
			phi = 0;
			return;
		}

		theta = acos(z / r);

		if (x > 0) phi = atan(y / x);
		else if (x == 0) phi = sign(y) * M_PI / 2;
		else if (x < 0 && y >= 0) phi = atan(y / x) + M_PI;
		else if (x < 0 && y < 0) phi = atan(y / x) - M_PI;
		else throw vhc::Exception("This should not happen!");

	}

	static void toCarthesian(double r, double theta, double phi, double& x, double& y, double& z) {
		x = r * sin(theta) * cos(phi);
		y = r * sin(theta) * sin(phi);
		z = r * cos(theta);
	}
};

#endif /* CAMERA_H_ */
