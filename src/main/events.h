/*
 * events.h
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#ifndef EVENTS_H_
#define EVENTS_H_

#include <list>
#include "Particle.h"

namespace vhc {

/** Classe de base de tout evenement. */
class Event {

private:

	/** Pointeur sur le createur de cet evenement. */
	void *const sender;

public:

	Event(void *const sender);
	virtual ~Event();

	/** Retourne le createur de cet evenement. */
	void *const getSender() const;

};

/** Classe de base de tout evenement de particules. */
class ParticleEvent: public Event {
private:

	/** Pointeur sur la particule de cet evenement. */
	Particle *const particle;

public:

	ParticleEvent(void *const sender, Particle *const particle);
	virtual ~ParticleEvent();

	/** Retourne la particule consideree lors de cet evenement. */
	Particle *const getParticle() const;

};

/** Evenemnt representant l'ajout d'une particule. */
class ParticleAddedEvent: public ParticleEvent {

public:

	/** Cree un nouveau evenement d'ajout de particule.
	 *  @param sender origine de cet evenement
	 *  @param particle particule ajoutee */
	ParticleAddedEvent(void *const sender, Particle *const particle);

	virtual ~ParticleAddedEvent();
};

/** Evenemnt representant l'enlevement d'une particule. */
class ParticleRemovedEvent: public ParticleEvent {
public:

	/** Cree un nouveau evenement d'enlevement de particule.
	 *  @param sender origine de cet evenement
	 *  @param particle particule enlevee */
	ParticleRemovedEvent(void *const sender, Particle *const particle);
	virtual ~ParticleRemovedEvent();
};

template<typename T>
/** Represente un ecouteur d'evenements. Tout ecouteur peur se souscrire a un publicateur d'evenements pour ainsi etre
 *  informee de tout evenement.
 *  @see vhc::Publisher */
class Listener {

public:

	/** Methode appelee par un publicateur lors d'un evenement. Cette methode
	 *  represente la reaction de l'ecouteur lors d'un evenement et est a
	 *  implementer par tout ecouteur concret. */
	virtual void react(const T& event) = 0;

};

template<typename T>
/** Represente un publicateur d'evenements. Un publicateur peut publier un evenement a tous ses ecouteurs souscrits.
 *  @see vhc::Listener */
class Publisher {

private:

	/** Type de collection des ecouteurs. */
	typedef std::list< Listener<T> * > ListenerCollection;

	/** Ecouteurs souscrits a ce publicateur. */
	ListenerCollection listeners;

protected:

	Publisher(): listeners(0) {};
	virtual ~Publisher() {};

	/** Publie un evenement a tous les ecouteurs de ce publicateur. */
	void publish(const T& event) {
		for (typename ListenerCollection::iterator i = listeners.begin(); i != listeners.end(); ++i) {
			(**i).react(event);
		}
	}

public:

	/** Souscrit l'ecouteur donne a ce publicateur. */
	void subscribe(Listener<T>* listener) {
		listeners.push_back(listener);
	}

	/** Retire l'ecouteur donne de ce publicateur. */
	void unsubscribe(Listener<T>* listener) {
		listeners.remove(listener);
	}

};

}

#endif /* EVENTS_H_ */
