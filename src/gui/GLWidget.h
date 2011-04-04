#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "Camera.h"

class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget (QWidget* parent = 0);
	~GLWidget ();

	QSize minimumSizeHint () const;
	QSize sizeHint () const;

	double eyeX;
	double eyeY;
	double eyeZ;

	Camera camera;
	bool wireframe;


protected:

	void initializeGL ();
	void paintGL ();
	void resizeGL (int width, int height);
	void mousePressEvent (QMouseEvent* event);
	void mouseReleaseEvent (QMouseEvent* event);
	void keyPressEvent (QKeyEvent* event);
	void keyReleaseEvent (QKeyEvent* event);
};

#endif
