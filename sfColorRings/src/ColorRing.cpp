/*
 *  ColorRing.cpp
 *  polygonExample
 *
 *  Created by Marc Wren  on 6/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ColorRing.h"
#include "SpinningRing.h"
#include "sfDrawingUtil.h"
#include <list>
//#include <exception>

ColorRing::ColorRing()
{
	_initialized = false;
}

void ColorRing::setup( int vWindowW, int vWindowH )
{
	// Setup class properties.
	_initialized = true;
	_numberOfRings = 10;
	_vibrationAmount = 0;
	_innerDiameter = 150;
	_outerDiameter = 200;
	_offsetFactor = 1;
	_rotationSpeed = 10;
	_ringCenterX = vWindowW / 2;
	_ringCenterY = vWindowH / 2;
	float vOffsetRange = 2;
	
	// Get the list of colors for each ring.
	sfDrawingUtil vUtil;
	vector<int> vColors = vUtil.colorWheel( _numberOfRings );
	
	// Create the list of rings.
	for( int i = 0; i < _numberOfRings; i++ )
	{
		SpinningRing vRing( _ringCenterX, _ringCenterY, 0, _outerDiameter, _innerDiameter, vColors.at(i) );
		vRing.setOffsetFactor( _offsetFactor );
		vRing.setXOffset( ofRandom( -vOffsetRange, vOffsetRange ) );
		vRing.setYOffset( ofRandom( -vOffsetRange, vOffsetRange ) );
		vRing.setZRotationSpeed( ofRandom( -_rotationSpeed, _rotationSpeed ) );
		_rings.push_front( vRing );
	}
}

void ColorRing::update()
{
	if( _initialized == false )
	{
		//throw exception;
	}
	
	for( list<SpinningRing>::iterator vIterator = _rings.begin(); vIterator != _rings.end(); ++vIterator )
	{
		// Add vibration.
		vIterator->setX( _ringCenterX + ofRandom( -_vibrationAmount, _vibrationAmount ) );
		vIterator->setY( _ringCenterY + ofRandom( -_vibrationAmount, _vibrationAmount ) );
		
		// Update the offsetFactor.
		vIterator->setOffsetFactor( _offsetFactor );
		
		// Update the inner and outer diameters of the ring.
		vIterator->setInnerDiameter( _innerDiameter );
		vIterator->setOuterDiameter( _outerDiameter );
		
		// Spin the ring.
		vIterator->update();
	}
}

void ColorRing::draw()
{
	if( _initialized == false )
	{
		//throw exception;
	}
	
	// Enable blending mode.
	ofEnableAlphaBlending();
	glBlendFunc(GL_SRC_COLOR, GL_ONE);
	
	// Draw each of our rings.
	for( list<SpinningRing>::iterator vIterator = _rings.begin(); vIterator != _rings.end(); ++vIterator )
	{
		// Draw the current SpinningRing.
		vIterator->draw();
	}
	
	// Set the GL state back to its original state.
	ofDisableAlphaBlending();
}

void ColorRing::setVibrationAmount( float vVibration )
{
	_vibrationAmount = vVibration;
}

void ColorRing::setInnerDiameter( float vDiameter )
{
	_innerDiameter = vDiameter;
}

void ColorRing::setOuterDiameter( float vDiameter )
{
	_outerDiameter = vDiameter;
}

void ColorRing::setOffsetFactor( float vOffset )
{
	_offsetFactor = vOffset;
}
