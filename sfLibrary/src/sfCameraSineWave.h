/*
 * sfCameraSineWave.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#ifndef SFCAMERASINEWAVE_H_
#define SFCAMERASINEWAVE_H_

#include "sfCameraPlugin.h"
#include "ofxVec3f.h"
#include "sfAnimatedPoint.h"

class sfCameraSineWave: public sfCameraPlugin
{
	public:
		sfCameraSineWave();
		/**
		 * Shake the camera.
		 */
		void shake();
		/**
		 * Set how long shake events will last for.
		 */
		void setShakeDuration( float duration );
		/**
		 * The number of degrees along the sine wave path to move
		 * each update cycle.
		 */
		void setWaveSpeed( float speed );
		/**
		 * Set the minimum amount of the sine wave when not shaking.
		 */
		void setMinWaveWidth( float width );
		/**
		 * Set how far the target will move when shaking.
		 */
		void setMaxWaveWidth( float width );
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
		 * The number of degrees along the sine wave path that we have traveled.
		 */
		float _rotation;
		/**
		 * The number of degrees we move along the sine wave path with each update.
		 */
		float _rotationSpeed;
		/**
		 * A countdown to 0 during which time the camera will shake.
		 */
		int _shakeCountdown;
		/**
		 * The amount of time the camera will shake for.
		 */
		int _shakeDuration;
		/**
		 * The minimum amount that the camera will move along any
		 * axis when it is not actively shaking.
		 */
		float _minWaveWidth;
		/**
		 * The maximum amount that the camera will move along any
		 * axis during a shake.
		 */
		float _maxWaveWidth;
};

#endif /* SFCAMERASINEWAVE_H_ */
