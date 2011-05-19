/*
 * SingleBeam.h
 *
 *  Created on: May 18, 2011
 *      Author: jakob
 */

#ifndef SINGLEBEAM_H_
#define SINGLEBEAM_H_

#include "Beam.h"
#include "Particle.h"

namespace vhc {

class SingleBeam: public vhc::Beam {
public:
	SingleBeam(const Particle& particle);
	virtual ~SingleBeam();

	virtual void initializeParticles();

	virtual SingleBeam* clone() const;
};

}

#endif /* SINGLEBEAM_H_ */
