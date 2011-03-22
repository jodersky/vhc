/*
 * BasicTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#include "Element.h"
#include "Curved.h"
#include "Straight.h"
#include "Vector3D.h"

using namespace vhc;

int main() {

	Straight(Vector3D(0,0,0), Vector3D(1,2,0), 0.2);

	return 0;
}

