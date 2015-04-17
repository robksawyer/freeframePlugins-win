/*
 * sfAnimatedPoint.cpp
 *
 *  Created on: Jul 20, 2010
 *      Author: marcwren
 */
#include "sfOutOfBounds.h"
#include "sfAnimatedPoint.h"
#include "Quad.h"
#include "Quart.h"
#include "Quint.h"
#include "Sine.h"
#include "Linear.h"
#include "Expo.h"
#include "Elastic.h"
#include "Cubic.h"
#include "Circ.h"
#include "Bounce.h"
#include "Back.h"

// TEMP
#include "ofMain.h"
// TEMP

sfAnimatedPoint::sfAnimatedPoint()
{
	_init( 0, 0, 0, 0.7 );
}

sfAnimatedPoint::sfAnimatedPoint( float vX, float vY, float vZ )
{
	_init( vX, vY, vZ, 0.7 );
}

sfAnimatedPoint::sfAnimatedPoint( float vX, float vY, float vZ, float vFactor )
{
	_init( vX, vY, vZ, vFactor );
}

void sfAnimatedPoint::_init( float vX, float vY, float vZ, float vFactor )
{
	x = _originX = targetX = vX;
	y = _originY = targetY = vY;
	z = _originZ = targetZ = vZ;
	_animationTime = 0;
	_animating = false;
	factor = vFactor;
	setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_IN, 30 );
}

void sfAnimatedPoint::setTarget( float vX, float vY, float vZ )
{
	// TODO The target* vars need to be the difference
	// from x/y/z (as opposed to an absolute location).
	// ie. distanceX = x +|- vX;
	// This means the current equation will need to be updated
	// to determine the absolute location.
	targetX = vX;
	targetY = vY;
	targetZ = vZ;
}

void sfAnimatedPoint::setTarget( ofxVec3f vT )
{
	setTarget( vT.x, vT.y, vT.z );
}

void sfAnimatedPoint::setAnimationType( int vType )
{
	if( vType < sfAnimatedPoint::BASIC || vType > sfAnimatedPoint::BACK )
	{
		throw sfOutOfBounds( "The animation type you specified is not a valid type." );
	}
	_animationType = vType;
}

void sfAnimatedPoint::setAnimationDirection( int vDirection )
{
	if( vDirection < sfAnimatedPoint::EASE_IN || vDirection > sfAnimatedPoint::EASE_IN_OUT )
	{
		throw sfOutOfBounds( "The direction type you specified is not a valid type." );
	}

	_animationEasing = vDirection;
}

void sfAnimatedPoint::setAnimationDuration( int vDuration )
{
	_animationDuration = vDuration;
}

void sfAnimatedPoint::start()
{
	_animating = true;
	_animationTime = 0;
	_originX = x;
	_originY = y;
	_originZ = z;
}

void sfAnimatedPoint::pause()
{
	_animating = false;
}

void sfAnimatedPoint::setAnimation( int vType, int vDirection, int vDuration )
{
	setAnimationType( vType );
	setAnimationDirection( vDirection );
	setAnimationDuration( vDuration );
}

bool sfAnimatedPoint::isAnimating()
{
	return _animating;
}

void sfAnimatedPoint::update()
{
	if( _animating )
	{
		++_animationTime;

		float vChangeX = targetX - _originX;
		float vChangeY = targetY - _originY;
		float vChangeZ = targetZ - _originZ;
		float vX, vY, vZ;

		// TODO There is probably a much better way of doing this. Pass a
		// closure? A pointer? Use a template?
		switch( _animationType )
		{
			case sfAnimatedPoint::LINEAR:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Linear::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Linear::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Linear::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Linear::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Linear::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Linear::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Linear::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Linear::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Linear::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::QUAD:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Quad::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quad::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quad::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Quad::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quad::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quad::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Quad::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quad::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quad::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::QUART:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Quart::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quart::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quart::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Quart::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quart::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quart::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Quart::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quart::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quart::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::QUINT:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Quint::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quint::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quint::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Quint::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quint::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quint::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Quint::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Quint::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Quint::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::SINE:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Sine::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Sine::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Sine::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Sine::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Sine::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Sine::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Sine::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Sine::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Sine::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::EXPO:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Expo::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Expo::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Expo::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Expo::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Expo::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Expo::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Expo::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Expo::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Expo::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::ELASTIC:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Elastic::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Elastic::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Elastic::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Elastic::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Elastic::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Elastic::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Elastic::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Elastic::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Elastic::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::CUBIC:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Cubic::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Cubic::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Cubic::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Cubic::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Cubic::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Cubic::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Cubic::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Cubic::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Cubic::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::CIRC:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Circ::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Circ::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Circ::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Circ::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Circ::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Circ::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Circ::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Circ::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Circ::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::BOUNCE:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Bounce::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Bounce::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Bounce::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Bounce::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Bounce::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Bounce::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Bounce::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Bounce::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Bounce::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::BACK:
				switch( _animationEasing )
				{
					case sfAnimatedPoint::EASE_OUT:
						vX = Back::easeOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Back::easeOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Back::easeOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN_OUT:
						vX = Back::easeInOut( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Back::easeInOut( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Back::easeInOut( _animationTime, _originZ, vChangeZ, _animationDuration );
						break;
					case sfAnimatedPoint::EASE_IN:
					default:
						vX = Back::easeIn( _animationTime, _originX, vChangeX, _animationDuration );
						vY = Back::easeIn( _animationTime, _originY, vChangeY, _animationDuration );
						vZ = Back::easeIn( _animationTime, _originZ, vChangeZ, _animationDuration );
					break;
				}
				break;
			case sfAnimatedPoint::BASIC:
			default:
				vX = x + ( targetX - x ) * factor;
				vY = y + ( targetY - y ) * factor;
				vZ = z + ( targetZ - z ) * factor;
			break;
		}

		x = vX;
		y = vY;
		z = vZ;

		if( _animationType != sfAnimatedPoint::BASIC && _animationTime >= _animationDuration )
		{
			_animating = false;
		}
		// TODO Stop animating if within X distance.
//		else if( _animationType == sfAnimatedPoint::BASIC )
//		{
//
//		}
	}
}
