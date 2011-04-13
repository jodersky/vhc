/*
 * ParticleRenderer.h
 *
 *  Created on: Apr 12, 2011
 *      Author: jakob
 */

#ifndef PARTICLERENDERER_H_
#define PARTICLERENDERER_H_

#include "Particle.h"

namespace vhc {

class ParticleRenderer {
public:
	ParticleRenderer();
	virtual ~ParticleRenderer();
	void render(const Particle& particle) const;
};

}

#endif /* PARTICLERENDERER_H_ */
