/*
 * KeyManager.cc
 *
 *  Created on: May 4, 2011
 *      Author: jakob
 */

#include "KeyManager.h"
#include "Stage.h"
#include "util.h"
#include <QGLWidget>

using namespace vhc::util;

namespace vhc {


KeyManager::KeyManager(Stage& stage): stage(stage), keys() {

}

KeyManager::~KeyManager() {}

void KeyManager::press(int key) {
	std::set<int>::iterator it = keys.begin();

	keys.insert(it, key);

	switch(key) {
		case Qt::Key_Escape:
			QApplication::exit(0);
			break;
		case Qt::Key_1:
			stage.setDisplayMode(FILL);
			break;
		case Qt::Key_2:
			stage.setDisplayMode(WIREFRAME);
			break;
		case Qt::Key_3:
			stage.setDisplayMode(POINTS);
			break;
		case Qt::Key_Space:
			stage.setRunning(!stage.isRunning());
			break;
		case Qt::Key_QuoteLeft:
			stage.getParticleRenderer().enableDrawSpheres(!stage.getParticleRenderer().isDrawSpheresEnabled());
			break;
		default:
			break;
	}

};

void KeyManager::release(int key) {
	keys.erase(key);
}

bool KeyManager::isPressed(int key) const {
	return (keys.find(key) != keys.end());
}



}
