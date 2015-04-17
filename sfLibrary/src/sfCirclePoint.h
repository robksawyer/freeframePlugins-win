/*
 * sfCirclePoint.h
 *
 * Draws a point where the non-point end is rounded. You
 * could also describe the shape as a circle with a point
 * extruding from it.
 *
 *  Created on: Aug 25, 2010
 *      Author: marc.wren
 */

#ifndef SFCIRCLEPOINT_H_
#define SFCIRCLEPOINT_H_

#include "glee.h"
#include "sfOpenGL.h"
//#include "glu.h"
//#include <OpenGL/glu.h>

class sfCirclePoint
{
	public:
		/**
		 * Instanciate a circle point object of default size.
		 */
		sfCirclePoint();
		/**
		 * Construct a circle point of the specified size.
		 * @param width The width of the shape.
		 * @param height The height of the shape.
		 */
		sfCirclePoint( float width, float height );
		/**
		 * Draw the shape to the screen.
		 */
		void draw();
		/**
		 * The number of slices to draw in the arc portion of the shape.
		 */
		int slices;

	private:
		/**
		 * The pointer to the quadric that will be used to render
		 * circles.
		 */
		GLUquadric* _quadric;
		/**
		 * The width of the point.
		 */
		float _width;
		/**
		 * The height of the point.
		 */
		float _height;
		/**
		 * The offset from the center of the star to the middle
		 * of the polygon used when drawing the star.
		 *
		 * In more detail, the point is drawn using part of a circle to
		 * describe the top of the point and a diamond polygon to
		 * describe the angular portion. In the following
		 * diagram, the polygonXOffset is the location on the x axis
		 * of the points marked with an "X". A circle is then drawn
		 * undernieth this shape to complete the point.
		 *
		 *       .*.
		 *   X*     *X
		 *     *.   .*
		 *       *.*
		 */
		float _polygonXOffset;
		/**
		 * The y component of the polygon described above.
		 */
		float _polygonYOffset;
		/**
		 * The location at which the disk portion of the point
		 * will start drawing.
		 */
		float _diskStart;
		/**
		 * The number of degrees that the disk portion of the
		 * point will last.
		 */
		float _diskSweep;
		/**
		 * Initialize the shape.
		 * @param width The width of the shape.
		 * @param height The height of the shape.
		 */
		void _init( float width, float height );
		/**
		 * Performs the necessary calculations to be able to draw the shape.
		 * @param width The width of the shape.
		 * @param height The height of the shape.
		 */
		void _calculateShape( float width, float height );
};

#endif /* SFCIRCLEPOINT_H_ */
