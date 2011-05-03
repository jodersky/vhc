/*
 * AcceleratorBenchmarkTest.cc
 *
 *  Created on: May 2, 2011
 *      Author: jakob
 */

#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include "exceptions.h"
#include "Accelerator.h"
#include "StraightElement.h"
#include "Dipole.h"
#include "Particle.h"
#include "FODO.h"
#include "Vector3D.h"
#include "constants.h"

using namespace vhc;
using namespace std;

std::vector< Particle > createParticles(const Vector3D& position, int n, double mass = constants::ELECTRON_MASS, double charge = constants::E, double energy = 1E9 * constants::E, Vector3D direction = -Vector3D::j) {
	std::vector< Particle > v;

	double r = 0.1;

	for (int i = 0; i < n; ++i) {
		double x = (rand() % 1000) / 1000.0 * r;
		double y = (rand() % 1000) / 1000.0 * sqrt(r * r - x * x);
		double z = (rand() % 1000) / 1000.0 * sqrt(r * r - y * y - x * x);
		v.push_back(Particle(position + Vector3D(x, y, z), mass, charge, energy, direction));
	}

	return v;
}

Accelerator* standard() {
	double B = 5.8915820038873;
	double b = 1.2;
	FODO e1 = FODO(Vector3D(3, 2, 0), Vector3D(3, -2, 0), 0.1, 1.0, b);
	Dipole e2 = Dipole(e1.getExitPosition(), Vector3D(2, -3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e3 = FODO(e2.getExitPosition(), Vector3D(-2, -3, 0), 0.1, 1, b);
	Dipole e4 = Dipole(e3.getExitPosition(), Vector3D(-3, -2, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e5 = FODO(e4.getExitPosition(), Vector3D(-3, 2, 0), 0.1, 1.0, b);
	Dipole e6 = Dipole(e5.getExitPosition(), Vector3D(-2, 3, 0), 0.1, 1, Vector3D(0, 0, B));
	FODO e7 = FODO(e6.getExitPosition(), Vector3D(2, 3, 0), 0.1, 1.0, b);
	Dipole e8 = Dipole(e7.getExitPosition(), e1.getEntryPosition(), 0.1, 1, Vector3D(0, 0, B));
	Accelerator* acc = new Accelerator();
	acc->add(e1);
	acc->add(e2);
	acc->add(e3);
	acc->add(e4);
	acc->add(e5);
	acc->add(e6);
	acc->add(e7);
	acc->add(e8);

	acc->close();

	Particle p1 = Particle(Vector3D(3.00, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	Particle p2 = Particle(Vector3D(2.99, 0, 0), constants::PROTON_MASS, constants::E, 2 * constants::GeV, -Vector3D::j);
	acc->add(p1);
	acc->add(p2);

	std::vector< Particle > ps = createParticles(e1.getEntryPosition(), 10000);

	for (int i = 0; i < ps.size(); ++i) {
		acc->add(ps[i]);
	}


	return acc;
}

Accelerator* accelerator;

int main() {
	accelerator = standard();

	int steps = 1000;
	double dt = 1E-11;

	cout << "Simulating " << steps << " steps with " << accelerator->getParticles().size() << " particles...";
	cout.flush();
	int t0 = clock();
	for (int i = 0; i < steps; ++i) {
		accelerator->step(dt);
	}
	int t1 = clock() - t0;
	cout << "DONE" << endl;

	cout << "Time taken: " << t1 << " ticks @ " << CLOCKS_PER_SEC << " ticks/s ~ " << 1.0 * t1 / CLOCKS_PER_SEC << "s" << endl;
	cout << "Average: " << 1.0 * t1 / CLOCKS_PER_SEC / steps << " s/step" << endl;
	cout << "Average: " << 1.0 * t1 / CLOCKS_PER_SEC / steps / accelerator->getParticles().size() << " s/step/particle" << endl;

	return 0;
}


