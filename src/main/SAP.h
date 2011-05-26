/*
 * SAP.h
 *
 *  Created on: May 24, 2011
 *      Author: jakob
 */

#ifndef SAP_H_
#define SAP_H_

#include <vector>
#include "InteractionDetector.h"
#include "Particle.h"
#include "Element.h"

namespace vhc {

class SAP {

private:
	vector<Particle*> particles;
	element->localpos
	particle->localpos

public:

	//static const double THRESHOLD_RADIUS;

	SAP();
	virtual ~SAP();

	virtual void applyInteractions();
	virtual void acceleratorClosed();

	virtual void react(const ParticleAddedEvent& event) = 0;
	virtual void react(const ParticleRemovedEvent& event) = 0;
};

}

#endif /* SAP_H_ */
