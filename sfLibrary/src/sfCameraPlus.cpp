/*
 * sfCameraPlus.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: marc.wren
 */

#include "sfCameraPlus.h"

sfCameraPlus::sfCameraPlus()
{
	_hasPlugins = false;
}


void sfCameraPlus::place()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	gluPerspective(fieldOfView, aspectRatio, zNear, zFar);
	gluPerspective(fieldOfView, (float)ofGetWidth()/ofGetHeight(), zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef( 1, 1, 1 );
	gluLookAt( _actualCameraCoord[0], _actualCameraCoord[1], _actualCameraCoord[2], _actualFocalPointCoord[0], _actualFocalPointCoord[1], _actualFocalPointCoord[2], upVec[0], upVec[1], upVec[2]);
}

void sfCameraPlus::update()
{
	if( _hasPlugins )
	{
		// Loop through all plugins and update each one.
		for( unsigned int i = 0; i < _plugins.size(); i++ )
		{
			sfCameraPlugin* vPlugin = _plugins.at(i);

			// Update the state of the plugin.
			vPlugin->setCurrentFocalPoint( focalPointCoord );
			vPlugin->setCurrentCameraLocation( cameraCoord );
			vPlugin->update();

			// Set the current camera position and focal point to that
			// described by the plugin.
			// TODO How do we add the effects of multiple camera plugins?
			_actualCameraCoord = vPlugin->getDesiredCamera();
			_actualFocalPointCoord = vPlugin->getDesiredFocalPoint();
		}
	}
	else
	{
		_actualCameraCoord = cameraCoord;
		_actualFocalPointCoord = focalPointCoord;
	}
}

void sfCameraPlus::addPlugin( sfCameraPlugin* vP )
{
	// Add this plugin to the list of plugins.
	_plugins.push_back( vP );
	_hasPlugins = true;
}
