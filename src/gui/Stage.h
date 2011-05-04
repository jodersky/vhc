/*
 * Stage.h
 *
 *  Created on: Apr 6, 2011
 *      Author: jakob
 */

#ifndef STAGE_H_
#define STAGE_H_

#include <vector>
#include <QGLWidget>
#include <QtOpenGL>
#include "Camera.h"
#include "KeyManager.h"
#include "ElementRenderer.h"
#include "ParticleRenderer.h"
#include "Element.h"
#include "Accelerator.h"
#include "util.h"


namespace vhc {

class Stage: public QGLWidget {

	Q_OBJECT

public:

	Stage(QWidget* parent = NULL);
	virtual ~Stage();

	Camera& getCamera();

	void setDisplayMode(util::DisplayMode value);
	util::DisplayMode getDisplayMode() const;

	bool isRunning() const;
	void setRunning(bool value);

	ElementRenderer& getElementRenderer();
	ParticleRenderer& getParticleRenderer();


	//TODO !!! temporary
	Accelerator* accelerator;

protected:

	void displayText(QString text[], int size);

	void initializeGL();
	void resizeGL (int width, int height);
	void paintGL();

	//void mousePressEvent (QMouseEvent* event);
	//void mouseReleaseEvent (QMouseEvent* event);
	void keyPressEvent (QKeyEvent* event);
	void keyReleaseEvent (QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	Camera camera;
	KeyManager keyManager;

	QTimer* timer;
	QTime time;
	int frameTime; //ms

	double h;
	bool paused;

	ElementRenderer elementRenderer;
	ParticleRenderer particleRenderer;

	util::DisplayMode displayMode;

	QPoint center;

};

}

#endif /* STAGE_H_ */
