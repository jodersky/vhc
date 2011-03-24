/*
 * Main.cc
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#include <QApplication>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;

    window.resize(250, 150);
    window.setWindowTitle("Virtual Hadron Collider");
    window.show();

    return app.exec();
}
