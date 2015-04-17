/*
 * sfCameraShake.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#ifndef SFCAMERASHAKE_H_
#define SFCAMERASHAKE_H_

#include "sfCameraPlugin.h"
#include "ofxVec3f.h"
#include "sfAnimatedPoint.h"

class sfCameraShake: public sfCameraPlugin
{
	public:
		sfCameraShake();
		/**
		 * Shake the camera.
		 */
		void shake();
		/**
		 * Set how long shake events will last for.
		 */
		void setShakeDuration( float duration );
		/**
		 * Set how far the target will move when shaking.
		 */
		void setMaxShakeWidth( float width );
		/**
		 * Update the current location of the camera.
		 */
		void update();
		/**
		 * Set the current focal point of the camera. This is where the camera is
		 * supposed to be looking, not where this plugin will make the camera look.
		 */
		void setCurrentFocalPoint( ofxVec3f center );
		/**
		 * Set the current location of the camera. This is where the camera is
		 * supposed to be positioned, not where this plugin will actually position
		 * the camera.
		 */
		void setCurrentCameraLocation( ofxVec3f camera );
	private:
		/**
		 * A countdown to 0 during which time the camera will shake.
		 */
		int _shakeCountdown;
		/**
		 * The amount of time the camera will shake for.
		 */
		int _shakeDuration;
		/**
		 * The maximum amount that the camera will move along any
		 * axis during a shake.
		 */
		float _maxShakeWidth;
		/**
		 * The object used to track shaking of the camera.
		 */
		sfAnimatedPoint _cameraShaker;
		/**
		 * The object used to track shaking of the camera focal point.
		 */
		sfAnimatedPoint _focalPointShaker;
};

#endif /* SFCAMERASHAKE_H_ */
