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
//#include "FODO.h"
#include "Quadrupole.h"
#include "Element.h"
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

Element** FODO(Vector3D entry, Vector3D exit, double Rs, double L, double b) {
	double l = (entry - exit).norm() / 2.0 - 1;
	Vector3D d = (exit - entry).unit();
	Quadrupole* fq = new Quadrupole(entry, entry + d * l, Rs, b);
	StraightElement* s1 = new StraightElement(fq->getExitPosition(), fq->getExitPosition() + d * L, Rs);
	Quadrupole* dq = new Quadrupole(s1->getExitPosition(), s1->getExitPosition() + d * l, Rs, -b);
	StraightElement* s2 = new StraightElement(dq->getExitPosition(), exit, Rs);
	Element** fodo = new Element*[4];
	(fodo)[0] = fq;
	(fodo)[1] = s1;
	(fodo)[2] = dq;
	(fodo)[3] = s2;

	return fodo;
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
	Element** e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.1, 1.0, b);

	//FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.1, 1.0, b);
	Dipole e2 = Dipole(Vector3D(3, -2, 0), Vector3D(2, -3, 0), 0.1, 1, Vector3D(0, 0, B));

	Element** e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.1, 1, b);
	Dipole e4 = Dipole(Vector3D(-2, -3, 0), Vector3D(-3, -2, 0), 0.1, 1, Vector3D(0, 0, B));
	Element** e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.1, 1.0, b);
	Dipole e6 = Dipole(Vector3D(-3, 2, 0), Vector3D(-2, 3, 0), 0.1, 1, Vector3D(0, 0, B));
	Element** e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.1, 1.0, b);
	Dipole e8 = Dipole(Vector3D(2, 3, 0), Vector3D(3, 2, 0), 0.1, 1, Vector3D(0, 0, B));
	Accelerator* acc = new Accelerator();
	//acc->add(e1);
	for (int i = 0; i < 4; ++i) acc->add(e1[i][0]);
	acc->add(e2);
	for (int i = 0; i < 4; ++i) acc->add(e3[i][0]);
	//acc->add(e3);
	acc->add(e4);
	for (int i = 0; i < 4; ++i) acc->add(e5[i][0]);
	//acc->add(e5);
	acc->add(e6);
	for (int i = 0; i < 4; ++i) acc->add(e7[i][0]);
	//acc->add(e7);
	acc->add(e8);

	acc->close();

	//proton
	Particle p1 = Particle(Vector3D(3.01, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	Particle p2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	acc->add(p1);
	acc->add(p2);

	//anti-proton
	Particle ap1 = Particle(Vector3D(3.01, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	Particle ap2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	acc->add(ap1);
	acc->add(ap2);



	/*std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 1000);

	for (int i = 0; i < ps.size(); ++i) {
		acc->add(ps[i]);
	}*/


	return acc;
}


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


    window.showFullScreen();

    //app.setActiveWindow(&window);
    return app.exec();

	} catch (Exception& ex){
    	std::cerr << ex.toString() << "\n";
    }
}


