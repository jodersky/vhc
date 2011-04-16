/*
 * ParticleRenderer.h
 *
 *  Created on: Apr 12, 2011
 *      Author: jakob
 */

#ifndef PARTICLERENDERER_H_
#define PARTICLERENDERER_H_

#include "Renderer.h"
#include "Particle.h"

namespace vhc {

class ParticleRenderer: public Renderer<Particle> {
public:
	ParticleRenderer();
	virtual ~ParticleRenderer();
	void render(const Particle& particle) const;
};

}

#endif /* PARTICLERENDERER_H_ */
