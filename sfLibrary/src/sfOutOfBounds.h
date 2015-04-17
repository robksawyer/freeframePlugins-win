/*
 * An exception to throw when an "out of bounds" error occurs.
 *
 *  Created on: Aug 9, 2010
 *      Author: marcwren
 */

#ifndef SFOUTOFBOUNDS_H_
#define SFOUTOFBOUNDS_H_

#include <exception>
#include <string>

using namespace std;

class sfOutOfBounds: public exception
{
	public:
		/**
		 * Create an exception with the message specified.
		 * @param vMessage The message to display.
		 */
		sfOutOfBounds( string vMessage );

		~sfOutOfBounds() throw();

		const char* what() const throw();

	private:
		string _message;
};

#endif /* SFOUTOFBOUNDS_H_ */
