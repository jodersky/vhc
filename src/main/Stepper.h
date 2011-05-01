/*
 * Stepper.h
 *
 *  Created on: Apr 24, 2011
 *      Author: jakob
 */

#ifndef STEPPER_H_
#define STEPPER_H_

#include <vector>
#include "Accelerator.h"

namespace vhc {

class Stepper {

public:
	Stepper();
	virtual ~Stepper();

	virtual void step(const std::vector< Element* > & elements, const std::vector< Particle* > & particles, double dt) = 0;
};

}

#endif /* STEPPER_H_ */
