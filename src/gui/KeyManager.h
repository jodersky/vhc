/*
 * KeyManager.h
 *
 *  Created on: May 4, 2011
 *      Author: jakob
 */

#ifndef KEYMANAGER_H_
#define KEYMANAGER_H_

#include <set>

namespace vhc {

class Stage;

/** Classe responsable de la gestion des evenement de clavier. */
class KeyManager {

public:
	KeyManager(Stage& stage);
	virtual ~KeyManager();

	/** Une clef est appuyee. */
	void press(int key);

	/** Une clef est relachee. */
	void release(int key);

	/** Retourne vrai si la clef donnee est appuyee, faux sinon. */
	bool isPressed(int key) const;

private:

	/** Scene de ce manager. */
	Stage& stage;

	/** Ensemble des clefs actuellement appuyes. */
	std::set<int> keys;

};

}

#endif /* KEYMANAGER_H_ */
