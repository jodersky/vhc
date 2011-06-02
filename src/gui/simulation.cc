#include <iostream>
#include <QApplication>
#include "Stage.h"
#include "Accelerator.h"
#include "SAPInteractor.h"
#include "CircularBeam.h"
#include "Bunch.h"
#include "Particle.h"
#include "Element.h"
#include "Dipole.h"
#include "Quadrupole.h"
#include "FODO.h"
#include "Vector3D.h"
#include "exceptions.h"

using namespace std;
using namespace vhc;

Accelerator* makeStandard() {
	double B = 5.8915820038873;
	double b = 1.2;

	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.1, 1.0, b);
	Dipole e2 = Dipole(Vector3D(3, -2, 0), Vector3D(2, -3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.1, 1, b);
	Dipole e4 = Dipole(Vector3D(-2, -3, 0), Vector3D(-3, -2, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.1, 1.0, b);
	Dipole e6 = Dipole(Vector3D(-3, 2, 0), Vector3D(-2, 3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.1, 1.0, b);
	Dipole e8 = Dipole(Vector3D(2, 3, 0), Vector3D(3, 2, 0), 0.1, 1, Vector3D(0, 0, B));

	Accelerator* acc = new Accelerator(new SAPInteractor);
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
	Particle p1 = Particle(Vector3D(3.01, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	Particle p2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	acc->add(p1);
	acc->add(p2);

	//anti-proton
	Particle ap1 = Particle(Vector3D(3.01, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	Particle ap2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, -constants::E, 2 * constants::GeV, Vector3D::j);
	acc->add(ap1);
	acc->add(ap2);

	//faisceau circulaire
	acc->add(CircularBeam(p1, 20, 1));

	//bunch
	double emittance = 5E-6; //m
	double A_12 = 0.02; //1/m
	double A_22 = 4;//E-19; // s² m-1 (dépend totalement de l'accélérateur)
	double length = 300E-12 * constants::C;
	double stdDev = 0.1;
	acc->add(Bunch(p1, 500, 1, stdDev, length, emittance, A_12, A_22));

	return acc;
}

int main(int argc, char *argv[])
{
	try {

    QApplication app(argc, argv);

    vhc::Stage window;
    Accelerator* acc = makeStandard();
    window.setAccelerator(acc);

    window.setWindowTitle("Virtual Hadron Collider");
    window.resize(QSize(800, 800));
    window.show();


   // window.showFullScreen();
    return app.exec();

	} catch (Exception& ex){
    	std::cerr << ex.toString() << "\n";
    	throw;
    }
}
