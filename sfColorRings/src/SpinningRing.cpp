/*
 *  SpinningRing.cpp
 *  polygonExample
 *
 *  Created by Marc Wren  on 5/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SpinningRing.h"
#include "sfDrawingUtil.h"
#include "ofMain.h"

SpinningRing::SpinningRing()
{
	_init( 0, 0, 0, 100, 50, 0xff0000, 0, 0, 0, 0, 0 );
}

SpinningRing::SpinningRing( int vX, int vY, int vZ, int vOD, int vID, int vC )
{
	_init( vX, vY, vZ, vOD, vID, vC, 0, 0, 0, 0, ofRandom( 0, 360 ) );
}

SpinningRing::SpinningRing( int vX, int vY, int vZ, int vOD, int vID, int vC, int vOffX, int vOffY )
{
	_init( vX, vY, vZ, vOD, vOD, vC, vOffX, vOffY, 0, 0, ofRandom( 0, 360 ) );
}

void SpinningRing::_init( int vX, int vY, int vZ, int vOD, int vID, int vC, int vOffX, int vOffY, int vXR, int vYR, int vZR )
{
	setX( vX );
	setY( vY );
	setZ( vZ );
	setColor( vC );
	setOffsetFactor( 1 );
	// Make this a variable that can be set from the host app.
	_alpha = 150; // 0 - 255
	setOuterDiameter( vOD );
	setInnerDiameter( vID );
	setXOffset( vOffX );
	setYOffset( vOffY );
	setXRotation( vXR );
	setYRotation( vYR );
	setZRotation( vZR );
	setZRotationSpeed( 5 );
}

void SpinningRing::draw()
{
	// Store the current location in order to reset it later.
	ofPushMatrix();
	
	// Set drawing settings.
	ofSetColor( _r, _g, _b, _alpha );
	ofFill();
	
	// Move to the location of the ring.
	ofTranslate( _x, _y, _z );
	ofRotateZ( _zRotation );
	
	// Draw the ring.
	sfDrawingUtil vUtil;
	vUtil.drawRing( _offsetX * _offsetFactor, _offsetY * _offsetFactor, _outerDiameter, _innerDiameter );
	
	// Reset drawing head to its original state.
	ofPopMatrix();
}

void SpinningRing::update()
{
	setZRotation( _zRotation + _zRotationSpeed );
}

void SpinningRing::setX( int vX )
{
	_x = vX;
}

int SpinningRing::getX()
{
	return _x;
}

void SpinningRing::setY( int vY )
{
	_y = vY;
}

int SpinningRing::getY()
{
	return _y;
}

void SpinningRing::setZ( int vZ )
{
	_z = vZ;
}

int SpinningRing::getZ()
{
	return _z;
}

void SpinningRing::setXOffset( int vXOff )
{
	_offsetX = vXOff;
}

void SpinningRing::setYOffset( int vYOff )
{
	_offsetY = vYOff;
}

void SpinningRing::setOffsetFactor( int vFactor )
{
	_offsetFactor = vFactor;
}

void SpinningRing::setInnerDiameter( int vD )
{
	_innerDiameter = vD;
}

void SpinningRing::setOuterDiameter( int vD )
{
	_outerDiameter = vD;
}

void SpinningRing::setColor( int vC )
{
	_color = vC;
	sfDrawingUtil vUtil;
	_r = vUtil.getHexRedValue( vC );
	_g = vUtil.getHexGreenValue( vC );
	_b = vUtil.getHexBlueValue( vC );
}

void SpinningRing::setXRotation( int vR )
{
	// Make sure the new rotation is within bounds.
	vR = _constrainRotation( vR );
	_xRotation = vR;
}

void SpinningRing::setYRotation( int vR )
{
	// Make sure the new rotation is within bounds.
	vR = _constrainRotation( vR );
	_yRotation = vR;
}

void SpinningRing::setZRotation( int vR )
{
	// Make sure the new rotation is within bounds.
	vR = _constrainRotation( vR );
	_zRotation = vR;
}

int SpinningRing::_constrainRotation( int vR )
{
	if( vR < 0 )
	{
		int vRemainder = vR % 360;
		vR = 360 + vRemainder;
	}
	else if ( vR > 360 )
	{
		int vRemainder = vR % 360;
		vR = 0 + vRemainder;
	}
	return vR;
}

void SpinningRing::setZRotationSpeed( int vZRS )
{
	_zRotationSpeed = vZRS;
}
