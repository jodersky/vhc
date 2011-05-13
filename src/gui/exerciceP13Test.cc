/*
 * exerciceP13Test.cc
 *
 *  Created on: 11 mai 2011
 *      Author: christian
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
#include "exerciceP11Test.cc"
#include <vector>

using namespace std;
using namespace vhc;

int main(int argc, char *argv[])
{
	try {

    QApplication app(argc, argv);

    vhc::Stage window;
    Accelerator* acc = creatAccChap();
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
