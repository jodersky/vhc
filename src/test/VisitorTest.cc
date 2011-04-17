/*
 * VisitorTest.cc
 *
 *  Created on: Apr 3, 2011
 *      Author: jakob
 */

#include <iostream>
#include <vector>
#include "Element.h"
#include "CompositeElement.h"
#include "StraightElement.h"
#include "CurvedElement.h"
#include "Quadrupole.h"
#include "Dipole.h"
#include "FODO.h"
#include "ElementVisitor.h"
#include "Vector3D.h"
using namespace std;
using namespace vhc;

class PrintVisitor: public ElementVisitor {
public:

	virtual void visit(const StraightElement* straight) const {
		cout << "A straight element." << endl;
	}

	virtual void visit(const Quadrupole* quadrupole) const {
		cout << "A quadrupole." << endl;
	}

	virtual void visit(const Dipole* dipole) const {
		cout << "A dipole." << endl;
	}


};

int main() {
	PrintVisitor pv;
	Dipole* dp = new Dipole (Vector3D::Null, Vector3D::i, 0.2, 0.5);
	Quadrupole* qp = new Quadrupole(Vector3D::Null, Vector3D::i, 0.2, 2);
	FODO* fodo = new FODO(Vector3D::Null, Vector3D::i, 0.2, 0.25, 2.0);
	vector<Element*> elements;
	elements.push_back(dp);
	elements.push_back(qp);
	elements.push_back(fodo);

	for (int i = 0; i < elements.size(); ++i) {
		elements[i]->accept(pv);
	}

	for (int i = 0; i < elements.size(); ++i) {
		delete elements[i];
		elements[i] = NULL;
	}

	return 0;
}
