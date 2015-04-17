/*
 * sfResolumeBeatEventTracker.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: marc.wren
 */

#ifndef SFRESOLUMEBEATEVENTTRACKER_CPP_
#define SFRESOLUMEBEATEVENTTRACKER_CPP_

#include "sfResolumeBeatEventTracker.h"
#include "ofMain.h"

sfResolumeBeatEventTracker::sfResolumeBeatEventTracker()
{
	_lastBeatValue = _beatTracker = 0;
	_beatThreshhold = 20;
	_maxBeatChange = 127;
	_isStandalone = false;
	_framesPerBeat = 30;
}

float* sfResolumeBeatEventTracker::getParameterAddress()
{
	return &_beatTracker;
}

float sfResolumeBeatEventTracker::getMaxChangeValue()
{
	return _maxBeatChange;
}

void sfResolumeBeatEventTracker::setThreshhold( float vT )
{
	_beatThreshhold = vT;
}

bool sfResolumeBeatEventTracker::isBeatEvent()
{
	if( _lastBeatValue > _beatTracker && _lastBeatValue - _beatTracker > _beatThreshhold )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void sfResolumeBeatEventTracker::update()
{
	_lastBeatValue = _beatTracker;

	if( _isStandalone )
	{
		_beatTracker = fmod( (float)ofGetFrameNum(), _framesPerBeat );
	}
}

float sfResolumeBeatEventTracker::getBeatStrength()
{
	return (_lastBeatValue - _beatTracker) / _maxBeatChange;
}

void sfResolumeBeatEventTracker::setStandalone( bool vIsStandalone )
{
	_isStandalone = vIsStandalone;
}

void sfResolumeBeatEventTracker::setFramesPerBeat( int vFPS )
{
	_framesPerBeat = vFPS;
}

#endif /* SFRESOLUMEBEATEVENTTRACKER_CPP_ */
