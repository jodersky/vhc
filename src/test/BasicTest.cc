/*
 * BasicTest.cc
 *
 *  Created on: Mar 17, 2011
 *      Author: jakob
 */

#include "Element.h"
#include "CurvedElement.h"
#include "StraightElement.h"
#include "Vector3D.h"

using namespace vhc;

int main() {

	//StraightElement(Vector3D(0,0,0), Vector3D(1,2,0), 0.2);

	CurvedElement(Vector3D(0,0,0), Vector3D(1,2,0), 2, 0.2);

	return 0;
}

