/*
 * Camera.h
 *
 *  Created on: Mar 31, 2011
 *      Author: jakob
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <cmath>
#include <QtOpenGL>
#include "Vector3D.h"
#include <GL/glu.h>

namespace vhc {

/** Represente une camera, un observateur 3D. */
class Camera {

private:

	/** Position de la camera. */
	Vector3D position; //from position

	/** Direction de vue. */
	Vector3D direction; //to position + direction

	/** Haut de l'ecran. */
	Vector3D up;

	/** Heading. (angle autour de la verticale de la camera) */
	double heading; //left/right

	/** Pitch. (angle autour d'horizontale de la camera) */
	double pitch; //up/down

public:

	Camera();
	virtual ~Camera();

	/** Applique les transformantions de cet camera au viewport OpenGl. */
	void setView();

	/** Ajoute l'angle donne (en radians) au heading. */
	void addHeading(double h);

	/** Ajoute l'angle donne (en radians) au pitch. */
	void addPitch(double h);

	/** Translate la camera selon le vecteur donne (en coordonnees locales de cette camera). */
	void move(const Vector3D& moveVector);

	/** Retourne la position en coordonnees absolues de cette camera. */
	Vector3D getPosition() const;

	/** Retourne le heading de cette camera.
	 *  @see heading */
	double getHeading() const;

	/** Retourne le pitch de cette camera.
	 *  @see pitch */
	double getPitch() const;

};

}
#endif /* CAMERA_H_ */
