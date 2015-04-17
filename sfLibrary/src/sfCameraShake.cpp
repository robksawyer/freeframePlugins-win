/*
 * sfCameraShake.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#include "sfCameraShake.h"
#include "sfCamera.h"

sfCameraShake::sfCameraShake()
{
	_shakeDuration = 30;
	_maxShakeWidth = 450;
//	_shakeCountdown = -1;
	_cameraShaker.setAnimation( sfAnimatedPoint::ELASTIC, sfAnimatedPoint::EASE_OUT, _shakeDuration );
	_focalPointShaker.setAnimation( sfAnimatedPoint::ELASTIC, sfAnimatedPoint::EASE_OUT, _shakeDuration );
}

void sfCameraShake::setShakeDuration( float vD )
{
	_shakeDuration = vD;
	_focalPointShaker.setAnimationDuration( vD );
	_cameraShaker.setAnimationDuration( vD );
}

void sfCameraShake::setMaxShakeWidth( float vW )
{
	_maxShakeWidth = vW;
}

void sfCameraShake::shake()
{
	// TODO Also use a _minShakeWidth so the shaking is at least the min
	// but no more than the max.
	float vCX = _actualCamera.x + ofRandom( _maxShakeWidth, -_maxShakeWidth );
	float vCY = _actualCamera.y + ofRandom( _maxShakeWidth, -_maxShakeWidth );
	float vCZ = _actualCamera.z + ofRandom( _maxShakeWidth, -_maxShakeWidth );

	_cameraShaker.set( vCX, vCY, vCZ );
	_cameraShaker.setTarget( _actualCamera.x, _actualCamera.y, _actualCamera.z );
	_cameraShaker.start();

	float vFX = _actualFocalPoint.x + ofRandom( _maxShakeWidth, -_maxShakeWidth );
	float vFY = _actualFocalPoint.y + ofRandom( _maxShakeWidth, -_maxShakeWidth );
	float vFZ = _actualFocalPoint.z + ofRandom( _maxShakeWidth, -_maxShakeWidth );

	_focalPointShaker.set( vFX, vFY, vFZ );
	_focalPointShaker.setTarget( _actualFocalPoint.x, _actualFocalPoint.y, _actualFocalPoint.z );
	_focalPointShaker.start();
}

void sfCameraShake::update()
{
	// Update the camera shaker.
	if( _cameraShaker.isAnimating() )
	{
		if( _lastActualCamera != _actualCamera )
		{
			ofxVec3f vDiff = _actualCamera - _lastActualCamera;
			_cameraShaker.targetX += vDiff.x;
			_cameraShaker.targetY += vDiff.y;
			_cameraShaker.targetZ += vDiff.z;
		}
		_cameraShaker.update();
		_desiredCamera.set( _cameraShaker.x, _cameraShaker.y, _cameraShaker.z );
	}
	else
	{
		_desiredCamera = _actualCamera;
	}

	// Update the focal point shaker.
	if( _focalPointShaker.isAnimating() )
	{
		if( _lastDesiredFocalPoint != _desiredFocalPoint )
		{
			ofxVec3f vDiff = _desiredFocalPoint - _lastDesiredFocalPoint;
			_focalPointShaker.targetX += vDiff.x;
			_focalPointShaker.targetY += vDiff.y;
			_focalPointShaker.targetZ += vDiff.z;
		}
		_focalPointShaker.update();
		_desiredFocalPoint.set( _focalPointShaker.x, _focalPointShaker.y, _focalPointShaker.z );
	}
	else
	{
		_desiredFocalPoint = _actualFocalPoint;
	}
}
