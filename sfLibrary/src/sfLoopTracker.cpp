/*
 * sfIterationTracker.cpp
 *
 *  Created on: Nov 30, 2010
 *      Author: marc.wren
 */

#include "sfLoopTracker.h"

sfLoopTracker::sfLoopTracker()
{
	_forwards = true;
	_iterationNumber = 0;
	_hasLooped = false;
	_numberOfLoops = 0;
	_loopSize = 4;
	_currentIndex = 0;
	_startIndex = 0;
}

sfLoopTracker::sfLoopTracker( int vTotal, int vCurrent )
{
	_forwards = true;
	_iterationNumber = 0;
	_hasLooped = false;
	_numberOfLoops = 0;
	_loopSize = vTotal;
	_currentIndex = vCurrent;
	_startIndex = vCurrent;
}

void sfLoopTracker::setStartIteration( int vStart )
{
	_startIndex = vStart;
}

void sfLoopTracker::iterateBackwards( bool vBackwards )
{
	_forwards = !vBackwards;
}

int sfLoopTracker::update()
{
	++_iterationNumber;

	if( _forwards )
	{
		++_currentIndex;

		if( _currentIndex > _loopSize - 1 )
		{
			_currentIndex = 0;
		}
	}
	else
	{
		-- _currentIndex;

		if( _currentIndex < 0 )
		{
			_currentIndex = _loopSize - 1;
		}
	}

	if( _currentIndex == _startIndex && _iterationNumber >= _loopSize )
	{
		_hasLooped = true;
		++_numberOfLoops;
	}

	return _currentIndex;
}

void sfLoopTracker::setCurrentIndex( int vCurrent )
{
	_currentIndex = vCurrent;
}

int sfLoopTracker::getCurrentIndex()
{
	return _currentIndex;
}

int sfLoopTracker::getCurrentIteration()
{
	return _iterationNumber;
}

int sfLoopTracker::getCurrentLoop()
{
	return _numberOfLoops;
}

void sfLoopTracker::setCurrentLoop( unsigned int vLoop )
{
	_numberOfLoops = vLoop;
}

void sfLoopTracker::setLoopSize( int vTotal )
{
	if( vTotal <= _currentIndex )
	{
		setCurrentIndex(0);
		_hasLooped = true;
		++_numberOfLoops;
	}
	_loopSize = vTotal;
}

int sfLoopTracker::getLoopSize()
{
	return _loopSize;
}

bool sfLoopTracker::isMinIndex()
{
	if( _currentIndex == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool sfLoopTracker::isLoopStart()
{
	if( _currentIndex == _startIndex )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool sfLoopTracker::hasLooped()
{
	return _hasLooped;
}
