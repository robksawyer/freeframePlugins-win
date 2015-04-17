/*
 * sfSpiderPointsPoint.h
 *
 *  Created on: Dec 27, 2010
 *      Author: marc.wren
 */

#ifndef SFSPIDERPOINTSPOINT_H_
#define SFSPIDERPOINTSPOINT_H_

#include "sfAnimatedPoint.h"

/**
 * An animated point that can be told to hide (ie. animate back to
 * it's starting position). The point can then be queried to determine
 * if it has hidden itself.
 */
class sfSpiderPointsPoint: public sfAnimatedPoint
{
	public:
		sfSpiderPointsPoint();
		/**
		 * Hide the point (ie. animate it back into it's starting position).
		 */
		void hide();
		/**
		 * Hide the point into the location specified.
		 */
		void hide( float x, float y, float z );
		/**
		 * If the point is currently hiding itself, stop the hiding process.
		 */
		void unhide();
		/**
		 * True = the point has hidden itself.
		 */
		bool isHidden();
		/**
		 * True = the point is in the process of hiding itself.
		 */
		bool isHiding();
	private:
		/**
		 * The original location of the point.
		 */
		ofxVec3f _origin;
		/**
		 * True = The point is in the process of hiding.
		 */
		bool _isHiding;
		/**
		 * True = The point has finished hiding.
		 */
		bool _isHidden;
};

#endif /* SFSPIDERPOINTSPOINT_H_ */
