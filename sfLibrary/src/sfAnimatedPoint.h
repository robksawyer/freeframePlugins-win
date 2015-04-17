/*
 * sfAnimatedPoint.h
 *
 * A point that can track its own motion.
 *
 *  Created on: Jul 20, 2010
 *      Author: marcwren
 */

#ifndef SFANIMATEDPOINT_H_
#define SFANIMATEDPOINT_H_

#include "ofxVec3f.h"

class sfAnimatedPoint: public ofxVec3f
{
	public:
		/**
		 * The different easing animations that can be used.
		 */
		static const int BASIC = 0;
		static const int LINEAR = 1;
		static const int QUAD = 2;
		static const int QUART = 3;
		static const int QUINT = 4;
		static const int SINE = 5;
		static const int EXPO = 6;
		static const int ELASTIC = 7;
		static const int CUBIC = 8;
		static const int CIRC = 9;
		static const int BOUNCE = 10;
		static const int BACK = 11;
		/**
		 * The direction of the easing.
		 */
		static const int EASE_IN = 201;
		static const int EASE_OUT = 202;
		static const int EASE_IN_OUT = 203;
		/**
		 * Initialize the point to 0, 0, 0.
		 */
		sfAnimatedPoint();
		/**
		 * Set the initial location of the point.
		 */
		sfAnimatedPoint( float x, float y, float z );
		/**
		 * Set the initial location of the point and the factor
		 * by which it will ease into position.
		 */
		sfAnimatedPoint( float x, float y, float z, float factor );
		/**
		 * The distance on the x axis that the point will animate.
		 */
		float targetX;
		/**
		 * The distance on the y axis that the point will animate.
		 */
		float targetY;
		/**
		 * The distance on the z axis that the point will animate.
		 */
		float targetZ;
		/**
		 * The amount by which points will be moved towards their target.
		 */
		float factor;
		/**
		 * Set the animation style to use.
		 * @param type The animation name. This should be one of the
		 * constant animation types defined by this class (for example
		 * AnimatedPoint::QUAD).
		 * @param direction The direction of easing. This should be one
		 * of the constant animation directions (ex. AnimatedPoint::EASE_IN).
		 * @param duration The duration of the animation in frames.
		 */
		void setAnimation( int type, int direction, int duration );
		/**
		 * Set the type of animation. This should be one of the animation
		 * constants (ex. sfAnimatedPoint::QUAD).
		 */
		void setAnimationType( int type );
		/**
		 * Set the direction of animation (ie. in, out, etc.). This should be one
		 * of the animation direction constants (ex. sfAnimatedPoint::EASE_IN).
		 */
		void setAnimationDirection( int direction );
		/**
		 * Set the amount of time that the animation will last.
		 */
		void setAnimationDuration( int duration );
		/**
		 * Set targetX, targetY and targetZ properties at once.
		 */
		void setTarget( float x, float y, float z );
		/**
		 * Set the target x, y, and z using a vector.
		 */
		void setTarget( ofxVec3f target );
		/**
		 * Start the animation cycle.
		 */
		void start();
		/**
		 * Pause the animation cycle.
		 */
		void pause();
		/**
		 * Update the point's current location.
		 */
		void update();
		/**
		 * True = The point is currently animating.
		 */
		bool isAnimating();
	protected:
		/**
		 * True = Animation is currently under way.
		 */
		bool _animating;
		/**
		 * The current number of frames that the animation has lasted.
		 */
		int _animationTime;
		/**
		 * The starting X location of the animation.
		 */
		float _originX;
		/**
		 * The starting Y location of the animation.
		 */
		float _originY;
		/**
		 * The starting Z location of the animation.
		 */
		float _originZ;
		/**
		 * The type of animation being done. This should be one
		 * of the static animation types defined by this class.
		 */
		int _animationType;
		/**
		 * The direction of the easing in the animation. This should
		 * be one of the static animation easing types defined by this class.
		 */
		int _animationEasing;
		/**
		 * The duration of animation.
		 */
		int _animationDuration;
		/**
		 * Initialize the properties of this point.
		 */
		void _init( float x, float y, float z, float factor );
};

#endif /* SFANIMATEDPOINT_H_ */
