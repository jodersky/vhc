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

/** Un vecteur de dimension trois. Les instances de cette classes sont completement
 *  invariables, c'est-a-dire un vecteur une fois initialise, ses composantes ne
 *  peuvent plus etres modifies.
 *  Le fait qu'un vecteur ne possede pas d'etat, facilite le raisonement et parait
 *  surtout naturelle.
 *  Ainsi, chaque operation sur un vecteur retourne une nouvelle instance. La
 *  performance perdue ainsi est minimale pour une classe ne contenant que trois
 *  champs.
 */
class Vector3D {
	friend std::ostream& operator<< (std::ostream& output, const Vector3D& v);

private:
	/** Composante x. */
	double x;

	/** Composante y. */
	double y;

	/** Composante z. */
	double z;

public:

	/** Cree une nouvelle instance de <code>Vector3D</code>.
	 *  @param x 1e composante
	 *  @param y 2e composante
	 *  @param z 3e composante
	 */
	Vector3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

	/** Retourne la composante x de ce vecteur. */
	double getX() const {return x;};

	/** Retourne la composante y de ce vecteur. */
	double getY() const {return y;};

	/** Retourne la composante z de ce vecteur. */
	double getZ() const {return z;};

	/** Verifie si ce vecteur et le vecteur <code>v</code> sont eqaux, i.e. qu'ils ont les memes composantes. */
	bool operator== (const Vector3D& v) const {return x == v.x && y == v.y && z == v.z;};

	/** Verifie si ce vecteur et le vecteur <code>v</code> sont differents, i.e. qu'ils ont des composantes differentes. */
	bool operator!= (const Vector3D& v) const {return !((*this) == (v));};

	/** Addition de vecteurs. Retourne un nouveau vecteur resultant de l'addition de ce vecteur avec <code>v</code>. */
	Vector3D operator+ (const Vector3D& v) const {return Vector3D(x + v.x, y + v.y, z + v.z);};

	/** Multiplication scalaire. Retourne un nouveau vecteur resultant de la multiplication de ce vecteur par <code>n</code>. */
	Vector3D operator* (double n) const {return Vector3D(x * n, y * n, z * n);};

	/** Retourne l'oppose de ce vecteur. */
	Vector3D operator-() const {return (*this) * (-1.0);};

	/** Soustraction de vecteurs. Retourne un nouveau vecteur resultant de la soustraction de ce vecteur avec <code>v</code>. */
	Vector3D operator- (const Vector3D& v) const {return (*this) + -v;};

	/** Division scalaire. Retourne un nouveau vecteur resultant de la division de ce vecteur par <code>n</code>. */
	Vector3D operator/ (double n) const {return (*this) * (1.0 / n) ;};

	/** Produit scalaire. Retourne le produit scalaire de ce vecteur avec le vecteur <code>v</code>. */
	double dot(const Vector3D& v) const {return x * v.x + y * v.y + z * v.z;};

	/** Produit vectoriel. Retourne le produit vectoriel directe (main droite) de ce vecteur avec le vecteur <code>v</code>.
	 *  Nous avons decide de ne pas utiliser l'operateur `^' pour representer le produit vectoriel car sa precedence est plus
	 *  basse que toutes autres operations binaires sur les vecteurs.
	 */
	Vector3D cross(const Vector3D& v) const {return Vector3D(y * v.z - v.y * z, v.x * z - x * v.z, x * v.y - v.x * y);};

	/** Vecteur unitaire de ce vecteur. */
	Vector3D operator~() const {
		if (getLength() != 0.0) return (*this) / getLength();
		else throw std::domain_error("Unit vector.");
	};

	/** Retourne la norme du vecteur. */
	double getNorm() const {return sqrt(dot(*this));};

	/** Retourne une representation en chaine de ce vecteur. */
	std::string toString() const {
		std::stringstream s;
		s << "Vector3D(" << x << ", " << y << ", " << z << ")";
		return s.str();
	};

	/** Vecteur nulle. (0,0,0) */
	static const Vector3D Null;

	/** Vecteur unitaire, d'axe x. (1, 0, 0) */
	static const Vector3D i;

	/** Vecteur unitaire, d'axe y. (0, 1, 0) */
	static const Vector3D j;

	/** Vecteur unitaire, d'axe z. (0, 0, 1) */
	static const Vector3D k;

};

} // namespace

#endif /* VECTOR3D_H_ */
