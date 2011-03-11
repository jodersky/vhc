/*
 * Particle.h
 *
 *  Created on: Mar 9, 2011
 *      Author: jakob
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector3D.h"

namespace vhc {

class Particle {

private:
	Vector3D position;

public:
/*
	Vector3D getPosition();

	Vector3D getVelocity();

	Vector3D getEnergy();

	Vector3D getGamma();

	Vector3D getMomentum();
*/
	Particle(): position(0, 0, 0) {};
	virtual ~Particle();
};

}

#endif /* PARTICLE_H_ */