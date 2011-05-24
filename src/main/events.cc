/*
 * events.cc
 *
 *  Created on: May 23, 2011
 *      Author: jakob
 */

#include "events.h"
#include <list>

namespace vhc {

Event::Event(void *const sender): sender(sender) {}
Event::~Event() {}
void *const Event::getSender() const {return sender;}

ParticleEvent::ParticleEvent(void *const sender, Particle *const particle): Event(sender), particle(particle) {};
ParticleEvent::~ParticleEvent() {};
Particle *const ParticleEvent::getParticle() const {return particle;}

ParticleAddedEvent::ParticleAddedEvent(void *const sender, Particle *const particle): ParticleEvent(sender, particle) {};
ParticleAddedEvent::~ParticleAddedEvent() {};

ParticleRemovedEvent::ParticleRemovedEvent(void *const sender, Particle *const particle): ParticleEvent(sender, particle) {};
ParticleRemovedEvent::~ParticleRemovedEvent() {};

}
