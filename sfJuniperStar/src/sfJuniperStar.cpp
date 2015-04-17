/*
 * JuniperStar.cpp
 *
 *  Created on: Aug 12, 2010
 *      Author: marcwren
 */

#include "sfJuniperStar.h"
#include "ofMain.h"
#include "sfDrawingUtil.h"
#include <vector>
#include <math.h>
#include "sfLoopTracker.h"
#include <sstream>
#include "sfOutOfBounds.h"
#include <cmath>

sfJuniperStar::sfJuniperStar()
{
	_numberOfPoints = 4;
	_activePoint = 0;
	_alpha = 0.75;
	_pointXOffset = 0;
	_pointYOffset = 50;
	_pointWidth = 75;
	_pointHeight = 150;
	_pointRotation = 0;
	_pointSpacing = 0;
	_locationChangeDuration = 10;
	_isHiding = false;
	_sortPoints = true;
	_pointsRequireSorting = true;
	_location.setAnimation( sfAnimatedPoint::QUAD, sfAnimatedPoint::EASE_OUT, _locationChangeDuration );

	for( int j = 0; j < _numberOfPoints; j++ )
	{
		_createPoint( 0, 0 );
	}
//	_distributePoints();
}

sfJuniperStar::~sfJuniperStar()
{
	for( unsigned int i = 0; i < _points.size(); i++ )
	{
		delete _points.at(i);
	}
	_points.clear();
}

void sfJuniperStar::_createPoint( int vIndex, int vR )
{
	sfJuniperPoint* vPoint = new sfJuniperPoint( vR );
	vPoint->setOffset( _pointXOffset, _pointYOffset );
	vPoint->setAlpha( _alpha );
	vPoint->setXOffset( _pointXOffset );
	vPoint->setYOffset( _pointYOffset );
	vPoint->setSubRotation( _pointRotation );
	vPoint->setHeight( _pointHeight );
	vPoint->setWidth( _pointWidth );
	vPoint->index = vIndex;
	_points.insert( _points.begin() + vIndex, vPoint );
}

void sfJuniperStar::_distributePoints()
{
	sfDrawingUtil vUtil;
	vector<int> vColors = vUtil.colorWheel( _points.size() );
	float vDegreesPerRotation = 360.0 / _points.size();

	sfLoopTracker vIT( _points.size(), _activePoint );
	vIT.iterateBackwards( true );
	for( unsigned int i = 0; !vIT.hasLooped(); i++, vIT.update() )
	{
		sfJuniperPoint* vPoint = _points.at( vIT.getCurrentIndex() );

		float vZ =  0;
		if( _sortPoints )
		{
			vZ += -_pointSpacing * i;
		}
		else
		{
			vZ += -_pointSpacing * vIT.getCurrentIndex();
		}
		vPoint->setZLocation( vZ );

		float vDegrees = (float)vIT.getCurrentIndex() * -vDegreesPerRotation;

		vPoint->setRotation( vDegrees );
		vPoint->setHighlightColor( vColors.at( vIT.getCurrentIndex() ) );
		vPoint->setAlpha( _alpha );
	}

	_pointsRequireSorting = false;
}

void sfJuniperStar::setActivePoint( unsigned int vIndex )
{
	if( !_isHiding )
	{
		if( vIndex >= _points.size() )
		{
			stringstream vNumberOfPoints;
			vNumberOfPoints << _points.size();
			stringstream vAttemptedIndex;
			vAttemptedIndex << vIndex;
			string vMessage = "You cannot set the active point to a value larger than the number of points.";
			vMessage += " The current number of points is " + vNumberOfPoints.str() + " and attempted to set active point to " + vAttemptedIndex.str();
			throw sfOutOfBounds( vMessage );
		}

		for( unsigned int i = 0; i < _points.size(); i++ )
		{
			if( i == vIndex )
			{
				_points.at( i )->activate();
			}
			else
			{
				_points.at(i)->deactivate();
			}
		}

		_activePoint = vIndex;

		_pointsRequireSorting = true;
//		_distributePoints();
	}
}

unsigned int sfJuniperStar::getActivePoint()
{
	return _activePoint;
}

void sfJuniperStar::setSortPoints( bool vSort )
{
	_sortPoints = vSort;
}

void sfJuniperStar::nextPoint()
{
	if( !_isHiding )
	{
		_points.at( _activePoint )->deactivate();

		++_activePoint;
		if( _activePoint >= _numberOfPoints )
		{
			_activePoint = 0;
		}

		_points.at( _activePoint )->activate();

		_pointsRequireSorting = true;
//		_distributePoints();
	}
}

void sfJuniperStar::hide()
{
	if( !_isHiding )
	{
		for( int i = 0; i < _points.size(); i++ )
		{
			_points.at( i )->hide();
		}
		_isHiding = true;
	}
}

bool sfJuniperStar::isHidden()
{
	for( unsigned int i = 0; i < _points.size(); i++ )
	{
		if( !_points.at(i)->isHidden() )
		{
			return false;
		}
	}

	return true;
}

void sfJuniperStar::move( float vX, float vY, float vZ )
{
	_location.setTarget( vX, vY, vZ );
	_location.start();
}

