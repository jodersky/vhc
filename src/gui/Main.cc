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
#include "Vector3D.h"


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

    vhc::Particle p(se.getEntryPosition(), 1, 1);
    accelerator.add(p);

    vhc::Stage window;
    window.accelerator = &accelerator;
    window.showFullScreen();

    //window.resize(QSize(500, 500));
    window.setWindowTitle("Virtual Hadron Collider");
    window.show();

    return app.exec();
}
