/*
 * SpiderPoints.h
 * Draws a list of points (around a center point) and animates the location of those
 * points every time a beat event occurs.
 *
 *  Created on: Jul 14, 2010
 *      Author: marcwren
 */

#ifndef SPIDERPOINTS_H_
#define SPIDERPOINTS_H_

#include "ofMain.h"
#include "sfAnimatedPoint.h"
#include "sfSpiderPointsPoint.h"
#include "sfLoopTracker.h"

class sfSpiderPoints
{
	public:
		sfSpiderPoints();
		~sfSpiderPoints();

		/**
		 * Initial setup of object.
		 */
		void setup();
		/**
		 * Update the current state of the object.
		 */
		void update();
		/**
		 * Draw the object to the screen.
		 */
		void draw();
		/**
		 * Set the size of the window in which the spider points will be displayed.
		 * This will recenter the animation and reset the radius to fit within the window size.
		 *
		 * @param width The width of the window.
		 * @param height The height of the window.
		 */
		void setWindowSize( int width, int height );
		/**
		 * Handle a beat event. This will make all of the points scatter.
		 */
		void movePoints();
		/**
		 * Set the inner radius of the points.
		 * @param The new radius.
		 */
		void setOuterRadius( int innerRadius );
		/**
		 * Set the outer radius of the points.
		 * @param The new radius.
		 */
		void setInnerRadius( int outerRadius );
		/**
		 * Set the location of the SpiderPoints center.
		 */
		void setLocation( float x, float y, float z );
		/**
		 * Rotate the SpiderPoints object a random amount and direction.
		 */
		void rotate();
		/**
		 * Set the rotation to a specific rotation value.
		 */
		void rotate( float x, float y, float z );
		/**
		 * The the duration of the rotation aspect of the animation.
		 */
		void setAutoRotateDuration( int duration );
		/**
		 * Set the amount of time it takes points to animate into their positions.
		 */
		void setPointSpeed( int duration );
		/**
		 * Set the number of points in a SpiderPoints object.
		 */
		void setNumberOfPoints( unsigned int total );
		/**
		 * Add the number of points specified to the SpiderPoints object.
		 */
		void addPoints( unsigned int total );
		/**
		 * Remove the number of points specified from the SpiderPoints object.
		 */
		void removePoints( unsigned int total );
		/**
		 * Set the type of animation easing used when animating points. Must be
		 * one of the sfAnimatedPoint::EASE_* values.
		 */
		void setPointAnimationEaseDirection( int type );
		/**
		 * When moving points, set how many frames pass between each point starting
		 * to move to its new location.
		 * @param frames The number of frames between point movements.
		 */
		void setPointStaggerDuration( int frames );
		/**
		 * Set the type of animation easing used when animating rotation. Must be
		 * one of the sfAnimatedPoint::EASE_* values.
		 */
		void setRotationEaseDirection( int type );
		/**
		 * Make the spider points object colored or white.
		 * @param colors True = colore the object.
		 */
		void useColors( bool colors );

	private:
		/**
		 * True = The setup method has been called and the initial set of points have
		 * been created.
		 */
		bool _initialized;
		/**
		 * The object used to stagger the movement of points.
		 */
		sfLoopTracker _pointStagger;
		/**
		 * The number of frames that point movements are staggered.
		 */
		int _pointStaggerDuration;
		/**
		 * The x center point around which the points will animate.
		 */
		int _x;
		/**
		 * The y center point around which the points will animate.
		 */
		int _y;
		/**
		 * The z center point around which the points will animate.
		 */
		int _z;
		/**
		 * The current rotation amount around all axises.
		 */
		sfAnimatedPoint _rotation;
		/**
		 * The duration that the rotation aspect of the animation will last.
		 */
		int _rotationDuration;
		/**
		 * The amount of time it takes points to move into their new locations.
		 */
		int _pointAnimationDuration;
		/**
		 * The direction of easing for point movements. This must be one of the
		 * sfAnimatedPoint::EASE_* values.
		 */
		int _pointAnimationEasing;
		/**
		 * The type of animation used to move the points to their new locations.
		 */
		int _pointAnimationType;
		/**
		 * The type of animation used for rotation.
		 */
		int _rotationType;
		/**
		 * The easing direction of the rotation animation.
		 */
		int _rotationEasing;
		/**
		 * The radius from the center inside of which points will not land.
		 */
		int _innerRadius;
		/**
		 * The radius from the center inside of which points will land.
		 */
		int _outerRadius;
		/**
		 * The number of points to draw to the screen (including points that are currently
		 * hiding themselves).
		 */
//		unsigned int _numberOfPoints;
		/**
		 * The number of points that are NOT hiding themselves. Think of this as the desired
		 * number of points.
		 */
		unsigned int _numberOfActivePoints;
		/**
		 * The list of point objects.
		 */
		vector<sfSpiderPointsPoint*> _points;
		/**
		 * Whether or not the points are drawn in 3 dimensions.
		 */
		bool _is3D;
		/**
		 * True = color the shape. False = make the shape white.
		 */
		bool _useColors;
		/**
		 * Randomly pick a value within the SpiderPoint's area (ie. this can be used
		 * as the x, y, or z value of a point and will lie within the innerRadius and
		 * outerRadius of this instance).
		 * @param root The root location from which this value will be picked (ie. pass
		 * this object's _x, _y, or _z value).
		 * @return An integer that is within range for use as the x, y, or z value of a
		 * point.
		 */
		int _newPointLocation( int root );
		/**
		 * Setup the initial state of a new point.
		 */
		void _setupPoint( sfSpiderPointsPoint* point );
		/**
		 * Remove any points that have been completely hidden.
		 */
		void _removeOldPoints();
		/**
		 * Set points that are currently hiding to unhidden states.
		 * @param total The number of points to unhide.
		 */
		void _unhidePoints( unsigned int total );
};

#endif /* SPIDERPOINTS_H_ */
