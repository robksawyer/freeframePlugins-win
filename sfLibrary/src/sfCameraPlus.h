/*
 * sfCameraPlus.h
 *
 *  Created on: Nov 9, 2010
 *      Author: marc.wren
 */

#ifndef SFCAMERAPLUS_H_
#define SFCAMERAPLUS_H_

#include "sfCamera.h"
#include "sfCameraPlugin.h"

class sfCameraPlus: public sfCamera
{
	public:
		sfCameraPlus();
		/**
		 * Add a plugin to the camera that can change what the camera sees.
		 */
		void addPlugin( sfCameraPlugin* plugin );
		/**
		 * Update the camera and any of its plugins.
		 */
		void update();
		/**
		 * Override the place method of sfCamera so we can utilize
		 * the _actual* properties to place the camera.
		 */
		virtual void place();
	protected:
		/**
		 * True = There are currently plugins registered with this camera.
		 */
		Boolean _hasPlugins;
		/**
		 * The list of plugins used in this project.
		 */
		vector<sfCameraPlugin*> _plugins;
		/**
		 * The location vector used to place the camera.
		 * cameraCoord is the desired camera position and this
		 * property is the actual position.
		 */
		ofxVec3f _actualCameraCoord;
		/**
		 * The location vector used as the camera's focal point.
		 * focalPointCoord is the desired camera focal point and
		 * this property is the actual focal point.
		 */
		ofxVec3f _actualFocalPointCoord;
};

#endif /* SFCAMERAPLUS_H_ */
