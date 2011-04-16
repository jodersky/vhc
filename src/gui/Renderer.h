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

	virtual void render(const T& item) const = 0;
};

}

#endif /* RENDERER_H_ */
