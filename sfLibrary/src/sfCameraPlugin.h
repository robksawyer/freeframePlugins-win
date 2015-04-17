/*
 * sfCameraPlugin.h
 * Defines the interface required by all sfCameraPlugins.
 *
 *  Created on: Nov 9, 2010
 *      Author: marc.wren
 */

#ifndef SFCAMERAPLUGIN_H_
#define SFCAMERAPLUGIN_H_

#include "ofxVec3f.h"

class sfCameraPlugin
{
    public:
		/**
		 * Update the current camera plugin.
		 */
        virtual void update();
		/**
		 * Set the current location of the camera. This is where the camera is
		 * supposed to be positioned, not where this plugin will actually position
		 * the camera.
		 */
		void setCurrentCameraLocation( ofxVec3f camera );
		/**
		 * Get camera position that this plugin wants the camera to be placed at.
		 */
		ofxVec3f getDesiredCamera();
		/**
		 * Set the current focal point of the camera. This is where the camera is
		 * supposed to be looking, not where this plugin will make the camera look.
		 */
		void setCurrentFocalPoint( ofxVec3f center );
		/**
		 * Get the focal point that the camera wishes to be pointed at.
		 */
		ofxVec3f getDesiredFocalPoint();
    protected:
		/**
		 * The location that the camera is supposed to be placed at.
		 */
		ofxVec3f _actualCamera;
		/**
		 * The point that the camera is supposed to be looking at.
		 */
		ofxVec3f _actualFocalPoint;
		/**
		 * The location that this plugin wants the camera to point.
		 */
		ofxVec3f _desiredCamera;
		/**
		 * The location that this plugin wants the camera's focal point to be.
		 */
		ofxVec3f _desiredFocalPoint;
		/**
		 * The actual camera from the last time it was updated.
		 */
		ofxVec3f _lastActualCamera;
		/**
		 * The actual focal point from the last time it was updated.
		 */
		ofxVec3f _lastActualFocalPoint;
		/**
		 * The desired camera from the last time it was updated.
		 */
		ofxVec3f _lastDesiredCamera;
		/**
		 * The desired focal point from the last time it was updated.
		 */
		ofxVec3f _lastDesiredFocalPoint;
};

#endif /* SFCAMERAPLUGIN_H_ */
