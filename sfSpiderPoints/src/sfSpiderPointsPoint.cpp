/*
 * sfSpiderPointsPoint.cpp
 *
 *  Created on: Dec 27, 2010
 *      Author: marc.wren
 */

#include "sfSpiderPointsPoint.h"

sfSpiderPointsPoint::sfSpiderPointsPoint()
{
	_isHiding = false;
	_isHidden = false;
	// TODO This should be determined somehow.
	_origin = ofxVec3f( 0, 0, 0 );
}

bool sfSpiderPointsPoint::isHidden()
{
	if( _isHiding && x == _origin.x && y == _origin.y && z == _origin.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool sfSpiderPointsPoint::isHiding()
{
	return _isHiding;
}

void sfSpiderPointsPoint::hide()
{
	hide( _origin.x, _origin.y, _origin.z );
}

void sfSpiderPointsPoint::hide( float vX, float vY, float vZ )
{
	if( !_isHiding )
	{
		_origin.set( vX, vY, vZ );
		setTarget( vX, vY, vZ );
		start();
		_isHiding = true;
	}
}

void sfSpiderPointsPoint::unhide()
{
	if( _isHiding )
	{
		_isHiding = false;
		pause();
	}
}
