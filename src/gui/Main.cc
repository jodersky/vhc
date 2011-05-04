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

using namespace std;
using namespace vhc;

std::vector< Particle > createParticles(const Vector3D& position, int n, double mass = constants::PROTON_MASS, double charge = constants::E, double energy = 2E9 * constants::E, Vector3D direction = -Vector3D::j) {
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


Accelerator* standard() {
/*
 * L'accélérateur est constitué des 20 éléments suivants :
Quadrupole     :  in  = (3, 2, 0) ; out = (3, 1, 0) ; Re = 0.1 ; b = 1.2
Section droite :  in  = (3, 1, 0) ; out = (3, 0, 0) ; Re = 0.1
Quadrupole     :  in  = (3, 0, 0) ; out = (3, -1, 0) ; Re = 0.1 ; b = -1.2
Section droite :  in  = (3, -1, 0) ; out = (3, -2, 0) ; Re = 0.1
Dipole         :  in  = (3, -2, 0) ; out = (2, -3, 0) ; Re = 0.1 ; Rc = 1 ; Cc = (2, -2, 0) ; B=(0, 0, 5.89158)
Quadrupole     :  in  = (2, -3, 0) ; out = (1, -3, 0) ; Re = 0.1 ; b = 1.2
Section droite :  in  = (1, -3, 0) ; out = (0, -3, 0) ; Re = 0.1
Quadrupole     :  in  = (0, -3, 0) ; out = (-1, -3, 0) ; Re = 0.1 ; b = -1.2
Section droite :  in  = (-1, -3, 0) ; out = (-2, -3, 0) ; Re = 0.1
Dipole         :  in  = (-2, -3, 0) ; out = (-3, -2, 0) ; Re = 0.1 ; Rc = 1 ; Cc = (-2, -2, 0) ; B=(0, 0, 5.89158)
Quadrupole     :  in  = (-3, -2, 0) ; out = (-3, -1, 0) ; Re = 0.1 ; b = 1.2
Section droite :  in  = (-3, -1, 0) ; out = (-3, 0, 0) ; Re = 0.1
Quadrupole     :  in  = (-3, 0, 0) ; out = (-3, 1, 0) ; Re = 0.1 ; b = -1.2
Section droite :  in  = (-3, 1, 0) ; out = (-3, 2, 0) ; Re = 0.1
Dipole         :  in  = (-3, 2, 0) ; out = (-2, 3, 0) ; Re = 0.1 ; Rc = 1 ; Cc = (-2, 2, 0) ; B=(0, 0, 5.89158)
Quadrupole     :  in  = (-2, 3, 0) ; out = (-1, 3, 0) ; Re = 0.1 ; b = 1.2
Section droite :  in  = (-1, 3, 0) ; out = (0, 3, 0) ; Re = 0.1
Quadrupole     :  in  = (0, 3, 0) ; out = (1, 3, 0) ; Re = 0.1 ; b = -1.2
Section droite :  in  = (1, 3, 0) ; out = (2, 3, 0) ; Re = 0.1
Dipole         :  in  = (2, 3, 0) ; out = (3, 2, 0) ; Re = 0.1 ; Rc = 1 ; Cc = (2, 2, 0) ; B=(0, 0, 5.89158)
 *
 *
 *L'accélérateur contient les 2 particules suivantes :
Une particule :
  position : (3.01, 0, 0)
  vitesse  : (0, -2.64754e+08, 0)
  gamma    : 2.13158
  energie (GeV) : 2
  masse   (GeV/c^2) : 0.938272
  charge   : 1.60217653e-19
  force    : ( 0 ; 0 ; 0 )

Une particule :
  position : (2.99, 0, 0)
  vitesse  : (0, -2.64754e+08, 0)
  gamma    : 2.13158
  energie (GeV) : 2
  masse   (GeV/c^2) : 0.938272
  charge   : 1.60217653e-19
  force    : ( 0 ; 0 ; 0 )
 *
 */

	double B = 5.8915820038873;
	double b = 1.2;
	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.1, 1.0, b);
	Dipole e2 = Dipole(e1.getExitPosition(), Vector3D(2, -3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.1, 1, b);
	Dipole e4 = Dipole(e3.getExitPosition(), Vector3D(-3, -2, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.1, 1.0, b);
	Dipole e6 = Dipole(e5.getExitPosition(), Vector3D(-2, 3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.1, 1.0, b);
	Dipole e8 = Dipole(e7.getExitPosition(), e1.getEntryPosition(), 0.1, 1, Vector3D(0, 0, B));
	Accelerator* acc = new Accelerator();
	acc->add(e1);
	acc->add(e2);
	acc->add(e3);
	acc->add(e4);
	acc->add(e5);
	acc->add(e6);
	acc->add(e7);
	acc->add(e8);

	acc->close();

	//proton
	Particle p1 = Particle(Vector3D(3.00, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	Particle p2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	acc->add(p1);
	acc->add(p2);

	//anti-proton
	Particle ap1 = Particle(Vector3D(3.00, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	Particle ap2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	acc->add(ap1);
	acc->add(ap2);



	/*std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 1000);

	for (int i = 0; i < ps.size(); ++i) {
		acc->add(ps[i]);
	}*/


	return acc;
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

	std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 100000);

	for (int i = 0; i < ps.size(); ++i) {
		acc->add(ps[i]);
	}

	acc->close();

	return acc;
}

Accelerator* linear() {
	Accelerator* acc = new Accelerator();

	for(int i = 0; i < 10; ++i) {
		FODO e = FODO(Vector3D(4, 0, 0) * i, Vector3D(4, 0, 0) * (i + 1), 0.1, 1, 1.2);
		acc->add(e);
	}

	Particle e(Vector3D(0, 0.05, 0.01), constants::PROTON_MASS, constants::E, 2 * constants::GeV, Vector3D::i);
	acc->add(e);
	acc->close();

	return acc;
}
/*
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

	Element*\ celement = acc->add(element);

	std::vector< Particle > ps = createParticles(element.getEntryPosition(), 10, constants::ELECTRON_MASS, constants::E, energy, direction);

	for (int i = 0; i < ps.size(); ++i) {
		Particle* cparticle = acc->add(ps[i]);
		cparticle->setElement(celement);
	}

	Particle* cparticle = acc->add(particle);
	cparticle->setElement(celement);
	return acc;
}*/


int main(int argc, char *argv[])
{
	try {

    QApplication app(argc, argv);

    vhc::Stage window;
    Accelerator* acc = standard();
    window.accelerator = acc;

    window.setWindowTitle("Virtual Hadron Collider");
    window.resize(QSize(500, 500));
    window.show();


    //window.showFullScreen();

    //app.setActiveWindow(&window);
    return app.exec();

	} catch (Exception& ex){
    	std::cerr << ex.toString() << "\n";
    }
}


