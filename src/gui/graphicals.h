/*
 * graphicals.h
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#ifndef GRAPHICALS_H_
#define GRAPHICALS_H_
#include "Element.h"

namespace vhc {

class Renderable {

public:

	Renderable() {};

	virtual ~Renderable() {};

	virtual void render() const = 0;

};

template <class T>;
class Graphical: public Renderable {
private:
	T* element
};


}

#endif /* GRAPHICALS_H_ */
