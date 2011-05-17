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

protected:

	virtual void init(const Particle& referenceParticle, int quantity, int lambda) = 0;

public:
	CircularBeam(const Particle& referenceParticle, int quantity, int lambda);
	virtual ~CircularBeam();

	virtual CircularBeam* clone() const;
};

}

#endif /* CIRCULARBEAM_H_ */
