/*
 * sfCameraPlugin.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: marc.wren
 */

#include "sfCameraPlugin.h"

void sfCameraPlugin::setCurrentCameraLocation( ofxVec3f vC )
{
	_lastDesiredCamera = _desiredCamera;
	_lastActualCamera = _actualCamera;
	_actualCamera = _desiredCamera = vC;
}

void sfCameraPlugin::setCurrentFocalPoint( ofxVec3f vFocal )
{
	_lastDesiredFocalPoint = _desiredFocalPoint;
	_lastActualFocalPoint = _actualFocalPoint;
	_actualFocalPoint = _desiredFocalPoint = vFocal;
}

void sfCameraPlugin::update()
{

}

ofxVec3f sfCameraPlugin::getDesiredCamera()
{
	return _desiredCamera;
}

ofxVec3f sfCameraPlugin::getDesiredFocalPoint()
{
	return _desiredFocalPoint;
}
