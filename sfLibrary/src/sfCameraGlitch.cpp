/*
 * sfCameraGlitch.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#include "sfCameraGlitch.h"
#include "sfCamera.h"

sfCameraGlitch::sfCameraGlitch()
{
	_glitchDuration = 5;
	_maxGlitchWidth = 60;
	_glitchCountdown = -1;
}

void sfCameraGlitch::setGlitchDuration( float vD )
{
	_glitchDuration = vD;
}

void sfCameraGlitch::setMaxGlitchWidth( float vW )
{
	_maxGlitchWidth = vW;
}

void sfCameraGlitch::glitch()
{
	_glitchCountdown = _glitchDuration;
//	_focalPoint = centerCoord;
//	_targetEye = cameraCoord;
}

void sfCameraGlitch::update()
{
	if( _glitchCountdown > 0 )
	{
		--_glitchCountdown;
		_desiredFocalPoint.x = _actualFocalPoint.x + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );
		_desiredFocalPoint.y = _actualFocalPoint.y + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );
		_desiredFocalPoint.z = _actualFocalPoint.z + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );

		_desiredCamera.x = _actualCamera.x + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );
		_desiredCamera.y = _actualCamera.y + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );
		_desiredCamera.z = _actualCamera.z + ofRandom( _maxGlitchWidth, -_maxGlitchWidth );
	}
	else if( _glitchCountdown == 0 )
	{
		_glitchCountdown = -1;
		_desiredFocalPoint = _actualFocalPoint;
		_desiredCamera = _actualCamera;
	}
	else
	{
		_desiredFocalPoint = _actualFocalPoint;
		_desiredCamera = _actualCamera;
	}
}
