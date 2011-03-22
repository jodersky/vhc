/*
 * Courbe.h
 *
 *  Created on: 21 mars 2011
 *      Author: christian
 */

#ifndef COURBE_H_
#define COURBE_H_

#include<Element.h>

namespace vhc {

class Courbe : public Element {
protected:
	/** Postion de centre de courbure
	 * (rayon de courbure implicite). */
	Vector3D courbureCenter;

public:
	Courbe();
	virtual ~Courbe();
};

}

#endif /* COURBE_H_ */
