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
#include "BeamRenderer.h"
#include "Element.h"
#include "Accelerator.h"
#include "util.h"


namespace vhc {

/** Une scene gere la representation graphique d'un accelerateur. */
class Stage: public QGLWidget {

	Q_OBJECT

public:

	Stage(QWidget* parent = NULL);
	virtual ~Stage();

	/** Retourne la camera de cette scene. */
	Camera& getCamera();

	/** Retourne le mode de representation. */
	void setDisplayMode(util::DisplayMode value);

	/** Affecte le mode de representation. */
	util::DisplayMode getDisplayMode() const;

	/** Retourne l'etat de la simulation. */
	bool isRunning() const;

	/** Affecte l'etat de simulation. */
	void setRunning(bool value);

	ElementRenderer* getElementRenderer() const;
	void setElementRenderer(ElementRenderer* value);

	BeamRenderer* getBeamRenderer() const;
	void setBeamRenderer(BeamRenderer* value);


	/** Retourne l'accelerateur de cette scene. */
	Accelerator* getAccelerator() const;

	/** Affecte l'accelerateur de cette scene. */
	void setAccelerator(Accelerator* accelerator);

	/** Retourne le pas de temps utilise pour simuler l'accelerateur de cette scene. */
	double getStep() const;

	/** Affecte le pas de temps utilise pour simuler l'accelerateur de cette scene. */
	void setStep(double value);

protected:

	/** Ecrit du texte sur l'ecran. */
	void displayText(QString text[], int size);

	void initializeGL();
	void resizeGL (int width, int height);
	void paintGL();

	void mousePressEvent (QMouseEvent* event);
	//void mouseReleaseEvent (QMouseEvent* event);
	void keyPressEvent (QKeyEvent* event);
	void keyReleaseEvent (QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:

	Accelerator* accelerator;

	//io
	KeyManager keyManager;

	//graphics
	bool captured;

	Camera camera;
	ElementRenderer* elementRenderer;
	BeamRenderer* beamRenderer;
	QPoint center;
	util::DisplayMode displayMode;

	//simulation
	QTimer* timer;
	QTime time;
	int frameTime; //ms
	double h;
	bool paused;





};

}

#endif /* STAGE_H_ */
