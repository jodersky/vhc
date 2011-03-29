/*
 * Main.cc
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#include <QApplication>
#include <QWidget>
#include "GLWidget.h"
#include "Vector3D.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GLWidget window;
    vhc::Vector3D s = vhc::Vector3D::i;

    window.resize(250, 150);
    window.setWindowTitle("Virtual Hadron Collider");
    window.show();

    return app.exec();
}
