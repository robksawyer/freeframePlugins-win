/*
 * sfCameraSineWave.h
 *
 *  Created on: Nov 8, 2010
 *      Author: marc.wren
 */

#include "sfCameraSineWave.h"
#include "sfCamera.h"

sfCameraSineWave::sfCameraSineWave()
{
	_shakeDuration = 45;
	_shakeCountdown = 1;
	_maxWaveWidth = 300;
	_minWaveWidth = 20;
	_rotation = 0;
	_rotationSpeed = 35;
}

void sfCameraSineWave::setWaveSpeed( float vS )
{
	_rotationSpeed = vS;
}

void sfCameraSineWave::setShakeDuration( float vD )
{
	_shakeDuration = vD;
}

void sfCameraSineWave::setMinWaveWidth( float vW )
{
	_minWaveWidth = vW;
}

void sfCameraSineWave::setMaxWaveWidth( float vW )
{
	_maxWaveWidth = vW;
}

void sfCameraSineWave::shake()
{
	_shakeCountdown = _shakeDuration;
}

void sfCameraSineWave::update()
{
	if( _shakeCountdown > 1 )
	{
		--_shakeCountdown;
	}

	_rotation += _rotationSpeed;
	if( _rotation > 360 )
	{
		_rotation = fmod( _rotation, 360 );
	}

	float vWaveSpread = _maxWaveWidth - _minWaveWidth;
	float vWaveFactor = vWaveSpread * ( (float)_shakeCountdown / (float)_shakeDuration);
	float vFY = _actualFocalPoint.y + sin( _rotation * DEG_TO_RAD ) * (_minWaveWidth + vWaveFactor);

	_desiredFocalPoint.set( _actualFocalPoint.x, vFY, vFY );
	_desiredCamera = _actualCamera;
}
