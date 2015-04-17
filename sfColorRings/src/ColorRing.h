/*
 *  ColorRing.h
 *	This class creates a list of spinning rings that can vibrate.
 *
 *  Created by Marc Wren  on 6/25/10.
 *  Copyright 2010 Soul Fresh. All rights reserved.
 *
 */

#include "ofMain.h"
#include "SpinningRing.h"

#ifndef _SF_COLOR_RING
#define _SF_COLOR_RING

class ColorRing 
{
public:
	ColorRing();
	
	/**
	 * Setup the initial state of this class (intended to be
	 * called in the setup of your application and before using
	 * this class).
	 * @param windowWidth The width of the display window.
	 * @param windowHeight The height of the display window.
	 */
	void setup( int windowWidth, int windowHeight );
	/**
	 * Update the current state of this class (intended to 
	 * be called every frame).
	 */
	void update();
	/**
	 * Draw the current state of this class (intended to be called
	 * every frame after a call to update).
	 */
	void draw();
	/**
	 * The amount of vibration to add to the loop.
	 */
	void setVibrationAmount( float vibration );
	/**
	 * Set the inner diameter of the loop.
	 */
	void setInnerDiameter( float innerDiameter );
	/**
	 * Set the outer diameter of the loop.
	 */
	void setOuterDiameter( float outerDiameter );
	/**
	 * Set the factor by which rings will be offset from each other.
	 */
	void setOffsetFactor( float offset );
	
private:
	/**
	 * Whether or not the setup method has been called.
	 */
	Boolean _initialized;
	/**
	 * The list of ring objects being displayed.
	 */
	list<SpinningRing> _rings;
	/**
	 * The center x location of the rings.
	 */
	int _ringCenterX;
	/**
	 * The center y location of the rings.
	 */
	int _ringCenterY;
	/**
	 * The number of rings being displayed.
	 */
	int _numberOfRings;
	/**
	 * The amount of vibration (in pixels) added to all rings. 
	 * 0 means that the rings do not vibrate. 10 means that
	 * each ring will be moved by up to 10 pixels with each
	 * update event.
	 */
	int _vibrationAmount;
	/**
	 * The amount that each ring can be offset from it's
	 * center. For example, setting this to 10 means that
	 * the ring will be offset somewhere between -10 and +10
	 * pixels from it's center. The actual offset will be 
	 * randomized so that each ring has a different final
	 * offset amount.
	 */
	int _offsetFactor;
	/**
	 * The inner diameter of our rings.
	 */
	int _innerDiameter;
	/**
	 * The outer diameter of our rings.
	 */
	int _outerDiameter;
	/**
	 * The speed factor at which each ring rotates.
	 */
	int _rotationSpeed;
};

#endif
	