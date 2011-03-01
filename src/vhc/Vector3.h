/*
 * Vector3.h
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <iostream>
#include <sstream>
#include <math.h>

namespace vhc {

/** A three-dimensional vector. Instances of this class are completely immutable, i.e. the
 *  values (x, y, z), once initialised, cannot be changed anymore.
 *  This highly facilitates reasoning about code using vectors.
 */
class Vector3 {
	friend std::ostream& operator<< (std::ostream& output, const Vector3& v);

private:
	double x;
	double y;
	double z;

public:

	/** Creates a new instance of <code>Vector3</code>.
	 *  @param x x value of this vector
	 *  @param y y value of this vector
	 *  @param z z value of this vector
	 */
	Vector3(double x, double y, double z) {this->x = x; this->y = y; this->z = z;};

	/** Returns the x value of this vector. */
	double getX() const {return x;};

	/** Returns the y value of this vector. */
	double getY() const {return y;};

	/** Returns the z value of this vector. */
	double getZ() const {return z;};

	/** Tests if this vector and vector <code>v</code> are equal, i.e. have the same coordinates. */
	bool operator== (const Vector3& v) const {return x == v.x && y == v.y && z == v.z;};

	/** Tests if this vector and vector <code>v</code> are different, i.e. have different coordinates. */
	bool operator!= (const Vector3& v) const {return !((*this) == (v));};

	/** Vector addition. Returns a new vector resulting of adding this vector to vector <code>v</code>. */
	Vector3 operator+ (const Vector3& v) const {return Vector3(x + v.x, y + v.y, z + v.z);};

	/** Scalar multipication. Returns a new vector resulting of multiplying this vector by <code>n</code>. */
	Vector3 operator* (double n) const {return Vector3(x * n, y * n, z * n);};

	/** Returns the opposite of this vector. */
	Vector3 operator-() const {return (*this) * (-1.0);};

	/** Vector subtraction. Returns a new vector resulting of adding this vector to the opposite of vector <code>v</code>. */
	Vector3 operator- (const Vector3& v) const {return (*this) + -v;};

	/** Scalar division. Returns a new vector resulting of multiplying this vector by the inverse of <code>n</code>. */
	Vector3 operator/ (double n) const {return (*this) * (1.0 / n) ;};

	/** Dot product. Returns the dot product of this vector and vector <code>v</code>. */
	double dot(const Vector3& v) const {return x * v.x + y * v.y + z * v.z;};

	/** Cross product. Returns the right-handed cross product of this vector and vector <code>v</code>. */
	Vector3 cross(const Vector3& v) const {return Vector3(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);};

	/** Length of this vector. */
	double getLength() const {return sqrt(dot(*this));};

	/** Unit vector parallel to this vector. */
	Vector3 getUnit() const {return (*this) / getLength();};

	/** Returns a string representation of this vector. */
	std::string toString() const {
		std::stringstream s;
		s << "Vector3(" << x << ", " << y << ", " << z << ")";
		return s.str();
	};

	/** Null vector. (0,0,0) */
	static Vector3 Null;

	/** X-axis unit vector. (1, 0, 0) */
	static Vector3 i;

	/** Y-axis unit vector. (0, 1, 0) */
	static Vector3 j;

	/** Z-axis unit vector. (0, 0, 1) */
	static Vector3 k;

};

} // namespace

#endif /* VECTOR3_H_ */
