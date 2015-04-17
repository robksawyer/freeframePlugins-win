/*
 * sfCirclePoint.cpp
 *
 *  Created on: Aug 25, 2010
 *      Author: marc.wren
 */

#include "sfCirclePoint.h"
#include <math.h>
#include "glee.h"
#include "sfOpenGL.h"
#include "ofMain.h"

sfCirclePoint::sfCirclePoint()
{
	_init( 100, 200 );
}

sfCirclePoint::sfCirclePoint( float vW, float vH )
{
	_init( vW, vH );
}

void sfCirclePoint::_init( float vW, float vH )
{
	// We always want to draw at least a circle.
	if( vH < vW )
	{
		vH = vW;
	}

	slices = 50;
	_width = vW;
	_height = vH;
	_quadric = gluNewQuadric();
	_calculateShape( vW, vH );
}

void sfCirclePoint::_calculateShape( float vW, float vH )
{
	float vRadius = vW/2;

	// Quarter Angle in Radians (ie. 90 degrees)
	float vQAR = 90 * PI / 180;

	// Degrees around the circle that we will extend past the halfway point of our circle.
	// http://en.wikipedia.org/wiki/Tangent_lines_to_circles
	float vRadians = vQAR - acos( vRadius / ( vH - vRadius ) );
	float vDeg = vRadians * 180 / PI;

	// The y offset from the circle's center that we must draw our polygon.
	_polygonYOffset = vRadius * sin( vRadians );
	_polygonXOffset = vRadius * cos( vRadians );
	_diskStart = -90 - vDeg;
	_diskSweep = 180 + (vDeg * 2);
}

void sfCirclePoint::draw()
{
	float vRadius = _width / 2;

	// If the _width and _height are equal, draw a circle.
	if( _height <= _width )
	{
		gluDisk( _quadric, 0, vRadius, slices, 1 );
	}
	else
	{
		// Draw the circular part.
		gluPartialDisk( _quadric, 0, vRadius, slices, 1, _diskStart, _diskSweep );

		// Draw the point.
		glBegin( GL_POLYGON );
		glVertex3f( 0, 0, 0 );
		glVertex3f( _polygonXOffset, -_polygonYOffset, 0 );
		glVertex3f( 0, -(_height - vRadius), 0 );
		glVertex3f( -_polygonXOffset, -_polygonYOffset, 0 );
		glEnd();
	}
}
