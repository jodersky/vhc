/*
 * Dipole.h
 *
 *  Created on: Mar 28, 2011
 *      Author: jakob
 */

#ifndef DIPOLE_H_
#define DIPOLE_H_

#include <string>
#include <sstream>
#include "CurvedElement.h"
#include "Vector3D.h"
#include "ElementVisitor.h"


namespace vhc {

/** Represente un dipole avec un champ magnetique constant. */
class Dipole: public CurvedElement {

private:

	/** Champ magnetique du dipole. */
	Vector3D _magneticField;

public:

	/** Cree un nouveau dipole.
	 *  @param entry position d'entree
	 *  @param exit position de sortie
	 *  @param sectionRadius rayon de la chambre a vide
	 *  @param curvature courbure (inverse du rayon de courbure)
	 *  @param magneticField champ magnetique du dipole
	 *  @param next pointeur sur l'element prochain
	 *  @see vhc::Element*/
	Dipole(const Vector3D& entry, const Vector3D& exit, double sectionRadius, double curvature, const Vector3D& magneticField = Vector3D::Null, Element* next = NULL):
		CurvedElement(entry, exit, sectionRadius, curvature, next),
		_magneticField(magneticField) {};

	virtual ~Dipole() {};

	/** Retourne le champ magnetique a l'interieur de ce dipole. */
	Vector3D getMagneticField() const {
		return _magneticField;
	}

	/** Modifie le champ magnetique de ce dipole.
	 *  Ceci correspondrait en realite a une correction du champ a l'aide d'electroaimants. */
	void setMagneticField(const Vector3D& field) {
		_magneticField = field;
	}

	virtual Vector3D magneticFieldAt(const Vector3D& position) const {
		return _magneticField;
	}

	virtual std::string getType() const {return "Dipole";}
	virtual std::string toString() const {
		std::stringstream s;
		s << CurvedElement::toString() << "\n";
		s << "\tB: " << getMagneticField();
		s << "\t|B|: " << getMagneticField().norm();
		return s.str();
	}

	virtual void accept(ElementVisitor& v) {v.visit(this);}


};

}

#endif /* DIPOLE_H_ */
