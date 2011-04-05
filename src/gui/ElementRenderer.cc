/*
 * ElementRenderer.cc
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */

#include <QtOpenGL>
#include <math.h>
#include "ElementRenderer.h"
#include "CurvedElement.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "util.h"
#include "Vector3D.h"

//using namespace vhc::util;

namespace vhc {

ElementRenderer::ElementRenderer() {
	// TODO Auto-generated constructor stub

}

ElementRenderer::~ElementRenderer() {
	// TODO Auto-generated destructor stub
}


void ElementRenderer::visit(StraightElement* straight) {
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

void ElementRenderer::visit(Quadrupole* quadrupole) {

}


void ElementRenderer::visit(Dipole* dipole) {
	glPushMatrix();
	glTranslated(dipole->getCurvatureCenter().getX(), dipole->getCurvatureCenter().getY(), dipole->getCurvatureCenter().getZ());
	Vector3D d = dipole->getExitPosition() - dipole->getCurvatureCenter();
	Vector3D axis = Vector3D::i.cross(d);
	double angle = asin(axis.norm() / d.norm());
	glRotated(angle * 180 / M_PI, axis.getX(), axis.getY(), axis.getZ());

	//double fraction
	util::torus(d.norm(),
			dipole->getSectionRadius(),
			dipole->getAngle() / (2 * M_PI), SLICES, 200);// * dipole->getAngle() * d.norm());

	glPopMatrix();
}

}