void sfJuniperStar::setMoveSpeed( int vS )
{
	_location.setAnimationDuration( vS );
}

void sfJuniperStar::show()
{
	for( int i = 0; i < _numberOfPoints; i++ )
	{
		_points.at( i )->show();
	}

	_points.at( _activePoint )->activate();

	_isHiding = false;
}

void sfJuniperStar::setPointXOffset( float vX )
{
	if( !_isHiding )
	{
		if( vX != _pointXOffset )
		{
			_pointXOffset = vX;
			for( unsigned int i = 0; i < _points.size(); i++ )
			{
				_points.at(i)->setXOffset( _pointXOffset );
			}
		}
	}
}

void sfJuniperStar::setPointYOffset( float vY )
{
	if( !_isHiding )
	{
		if( vY != _pointYOffset )
		{
			_pointYOffset = vY;
			for( unsigned int i = 0; i < _points.size(); i++ )
			{
				_points.at(i)->setYOffset( _pointYOffset );
			}
		}
	}
}

void sfJuniperStar::setPointRotation( float vR )
{
	if( !_isHiding )
	{
		if( vR != _pointRotation )
		{
			_pointRotation = vR;
			for( unsigned int i = 0; i < _points.size(); i++ )
			{
				_points.at(i)->setSubRotation( _pointRotation );
			}
		}
	}
}

void sfJuniperStar::setPointHeight( float vH )
{
	if( !_isHiding )
	{
		if( vH != _pointHeight )
		{
			_pointHeight = vH;

			// Ensure that the point is at least a circle.
//			if( _pointHeight < _pointWidth )
//			{
//				setPointWidth( _pointHeight );
//			}

			for( unsigned int i = 0; i < _points.size(); i++ )
			{
				_points.at(i)->setHeight( _pointHeight );
			}
		}
	}
}

void sfJuniperStar::setPointWidth( float vW )
{
	if( !_isHiding )
	{
		if( vW != _pointWidth )
		{
			_pointWidth = vW;

			// Ensure that the point is at least a circle.
//			if( _pointWidth > _pointHeight )
//			{
//				setPointHeight( _pointWidth );
//			}

			for( unsigned int i = 0; i < _points.size(); i++ )
			{
				_points.at(i)->setWidth( _pointWidth );
			}
		}
	}
}

void sfJuniperStar::setNumberOfPoints( int vP )
{
	if( !_isHiding )
	{
		// TODO Validate that vP is positive.
		int vDiff = vP - _numberOfPoints;
		if( vDiff > 0 )
		{
			addPoints( vDiff );
		}
		else if( vDiff < 0 )
		{
			removePoints( -vDiff );
		}
	}
}

void sfJuniperStar::addPoints( int vNum )
{
	if( !_isHiding )
	{
		float vDegreesPerRotation = _points.size() == 0 ? 0 : 360/_points.size();

		for( int i = 0; i < vNum; i++ )
		{
			float vR = _activePoint * -vDegreesPerRotation;
			_createPoint( _activePoint + 1, vR );
			_points.at( _activePoint + 1 )->show();
		}
		_numberOfPoints = _points.size();

		_pointsRequireSorting = true;
//		_distributePoints();
	}
}

void sfJuniperStar::removePoints( unsigned int vNum )
{
	if( !_isHiding )
	{
		// Delete point object references in the points vector.
		for( vector<sfJuniperPoint*>::iterator vIT = _points.begin(); vIT != _points.begin() + vNum; ++vIT )
		{
			sfJuniperPoint* vPoint = *vIT;
			delete vPoint;
			_points.erase( vIT );
		}

		_numberOfPoints = _points.size();

		_pointsRequireSorting = true;
//		_distributePoints();
	}
}

void sfJuniperStar::setPointSpacing( float vD )
{
	if( !_isHiding )
	{
		if( _pointSpacing != vD )
		{
			_pointSpacing = vD;

			_pointsRequireSorting = true;
//			_distributePoints();
		}
	}
}

float sfJuniperStar::getDiameter()
{
	return _pointHeight + abs( (int)_pointYOffset ) * 2;
}

ofxVec3f sfJuniperStar::getLocation()
{
	return _location;
}

void sfJuniperStar::update()
{
	if( _pointsRequireSorting )
	{
		_distributePoints();
	}

	_location.update();

	for( unsigned int i = 0; i < _points.size(); i++ )
	{
		_points.at(i)->update();
	}
}

void sfJuniperStar::draw()
{
	unsigned int vStart;
	sfLoopTracker vIT;

	// Draw points from back to front.
	if( _sortPoints )
	{
		vStart = _activePoint == _points.size() - 1 ? 0  : _activePoint + 1;
		vIT = sfLoopTracker( _points.size(), vStart );
	}
	else
	{
		vStart = _points.size() - 1;
		// TODO Is this doing unnecessary copies? Is there a way to optimize it?
		vIT = sfLoopTracker( _points.size(), vStart );
		vIT.iterateBackwards( true );
	}

	for( ; !vIT.hasLooped(); vIT.update() )
	{
		glPushMatrix();

		glTranslatef( _location.x, _location.y, _location.z );

		// Draw the current point.
		_points.at( vIT.getCurrentIndex() )->draw();

		glPopMatrix();
	}
}
