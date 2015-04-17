/*
 * sfJuniperPoint.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: marc.wren
 */

#include "sfJuniperPoint.h"
#include "sfDrawingUtil.h"

sfJuniperPoint::sfJuniperPoint()
{
	_init();
}

sfJuniperPoint::sfJuniperPoint( float vR )
{
	_init();
	_initialRotation = vR;
}

void sfJuniperPoint::_init()
{
	index = 0;
	_deactivatedColor = 0xffffff;
	_activateAnimationDuration = 10;
	_deactivateAnimationDuration = 60;
	_showAnimationDuration = 15;
	_hideAnimationDuration = 15;
	_locationAnimationDuration = 30;
	_alpha = 0.5;
	_activeAlphaMultiplier = 1.5;
	_rotation = 0;
	_initialRotation = 0;
	_subRotation = 0;
	_hidden = true;
	_isActive = false;
	_width = 100;
	_height = 200;
	sfCirclePoint _renderer( _width, _height );

	_colorAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_IN, _activateAnimationDuration );
	_alphaAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_OUT, _showAnimationDuration );
	_rotationAnimator.setAnimation( sfAnimatedPoint::CIRC, sfAnimatedPoint::EASE_OUT, _showAnimationDuration );
	_locationAnimator.setAnimation( sfAnimatedPoint::CIRC, sfAnimatedPoint::EASE_OUT, _locationAnimationDuration );
}

void sfJuniperPoint::setRotation( float vR )
{
	_rotation = vR;
	_rotationAnimator.setTarget( vR, 0, 0 );
	_rotationAnimator.start();
}

void sfJuniperPoint::setSubRotation( float vR )
{
	_subRotation = vR;
}

void sfJuniperPoint::setXOffset( float vX )
{
	_xOffset = vX;
}

void sfJuniperPoint::setYOffset( float vY )
{
	_yOffset = vY;
}

void sfJuniperPoint::setOffset( float vX, float vY )
{
	_xOffset = vX;
	_yOffset = vY;
}

void sfJuniperPoint::setHeight( float vH )
{
	if( vH != _height )
	{
//		if( vH < _width )
//		{
//			vH = _width;
//		}
		_height = vH;
		_renderer = sfCirclePoint( _width, _height );
	}
}

void sfJuniperPoint::setWidth( float vW )
{
	if( _width != vW )
	{
		_width = vW;
		_renderer = sfCirclePoint( _width, _height );
	}
}

void sfJuniperPoint::setZLocation( float vZ )
{
	if( _locationAnimator.z != vZ )
	{
		_locationAnimator.setTarget( 0, 0, vZ );
		_locationAnimator.start();
	}
}

void sfJuniperPoint::setAlpha( float vA )
{
	// TODO Make sure this is in the range of 0 - 1.
	if( _alpha != vA )
	{
		_alpha = vA;
		_alphaAnimator.setTarget( vA, 0, 0 );
		_alphaAnimator.start();
	}
}

void sfJuniperPoint::setHighlightColor( int vC )
{
	_activatedColor = vC;
}

void sfJuniperPoint::activate()
{
	if( !_isActive && !_hidden )
	{
		_isActive = true;
		_colorAnimator.set( 0, 0, 0 );
		_colorAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_IN, _activateAnimationDuration );
		_colorAnimator.setTarget( 1, 0, 0 );
		_colorAnimator.start();
		_alphaAnimator.setTarget( _alpha * _activeAlphaMultiplier, 0, 0 );
		_alphaAnimator.start();
	}
}

void sfJuniperPoint::deactivate()
{
	if( _isActive && !_hidden )
	{
		_isActive = false;
		_colorAnimator.set( 1, 0, 0 );
		_colorAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_IN, _deactivateAnimationDuration );
		_colorAnimator.setTarget( 0, 0, 0 );
		_colorAnimator.start();
		_alphaAnimator.setTarget( _alpha, 0, 0 );
		_alphaAnimator.start();
	}
}

void sfJuniperPoint::show()
{
	_rotationAnimator.set( _initialRotation, 0, 0 );
	_rotationAnimator.setTarget( _rotation, 0, 0 );
	_rotationAnimator.setAnimation( sfAnimatedPoint::CIRC, sfAnimatedPoint::EASE_OUT, _showAnimationDuration );
	_rotationAnimator.start();
	_alphaAnimator.set( 0, 0, 0 );
	_alphaAnimator.setTarget( _alpha, 0, 0 );
	_alphaAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_OUT, _showAnimationDuration );
	_alphaAnimator.start();
	_hidden = false;
}

void sfJuniperPoint::hide()
{
	_rotationAnimator.setTarget( 0, 0, 0 );
	_rotationAnimator.setAnimation( sfAnimatedPoint::CIRC, sfAnimatedPoint::EASE_IN_OUT, _hideAnimationDuration );
	_rotationAnimator.start();
	_alphaAnimator.setTarget( 0, 0, 0 );
	_alphaAnimator.setAnimation( sfAnimatedPoint::LINEAR, sfAnimatedPoint::EASE_OUT, 2 * (_hideAnimationDuration / 3) );
	_alphaAnimator.start();
	_hidden = true;
}

bool sfJuniperPoint::isHidden()
{
	if( _hidden == true && !_rotationAnimator.isAnimating() && !_alphaAnimator.isAnimating() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void sfJuniperPoint::update()
{
	_colorAnimator.update();
	_rotationAnimator.update();
	_alphaAnimator.update();
	_locationAnimator.update();
}

void sfJuniperPoint::draw()
{
	glPushMatrix();

	glRotatef( _rotationAnimator.x, 0.0, 0.0, 1.0 );
	glTranslatef( _xOffset, _yOffset, _locationAnimator.z );
	glRotatef( _subRotation, 0, 0, 1 );

	sfDrawingUtil vUtil;
	int vC = vUtil.blendHex( _deactivatedColor, _activatedColor, _colorAnimator.x );
	float vR = (float)vUtil.getHexRedValue( vC ) / 255.0;
	float vG = (float)vUtil.getHexGreenValue( vC ) / 255.0;
	float vB = (float)vUtil.getHexBlueValue( vC ) / 255.0;

//	if( _alphaAnimator.x == 1 )
//	{
//		glDisable( GL_BLEND );
//	}
	glColor4f( vR, vG, vB, _alphaAnimator.x );
//	glEnable( GL_BLEND );

	_renderer.draw();

	glPopMatrix();
}
