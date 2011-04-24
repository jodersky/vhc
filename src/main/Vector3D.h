/*
 * Vector3D.h
 *
 *  Created on: Mar 1, 2011
 *      Author: Jakob Odersky
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <limits>
#include "Printable.h"

namespace vhc {

/** Un vecteur de dimension trois. Les instances de cette classes sont complètement
 *  invariables, c'est-à-dire qu'un vecteur une fois initialisé, ses composantes ne
 *  peuvent plus êtres modifiées.
 *  Le fait qu'un vecteur ne possède pas d'état, facilite le raisonnement et paraît
 *  surtout naturel.
 *  Ainsi, chaque opération sur un vecteur retourne une nouvelle instance. La
 *  performance ainsi perdue est minimale pour une classe ne contenant que trois
 *  champs.
 *  Les méthodes d'un vecteur sont toutes très simples et implémentées dans le header,
 *  afin d'être développées 'inline' durant la compilation, ce qui est plus rapide.
 */
class Vector3D: public Printable {

private:
	/** Composante x. */
	double x;

	/** Composante y. */
	double y;

	/** Composante z. */
	double z;

	/** Cache de norme. (-1 si pas encore calcule) */
	mutable double normCache;

public:

	/** Crée une nouvelle instance de <code>Vector3D</code>.
	 *  @param _x 1e composante
	 *  @param _y 2e composante
	 *  @param _z 3e composante
	 */
	Vector3D(double _x, double _y, double _z);

	/** Retourne la composante x de ce vecteur. */
	double getX() const;

	/** Retourne la composante y de ce vecteur. */
	double getY() const;

	/** Retourne la composante z de ce vecteur. */
	double getZ() const;

	/** Vérifie si ce vecteur et le vecteur <code>v</code> sont égaux, i.e. qu'ils ont les mêmes composantes. */
	bool operator== (const Vector3D& v) const;

	/** Vérifie si ce vecteur et le vecteur <code>v</code> sont différents, i.e. qu'ils ont des composantes différentes. */
	bool operator!= (const Vector3D& v) const;

	/** Addition de vecteurs. Retourne un nouveau vecteur résultant de l'addition de ce vecteur avec <code>v</code>. */
	Vector3D operator+ (const Vector3D& v) const;

	/** Multiplication scalaire. Retourne un nouveau vecteur résultant de la multiplication de ce vecteur par <code>n</code>. */
	Vector3D operator* (double n) const;

	/** Retourne l'opposé de ce vecteur. */
	Vector3D operator-() const;

	/** Soustraction de vecteurs. Retourne un nouveau vecteur résultant de la soustraction de ce vecteur avec <code>v</code>. */
	Vector3D operator- (const Vector3D& v) const;

	/** Division scalaire. Retourne un nouveau vecteur résultant de la division de ce vecteur par <code>n</code>. */
	Vector3D operator/ (double n) const;

	/** Produit scalaire. Retourne le produit scalaire de ce vecteur avec le vecteur <code>v</code>. */
	double dot(const Vector3D& v) const;

	/** Produit vectoriel. Retourne le produit vectoriel direct (main droite) de ce vecteur avec le vecteur <code>v</code>.
	 *  Nous avons decidé de ne pas utiliser l'operateur `^' pour représenter le produit vectoriel car sa précédence est plus
	 *  basse que toutes autres opérations binaires sur les vecteurs.
	 */
	Vector3D cross(const Vector3D& v) const;

	/** Vecteur unitaire de ce vecteur. */
	Vector3D operator~() const;

	/** Retourne le vecteur unitaire */
	Vector3D unit() const;

	/** Retourne la norme euclidienne du vecteur. */
	double norm() const;

	/** Retourne la norme de ce vecteur correspondant au minimum des composantes. */
	double minNorm() const;

	/** Retourne la norme du vecteur au carre. */
	double normSquare() const;

	/** Retourne une représentation en chaîne de caractères de ce vecteur. */
	virtual std::string toString() const;

	double angle(const Vector3D& v) const;

	/** Produit mixte de 3 vecteurs. Retourne le produit scalaire de ce vecteur
	 * 	avec le produit vectoriel de deux vecteurs <code>v</code> et <code>w</code>). */
	double tripleProduct(const Vector3D& v, const Vector3D& w) const;

	/** Rotation vectorielle. Retourne le vecteur courant, évalué dans la formule en <code>a</code>,
	 * le vecteur de l'axe, et en <code>t</code>, l'angle de rotation. */
	Vector3D rotate(const Vector3D& axis, double t) const;

	/** Verifie si les vecteurs <code>u</code> et <code>v</code> sont approximativement égaux, i.e. que la norme de leur difference est plus petit qu'un epsilon. */
	static bool ae(const Vector3D& u, const Vector3D& v, double epsilon = std::numeric_limits<double>::epsilon());

	/** Vecteur nul. (0,0,0) */
	static const Vector3D Null;

	/** Vecteur unitaire, d'axe x. (1, 0, 0) */
	static const Vector3D i;

	/** Vecteur unitaire, d'axe y. (0, 1, 0) */
	static const Vector3D j;

	/** Vecteur unitaire, d'axe z. (0, 0, 1) */
	static const Vector3D k;

};

/** Surcharge externe de la mutliplication scalaire. */
Vector3D operator* (double n, const Vector3D& v);

} // namespace

#endif /* VECTOR3D_H_ */
