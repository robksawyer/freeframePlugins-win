/*
 * Helpful math functions.
 *
 *  Created on: Jul 19, 2010
 *      Author: marcwren
 */

#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include "ofxVec3f.h"

class sfMathUtils
{
	public:
		sfMathUtils();
		static int LAST_POSITIVE_OR_NEGATIVE_HALF_ROUND;
		/**
		 * Returns either 1 or -1.
		 */
		int positiveOrNegative();
		/**
		 * Normal rounding.
		 */
		float round( float value );
		/**
		 * Get a random point within a sphere.
		 * @param outerRadius The outer radius of the sphere.
		 * @param innerRadius An inner radius within which points won't
		 * be created. This allows you to make sure you get points at least
		 * innerRadius from the sphere's center.
		 */
		ofxVec3f randomPointWithinSphere( float outerRadius, float innerRadius );
		/**
		 * Get a random point within a sphere.
		 * @param radius The radius of the sphere.
		 */
		ofxVec3f randomPointWithinSphere( float radius );
};

#endif /* MATHUTILS_H_ */
