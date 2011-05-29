/*
 * BeamRenderer.h
 *
 *  Created on: May 27, 2011
 *      Author: jakob
 */

#ifndef BEAMRENDERER_H_
#define BEAMRENDERER_H_

#include "Renderer.h"
#include "Beam.h"

namespace vhc {

/** Dessinateur standard de faisceaux. */
class BeamRenderer: public Renderer<Beam> {
private:
	bool _spheres;

public:
	BeamRenderer();
	virtual ~BeamRenderer();

	/** Dessine un faisceau. */
	virtual void render(const Beam& beam) const;

	/** Change le mode de dessin des particules en spheres ou points. */
	void setSpheresEnabled(bool value);

	/** Retourne vrai si on dessine des spheres. */
	bool getSpheresEnabled() const;
};

}

#endif /* BEAMRENDERER_H_ */
