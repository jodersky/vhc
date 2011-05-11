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
class Renderer {
public:
	Renderer() {};
	virtual ~Renderer() {};

	/** Methode qui doit etre appelee avant de dessiner une collection d'objets par <code>render</code>.
	 *  Cette methode gere des <code>glBegin()</code> en arriere-plan. */
	//virtual void begin() = 0;

	/** Dessine un objet. */
	virtual void render(const T& item) const = 0;

	//template <typename Container>
	//virtual void render(std::forward_iterator) const;

	/** Methode qui doit etre appelee avant de dessiner une collection d'objets par <code>render</code>.
	*  Cette methode gere des <code>glBegin()</code> en arriere-plan. */
	//virtual void end() = 0;
};

}

#endif /* RENDERER_H_ */
