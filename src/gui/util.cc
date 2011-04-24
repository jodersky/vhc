/*
 * util.cc
 *
 *  Created on: Apr 2, 2011
 *      Author: jakob
 */
#include <QtOpenGL>

namespace vhc {
namespace util {

void torus(double R, double r, double fraction, int slices, int stacks) {
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * M_PI;
   for (i = 0; i < slices; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= stacks * fraction ; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % slices;// + 0.5;
            t = j % stacks;

            x = (R+r*cos(s*twopi/slices))*cos(t*twopi/stacks);
            y = (R+r*cos(s*twopi/slices))*sin(t*twopi/stacks);
            z = r * sin(s * twopi / slices);
           // glColor3d(0, 1 - 1.0 * j / (stacks * fraction), 1.0 * j / (stacks * fraction));
            glVertex3d(x, y, z);
         }
      }
      glEnd();
   }
}

void cylinder(double base, double top, double height, int slices, int stacks) {
	GLUquadric* q = gluNewQuadric();
	gluCylinder(q, base, top, height, slices, stacks);
	gluDeleteQuadric(q);
}

void sphere(double radius, int slices, int stacks) {
	GLUquadric* q = gluNewQuadric();
	gluSphere(q, radius, slices, stacks);
	gluDeleteQuadric(q);
}

void axes() {
	glBegin(GL_LINES);
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);
	glEnd();
}

void grid(int divisions) {
	int size = divisions / 2;
	glBegin(GL_LINES);
	for (int i = 0; i <= 2 * size; ++i) {
		glVertex3d(1.0 * (i - size) / size, -1, 0);
		glVertex3d(1.0 * (i - size) / size, 1, 0);
	};
	glEnd();
	glBegin(GL_LINES);
	for (int i = 0; i <= 2 * size; ++i) {
		glVertex3d(-1, 1.0 * (i - size) / size, 0);
		glVertex3d(1, 1.0 * (i - size) / size, 0);
	};
	glEnd();
}

void crosshair() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	double vp[4];
	glGetDoublev(GL_VIEWPORT, vp);
	glOrtho(vp[0], vp[2], vp[1], vp[3],-1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glTranslated(vp[2] / 2, vp[3] / 2, 0);

	glBegin(GL_LINES);
	glVertex3d(-5, 0,0);
	glVertex3d(-2, 0, 0);

	glVertex3d(2, 0, 0);
	glVertex3d(5, 0, 0);

	glVertex3d(0,-5,0);
	glVertex3d(0, -2, 0);

	glVertex3d(0, 2,0);
	glVertex3d(0, 5, 0);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

}
}
