/*
 * Stage.h
 *
 *  Created on: Apr 6, 2011
 *      Author: jakob
 */

#ifndef STAGE_H_
#define STAGE_H_

#include <QGLWidget>
#include "Camera.h"


namespace vhc {

class Stage: public QGLWidget {

	Q_OBJECT

public:
	Stage(QWidget* parent);
	virtual ~Stage();

protected:

	void initializeGL();
	void resizeGL (int width, int height);
	void paintGL();

	void mousePressEvent (QMouseEvent* event);
	void mouseReleaseEvent (QMouseEvent* event);
	void keyPressEvent (QKeyEvent* event);
	void keyReleaseEvent (QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:

	Camera camera;

	bool wireframe;


};

}

#endif /* STAGE_H_ */
