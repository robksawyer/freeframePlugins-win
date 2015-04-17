/*
 * sfCameraMovements.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#ifndef SFCAMERAGLITCH_H_
#define SFCAMERAGLITCH_H_

#include "sfCameraPlugin.h"
#include "ofxVec3f.h"

// TODO Could I apply these as traits/plugins on sfCamera rather than extending it?
class sfCameraGlitch: public sfCameraPlugin
{
	public:
		sfCameraGlitch();
		/**
		 * Glitch the camera.
		 */
		void glitch();
		/**
		 * Set how long glitch events will last for.
		 */
		void setGlitchDuration( float duration );
		/**
		 * Set how far the target will move when glitching.
		 */
		void setMaxGlitchWidth( float width );
		/**
		 * Update the current location of the camera.
		 */
		void update();
	private:
		/**
		 * A countdown to 0 during which time the camera will glitch.
		 */
		int _glitchCountdown;
		/**
		 * The amount of time the camera will glitch for.
		 */
		int _glitchDuration;
		/**
		 * The maximum amount that the camera will move along any
		 * axis during a glitch.
		 */
		float _maxGlitchWidth;
};

#endif /* SFCAMERAGLITCH_H_ */
