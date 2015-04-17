/*
 * sfOutOfBounds.cpp
 *
 *  Created on: Aug 9, 2010
 *      Author: marcwren
 */

#include "sfOutOfBounds.h"

sfOutOfBounds::sfOutOfBounds( string vMessage )
{
	_message = vMessage;
}

sfOutOfBounds::~sfOutOfBounds() throw()
{

}

const char* sfOutOfBounds::what() const throw()
{
	return _message.c_str();
}
