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
#include "ElementRenderer.h"
#include "ParticleRenderer.h"
#include "Element.h"
#include "Accelerator.h"


namespace vhc {

enum DisplayMode {
	FILL = 0,
	WIREFRAME = 1,
	POINTS = 2
};

class Stage: public QGLWidget {

	Q_OBJECT

public:
	Stage(QWidget* parent = NULL);
	virtual ~Stage();

	//TODO !!! temporary
	Accelerator* accelerator;

protected:

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
	ElementRenderer* elementRenderer;
	ParticleRenderer particleRenderer;

	DisplayMode displayMode;

	int keys;
	QPoint center;

};

}

#endif /* STAGE_H_ */
