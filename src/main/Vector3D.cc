/*
 * Vector3D.cc
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#include <iostream>
#include "Vector3D.h"

using namespace std;

namespace vhc {

//c.f. header
Vector3D const Vector3D::Null = Vector3D(0.0, 0.0, 0.0);

//c.f. header
Vector3D const Vector3D::i = Vector3D(1.0, 0.0, 0.0);

//c.f. header
Vector3D const Vector3D::j = Vector3D(0.0, 1.0, 0.0);

//c.f. header
Vector3D const Vector3D::k = Vector3D(0.0, 0.0, 1.0);

//c.f. header
Vector3D operator* (double n, const Vector3D& v) {
	return v * n;
}

}
