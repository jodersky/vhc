/*
 * exception.h
 *
 *  Created on: Mar 24, 2011
 *      Author: jakob
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <sstream>
#include <string>
#include "Printable.h"

namespace vhc {

/** Classe de base representant une exception.
 *  Pour avoir une representation convenable de cette exception, appeller la methode <code>toString()</code>. */
class Exception: public Printable {

private:

	/** Message d'erreur de cette exception. */
	std::string message;

public:

	/** Constructeur par defaut. */
	Exception(): message("") {};

	/** Instancie une nouvelle exception avec le message d'erreur donne.
	 *  @param message message d'erreur*/
	Exception(std::string message): message(message) {};

	/** Destructeur virtuel. */
	virtual ~Exception() {};

	/** Retourne le type de cette exception, c'est-a-dire le nom de la classe. */
	virtual std::string getExceptionType() const {return "Exception";}

	/** Retourne le message d'erreur de cette exception. */
	virtual std::string getMessage() const {return message;}

	/** Retourne une representation en chaine de cette exception. Cette methode est a appeller pour
	 *  si on veut connaitre les details de cette exception.*/
	virtual std::string toString() const {
		std::stringstream s;
		s << getExceptionType() << ": " << getMessage();
		return s.str();
	}

};

/** Represente une exception due au passage d'un argument illegal.
 *  Exemple: si on voudrait instancier un polygone avec moins de 3 faces. */
class IllegalArgumentException: public Exception {
public:
		IllegalArgumentException(): Exception() {};
		IllegalArgumentException(std::string message): Exception(message) {};


		virtual std::string getExceptionType() const {return "IllegalArgumentException";}
};

/** Represente une exception due a l'appelle d'une operation non supportee par une instance de classe.
 *  Exemple: calculer le vecteur unitaire du vecteur nul. */
class UnsupportedOperationException: public Exception {
public:
		UnsupportedOperationException(): Exception() {};
		UnsupportedOperationException(std::string message): Exception(message) {};

		virtual std::string getExceptionType() const {return "UnsupportedOperationException";}
};


}

#endif /* EXCEPTION_H_ */
