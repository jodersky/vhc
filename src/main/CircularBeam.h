/*
 * CircularBeam.h
 *
 *  Created on: May 17, 2011
 *      Author: jakob
 */

#ifndef CIRCULARBEAM_H_
#define CIRCULARBEAM_H_

#include "Beam.h"

namespace vhc {

class CircularBeam: public Beam {


public:
	CircularBeam(const Particle& referenceParticle, int quantity, int lambda);
	virtual ~CircularBeam();

	virtual void initializeParticles();

	virtual CircularBeam* clone() const;
};

}

#endif /* CIRCULARBEAM_H_ */
