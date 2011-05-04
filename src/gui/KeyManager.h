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

class KeyManager {

public:
	KeyManager(Stage& stage);
	virtual ~KeyManager();

	void press(int key);
	void release(int key);
	bool isPressed(int key) const;

private:
	Stage& stage;

	std::set<int> keys;

};

}

#endif /* KEYMANAGER_H_ */
