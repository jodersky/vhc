/*
 * Main.cc
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#include <QApplication>
#include <QWidget>
#include "GLWidget.h"
#include "Stage.h"
#include "Accelerator.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "Particle.h"
#include "FODO.h"
#include "Vector3D.h"
#include <vector>

using namespace vhc;

std::vector< Particle > createParticles(const Vector3D& position, int n) {
	std::vector< Particle > v;

	for (int i = 0; i < n; ++i) {
		double x = (rand() % 100) / 1000.0;
		double y = (rand() % 100) / 1000.0;
		double z = (rand() % 100) / 1000.0;
		v.push_back(Particle(position + Vector3D(x, y, z), 1, 1));
	}

	return v;
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //GLWidget window;
    vhc::Accelerator accelerator;
    vhc::StraightElement se =  vhc::StraightElement(vhc::Vector3D::j, vhc::Vector3D::j + vhc::Vector3D::i, 0.2);
    vhc::StraightElement se2 = vhc::StraightElement(vhc::Vector3D(2,0,0), vhc::Vector3D(2,-1,0), 0.2);
    vhc::CurvedElement* ce = new vhc::Dipole(vhc::Vector3D(1,1,0), vhc::Vector3D::i * 2, 0.2, 1, vhc::Vector3D::Null);
    accelerator.add(se);
    accelerator.add(se2);
    accelerator.add(*ce);

	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.2, 1.0, 5.0);
	Dipole e2 = Dipole(e1.getExitPosition(), Vector3D(2, -3, 0), 0.2, 1);
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.2, 1, 5.0);
	Dipole e4 = Dipole(e3.getExitPosition(), Vector3D(-3, -2, 0), 0.2, 1);
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.2, 1.0, 5.0);
	Dipole e6 = Dipole(e5.getExitPosition(), Vector3D(-2, 3, 0), 0.2, 1);
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.2, 1.0, 5.0);
	Dipole e8 = Dipole(e7.getExitPosition(), e1.getEntryPosition(), 0.2, 1);
	Accelerator acc;
	acc.add(e1);
	acc.add(e2);
	acc.add(e3);
	acc.add(e4);
	acc.add(e5);
	acc.add(e6);
	acc.add(e7);
	acc.add(e8);


    vhc::Particle p(e1.getEntryPosition(), 1, 1);
    acc.add(p);

    std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 1000);

    for (int i = 0; i < ps.size(); ++i) {
    	acc.add(ps[i]);
    }


    vhc::Stage window;
    window.accelerator = &acc;
    window.showFullScreen();

    //window.resize(QSize(500, 500));
    window.setWindowTitle("Virtual Hadron Collider");
    window.show();

    return app.exec();
}
