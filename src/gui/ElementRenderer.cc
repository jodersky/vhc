/*
 * ElementRenderer.cc
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#include <QtOpenGL>
#include <math.h>
#include "ElementRenderer.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "util.h"
#include "Vector3D.h"

//using namespace vhc::util;

namespace vhc {

ElementRenderer::ElementRenderer() {
}

ElementRenderer::~ElementRenderer() {

}

void ElementRenderer::render(const Element& element) const {
	element.accept(*this);
}

void ElementRenderer::drawStraight(const StraightElement* straight) const {
	glPushMatrix();
	glTranslated(straight->getEntryPosition().getX(), straight->getEntryPosition().getY(), straight->getEntryPosition().getZ());
	Vector3D axis = Vector3D::k.cross(straight->getDiagonal());
	double angle = asin(axis.norm() / straight->getDiagonal().norm());
	glRotated(angle * 180 / M_PI, axis.getX(), axis.getY(), axis.getZ());

	util::cylinder(straight->getSectionRadius(),
				   straight->getSectionRadius(),
				   straight->getDiagonal().norm(),
				   SLICES, STACKS_PER_LENGTH * straight->getDiagonal().norm());

	glPopMatrix();
}


void ElementRenderer::visit(const StraightElement* straight) const {
	glColor4d(0.4, 0.4, 0.4, 0.9);
	drawStraight(straight);
}

void ElementRenderer::visit(const Quadrupole* quadrupole) const {
	if (quadrupole->getFocalizingCoefficient() > 0)
		glColor4d(0.4, 0, 0, 0.9);
	else
		glColor4d(0.4, 0.2, 0.2, 0.9);
	drawStraight(quadrupole);
}


void ElementRenderer::visit(const Dipole* dipole) const {
	glColor4d(0.2, 0, 0.4, 0.9);
	glPushMatrix();
	glTranslated(dipole->getCurvatureCenter().getX(), dipole->getCurvatureCenter().getY(), dipole->getCurvatureCenter().getZ());
	Vector3D d = dipole->getExitPosition() - dipole->getCurvatureCenter();
	Vector3D axis = Vector3D::i.cross(d);
	double angle = asin(axis.norm() / d.norm());

	if (d != -Vector3D::i)
		glRotated(angle * 180 / M_PI, axis.getX(), axis.getY(), axis.getZ());
	else
		glRotated(180, 0, 0, 1); //handle degenerate case

	//double fraction
	util::torus(d.norm(),
			dipole->getSectionRadius(),
			dipole->getAngle() / (2 * M_PI), SLICES, 200); // * dipole->getAngle() * d.norm());

	glPopMatrix();
}

}
