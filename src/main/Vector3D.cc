/*
 * Vector3D.cc
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#include <sstream>
#include "Vector3D.h"
#include "exceptions.h"

using namespace std;

namespace vhc {

Vector3D::Vector3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z), normCache(-1) {};

double Vector3D::getX() const {return x;};

double Vector3D::getY() const {return y;};

double Vector3D::getZ() const {return z;};

bool Vector3D::operator== (const Vector3D& v) const {return x == v.x && y == v.y && z == v.z;};

bool Vector3D::operator!= (const Vector3D& v) const {return !((*this) == (v));};

Vector3D Vector3D::operator+ (const Vector3D& v) const {return Vector3D(x + v.x, y + v.y, z + v.z);};

Vector3D Vector3D::operator* (double n) const {return Vector3D(x * n, y * n, z * n);};

Vector3D Vector3D::operator- () const {return (*this) * (-1.0);};

Vector3D Vector3D::operator- (const Vector3D& v) const {return (*this) + -v;};

Vector3D Vector3D::operator/ (double n) const {return (*this) * (1.0 / n) ;};

double Vector3D::dot(const Vector3D& v) const {return x * v.x + y * v.y + z * v.z;};

Vector3D Vector3D::cross(const Vector3D& v) const {return Vector3D(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);};

Vector3D Vector3D::operator~ () const {
	if (norm() != 0.0) return (*this) / norm();
	else throw UnsupportedOperationException("Zero vector does not have a unit vector.");
};

Vector3D Vector3D::unit() const {return ~(*this);}

double Vector3D::norm() const {
	if (normCache == -1) normCache = sqrt(dot(*this));
	return normCache;
}

double Vector3D::normSquare() const {return dot(*this);}

std::string Vector3D::toString() const {
	std::stringstream s;
	s << "(" << x << ", " << y << ", " << z << ")";
	return s.str();
};

double Vector3D::angle(const Vector3D& v) const {return acos(dot(v) / norm() / v.norm());}

double Vector3D::tripleProduct(const Vector3D& v, const Vector3D& w) const { return dot(v.cross(w)); }

Vector3D Vector3D::rotate(const Vector3D& axis, double t) const {
	const Vector3D& x = *this;
	const Vector3D& a = ~axis;
	return x * cos(t) + a * x.dot(a) * (1-cos(t)) +  a.cross(x) * sin(t);
}

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
