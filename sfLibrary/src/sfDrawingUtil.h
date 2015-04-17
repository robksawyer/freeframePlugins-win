/*
 * sfDrawingUtil.h
 * A collection of utility functions to aid in drawing with OpenGL.
 *
 *  Created on: Aug 23, 2010
 *      Author: marc.wren
 */

#ifndef SFDRAWINGUTIL_H_
#define SFDRAWINGUTIL_H_

#include "ofMain.h"
#include "ofxVec3f.h"

class sfDrawingUtil
{
	public:
		/**
		 * Draw a ring to the screen. This will use the current fill and color settings
		 * so you need to set those before calling this function.
		 * @param vX The x location of the center of the ring.
		 * @param vY The y location of the center of the ring.
		 * @param vOR The outer radius of the ring.
		 * @param vIR The inner radius of the ring.
		 */
		void drawRing( int x, int y, float outerRadius, float innerRadius );
		/**
		 * Depricated. Use gluDisk instead.
		 * Make the vertex calls that will define a circle shape. The shape is
		 * not actually drawn to the screen but the vertex calls to define the shape
		 * are made. This allows you to either begin and end the shape before and after
		 * calling this method, or to use the circle call as part of a more complex
		 * shape.
		 * @param x The x location of the circle's center.
		 * @param y The y location of the circle's center.
		 * @param radius The radius of the circle.
		 */
		void circleVerticies( int x, int y, float radius );
		/**
		 * Convert RGB values into a single Hex color value.
		 * @param red The red portion of the color.
		 * @param green The green portion of the color.
		 * @param blue The blue portion of the color.
		 */
		int rgbToHex( int red, int green, int blue );
		/**
		 * Get the red value out of a hex number.
		 * @param hex The hex number from which to retrieve the red portion.
		 */
		int getHexRedValue( int hex );
		/**
		 * Get the green value out of a hex number.
		 * @param hex The hex number from which to retrieve the red portion.
		 */
		int getHexGreenValue( int hex );
		/**
		 * Get the blue value out of a hex number.
		 * @param hex The hex number from which to retrieve the red portion.
		 */
		int getHexBlueValue( int hex );
		/**
		 * Blend between two Hex colors.
		 * @param color1 The begining hex value.
		 * @param color2 The ending hex value.
		 * @param amount The amount to blend by (0 - 1).
		 * 		0 = Use the begining hex value.
		 * 		0.5 = Blend the two hex values equally.
		 * 		1 = Use the ending hex value.
		 * @return The outcome hex value.
		 */
		int blendHex( int color1, int color2, float amount );
		/**
		 * Create an array of hex colors where each point is on the color spectrum between
		 * red and red. In other words, this function will divide the color spectrum
		 * into the number of parts specified and return a list of those colors.
		 * Code from: http://www.boostworthy.com/blog/?p=200
		 * @param points The number of points to divide the color spectrum into.
		 * @return A list of the colors as hex values on the color spectrum.
		 */
		vector<int> colorWheel( int points );
		void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric);
		void renderCylinder( ofxVec3f start, ofxVec3f end, float radius, int subdivisions, GLUquadricObj *quadric );
//		void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions);
};

#endif /* SFDRAWINGUTIL_H_ */
