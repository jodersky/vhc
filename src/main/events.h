/*
 * events.h
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <list>
#include <algorithm>
#include "Particle.h"

namespace vhc {

class Event {

private:
	void *const sender;

public:
	Event(void *const sender);
	virtual ~Event();

	void *const getSender() const;

};

class ParticleEvent: public Event {
private:
	Particle *const particle;
public:

	ParticleEvent(void *const sender, Particle *const particle);
	virtual ~ParticleEvent();

	Particle *const getParticle() const;

};

class ParticleAddedEvent: public ParticleEvent {
public:
	ParticleAddedEvent(void *const sender, Particle *const particle);
	virtual ~ParticleAddedEvent();
};

class ParticleRemovedEvent: public ParticleEvent {
public:
	ParticleRemovedEvent(void *const sender, Particle *const particle);
	virtual ~ParticleRemovedEvent();
};

template<typename T>
class Listener {

public:

	virtual void react(const T& event) = 0;

};

template<typename T>
class Publisher {

private:

	typedef std::list< Listener<T> * > ListenerCollection;
	ListenerCollection listeners;

protected:

	Publisher(): listeners(0) {};
	virtual ~Publisher() {};

	void publish(const T& event) {
		for (typename ListenerCollection::iterator i = listeners.begin(); i != listeners.end(); ++i) {
			(**i).react(event);
		}
	}

public:

	void subscribe(Listener<T>* listener) {
		listeners.push_back(listener);
	}

	void unsubscribe(Listener<T>* listener) {
		listeners.remove(listener);
	}

};

}

#endif /* EVENTS_H_ */
