/*
 * Vector3D.h
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <iostream>
#include <sstream>
#include <math.h>
#include <stdexcept>

namespace vhc {

/** A three-dimensional vector. Instances of this class are completely immutable, i.e. the
 *  values (x, y, z), once initialised, cannot be changed anymore.
 *  This highly facilitates reasoning about code using vectors.
 */
class Vector3D {
	friend std::ostream& operator<< (std::ostream& output, const Vector3D& v);

private:
	double x;
	double y;
	double z;

public:

	/** Creates a new instance of <code>Vector3D</code>.
	 *  @param x x value of this vector
	 *  @param y y value of this vector
	 *  @param z z value of this vector
	 */
	Vector3D(double x, double y, double z) {this->x = x; this->y = y; this->z = z;};

	/** Returns the x value of this vector. */
	double getX() const {return x;};

	/** Returns the y value of this vector. */
	double getY() const {return y;};

	/** Returns the z value of this vector. */
	double getZ() const {return z;};

	/** Tests if this vector and vector <code>v</code> are equal, i.e. have the same coordinates. */
	bool operator== (const Vector3D& v) const {return x == v.x && y == v.y && z == v.z;};

	/** Tests if this vector and vector <code>v</code> are different, i.e. have different coordinates. */
	bool operator!= (const Vector3D& v) const {return !((*this) == (v));};

	/** Vector addition. Returns a new vector resulting of adding this vector to vector <code>v</code>. */
	Vector3D operator+ (const Vector3D& v) const {return Vector3D(x + v.x, y + v.y, z + v.z);};

	/** Scalar multipication. Returns a new vector resulting of multiplying this vector by <code>n</code>. */
	Vector3D operator* (double n) const {return Vector3D(x * n, y * n, z * n);};

	/** Returns the opposite of this vector. */
	Vector3D operator-() const {return (*this) * (-1.0);};

	/** Vector subtraction. Returns a new vector resulting of adding this vector to the opposite of vector <code>v</code>. */
	Vector3D operator- (const Vector3D& v) const {return (*this) + -v;};

	/** Scalar division. Returns a new vector resulting of multiplying this vector by the inverse of <code>n</code>. */
	Vector3D operator/ (double n) const {return (*this) * (1.0 / n) ;};

	/** Dot product. Returns the dot product of this vector and vector <code>v</code>. */
	double dot(const Vector3D& v) const {return x * v.x + y * v.y + z * v.z;};

	/** Cross product. Returns the right-handed cross product of this vector and vector <code>v</code>. */
	Vector3D cross(const Vector3D& v) const {return Vector3D(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);};

	/** Length of this vector. */
	double getLength() const {return sqrt(dot(*this));};

	/** Unit vector parallel to this vector. */
	Vector3D getUnit() const {
		if (getLength() != 0.0) return (*this) / getLength();
		else throw std::domain_error("Unit vector.");
	};

	/** Returns a string representation of this vector. */
	std::string toString() const {
		std::stringstream s;
		s << "Vector3D(" << x << ", " << y << ", " << z << ")";
		return s.str();
	};

	/** Null vector. (0,0,0) */
	static const Vector3D Null;

	/** X-axis unit vector. (1, 0, 0) */
	static const Vector3D i;

	/** Y-axis unit vector. (0, 1, 0) */
	static const Vector3D j;

	/** Z-axis unit vector. (0, 0, 1) */
	static const Vector3D k;

};

} // namespace

#endif /* VECTOR3D_H_ */
