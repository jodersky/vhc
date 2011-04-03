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
            s = (i + k) % slices + 0.5;
            t = j % stacks;

            x = (R+r*cos(s*twopi/slices))*cos(t*twopi/stacks);
            y = (R+r*cos(s*twopi/slices))*sin(t*twopi/stacks);
            z = r * sin(s * twopi / slices);
            glColor3d(0, s/slices, t/slices);
            glVertex3f(x, y, z);
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

}
}
