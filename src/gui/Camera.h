/*
 * Camera.h
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <math.h>
#include "exception.h"

class Camera {

private:
	double _x;
	double _y;
	double _z;


public:
	Camera(double x, double y, double z): _x(x), _y(y), _z(z) {};
	virtual ~Camera();



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
