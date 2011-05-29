/*
 * EnergyBeamRenderer.h
 *
 *  Created on: May 29, 2011
 *      Author: jakob
 */

#ifndef ENERGYBEAMRENDERER_H_
#define ENERGYBEAMRENDERER_H_

#include "BeamRenderer.h"

namespace vhc {

class EnergyBeamRenderer: BeamRenderer {
public:
	EnergyBeamRenderer();
	virtual ~EnergyBeamRenderer();

	virtual void render(const Beam& beam) const;
};

}

#endif /* ENERGYBEAMRENDERER_H_ */
