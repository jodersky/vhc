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

Vector3D const Vector3D::Null = Vector3D(0.0, 0.0, 0.0);
Vector3D const Vector3D::i = Vector3D(1.0, 0.0, 0.0);
Vector3D const Vector3D::j = Vector3D(0.0, 1.0, 0.0);
Vector3D const Vector3D::k = Vector3D(0.0, 0.0, 1.0);

double Vector3D::tripleproduct(const Vector3D& v, const Vector3D& w) const {
	return this->dot(v.cross(w));
	};

Vector3D operator* (double n, const Vector3D& v) {
	return v * n;
}

}
