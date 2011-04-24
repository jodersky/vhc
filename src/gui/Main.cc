/*
 * Main.cc
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <cmath>
#include "exceptions.h"
#include "Stage.h"
#include "Accelerator.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "Particle.h"
#include "FODO.h"
#include "Vector3D.h"
#include "constants.h"
#include <vector>

using namespace vhc;

std::vector< Particle > createParticles(const Vector3D& position, int n, double mass = constants::ELECTRON_MASS, double charge = constants::E, double energy = 0, Vector3D direction = Vector3D::i) {
	std::vector< Particle > v;

	double r = 0.1;

	for (int i = 0; i < n; ++i) {
		double x = (rand() % 1000) / 1000.0 * r;
		double y = (rand() % 1000) / 1000.0 * sqrt(r * r - x * x);
		double z = (rand() % 1000) / 1000.0 * sqrt(r * r - y * y - x * x);
		v.push_back(Particle(position + Vector3D(x, y, z), mass, charge, energy, direction));
	}

	return v;
}


Accelerator* standardAccelerator() {
	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.2, 1.0, 5.0);
	Dipole e2 = Dipole(e1.getExitPosition(), Vector3D(2, -3, 0), 0.2, 1);
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.2, 1, 5.0);
	Dipole e4 = Dipole(e3.getExitPosition(), Vector3D(-3, -2, 0), 0.2, 1);
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.2, 1.0, 5.0);
	Dipole e6 = Dipole(e5.getExitPosition(), Vector3D(-2, 3, 0), 0.2, 1);
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.2, 1.0, 5.0);
	Dipole e8 = Dipole(e7.getExitPosition(), e1.getEntryPosition(), 0.2, 1);
	Accelerator* acc = new Accelerator();
	acc->add(e1);
	acc->add(e2);
	acc->add(e3);
	acc->add(e4);
	acc->add(e5);
	acc->add(e6);
	acc->add(e7);
	acc->add(e8);

	std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 1000);

	for (int i = 0; i < ps.size(); ++i) {
		acc->add(ps[i]);
	}

	return acc;
}

Accelerator* linear() {
	FODO element = FODO(Vector3D(0, 0, 0), Vector3D(4, 0, 0), 0.2, 0.2, 120);
	Accelerator* acc = new Accelerator();
	Element* celement = acc->add(element);
	Particle e(Vector3D(0, 0.15, 0.01), constants::ELECTRON_MASS, constants::E, 14E9 * constants::E, Vector3D::i);
	Particle* ce = acc->add(e);
	ce->setElement(celement);

	return acc;
}

Accelerator* singleDipole() {
	Vector3D entry = Vector3D(0, 2, 0);
	Vector3D exit =  Vector3D(2, 0, 0);
	double sectionRadius = 0.2;
	double curvature = 0.5;
	Vector3D direction = entry.cross(Vector3D::k);

	double mass = constants::ELECTRON_MASS;
	double charge = constants::E;
	double energy = 1 * 1E9 * constants::E;


	Particle particle = Particle(entry, mass, charge, energy, direction);
	double Bz = particle.getGamma() * particle.getMass() * curvature * particle.getVelocity().norm() / particle.getCharge();
	std::cout << "|B:|" << Bz << std::endl;
	Dipole element = Dipole(entry, exit, sectionRadius, curvature, Vector3D::k * Bz);

	Accelerator* acc = new Accelerator();

	Element* celement = acc->add(element);

	std::vector< Particle > ps = createParticles(element.getEntryPosition(), 10, constants::ELECTRON_MASS, constants::E, energy, direction);

	for (int i = 0; i < ps.size(); ++i) {
		Particle* cparticle = acc->add(ps[i]);
		cparticle->setElement(celement);
	}

	Particle* cparticle = acc->add(particle);
	cparticle->setElement(celement);
	return acc;
}


int main(int argc, char *argv[])
{
	try {

    QApplication app(argc, argv);

    vhc::Stage window;
    Accelerator* acc = linear();
    window.accelerator = acc;
    //window.showFullScreen();

    window.resize(QSize(500, 500));
    window.setWindowTitle("Virtual Hadron Collider");
    window.show();

    return app.exec();

    delete acc; acc = NULL;

	} catch (Exception& ex){
    	std::cerr << ex.toString() << "\n";
    }
}
