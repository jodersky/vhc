/*
 * Renderer.h
 *
 *  Created on: Apr 16, 2011
 *      Author: jakob
 */

#ifndef RENDERER_H_
#define RENDERER_H_

namespace vhc {

template <typename T>
/** Classe de base pour tout dessinateur. Un dessinateur peut dessiner un objet de son type. */
class Renderer {
public:

	Renderer() {};
	virtual ~Renderer() {};

	/** Dessine un objet. */
	virtual void render(const T& item) const = 0;

};

}

#endif /* RENDERER_H_ */
