/*
 * GElement.h
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#ifndef GELEMENT_H_
#define GELEMENT_H_
#include "Element.h"

namespace vhc {

class GElement {

	Element& element;

public:
	GElement(Element& element);


	virtual ~GElement();

};

}

#endif /* GELEMENT_H_ */
