/*
 * SpiderPoints.cpp
 *
 *  Created on: Jul 14, 2010
 *      Author: marcwren
 */

#include "sfSpiderPoints.h"
#include "ofMain.h"
#include <math.h>
#include <vector>
#include "sfMathUtils.h"
#include "Quad.h"
#include "sfOutOfBounds.h"
#include "sfDrawingUtil.h"

// DEBUG
#include <sstream>

sfSpiderPoints::sfSpiderPoints()
{
	_initialized = false;
	_x = 0;
	_y = 0;
	_z = 0;
	_rotation = sfAnimatedPoint( 0, 0, 0, 0.25f );
	_rotationDuration = 30;
	_rotationType = sfAnimatedPoint::SINE;
	_rotationEasing = sfAnimatedPoint::EASE_IN_OUT;
	_rotation.setAnimation( _rotationType, _rotationEasing, _rotationDuration);
	_pointAnimationDuration = 15;
	_pointAnimationType = sfAnimatedPoint::EXPO;
	_pointAnimationEasing = sfAnimatedPoint::EASE_OUT;
	_innerRadius = 100;
	_outerRadius = 200;
	_numberOfActivePoints = 20;
	_pointStaggerDuration = 0;
	_pointStagger = sfLoopTracker( _pointStaggerDuration, 0 );
	_is3D = true;
	_useColors = false;
	_rotation.setAnimation( _rotationType, _rotationEasing, _rotationDuration);
	_points.clear();
}

sfSpiderPoints::~sfSpiderPoints()
{
	if( _initialized )
	{
		for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin(); vIT != _points.end(); vIT++ )
		{
			sfSpiderPointsPoint* vPoint = *vIT;
			delete vPoint;
		}
	}
}

void sfSpiderPoints::setup()
{
	// This has to be set before calling addPoints.
	_initialized = true;

	// Create all our initial points.
	addPoints( _numberOfActivePoints );

	rotate();
}

void sfSpiderPoints::addPoints( unsigned int vT )
{
	if( !_initialized )
	{
		_numberOfActivePoints = _points.size() + vT;
	}
	else
	{
		// If there are points currently being animated out,
		// start by un-hiding those points instead of adding new ones.
		// TODO Replace _numberOfPoints with _points.size();
		unsigned int vPointsToUnhide;
		unsigned int vPointsLeftToAdd = vT;
		int vPointsHiding = _points.size() - _numberOfActivePoints;

		if( (signed int)vT <= vPointsHiding )
		{
			vPointsToUnhide = vT;
			vPointsLeftToAdd = 0;
		}
		else
		{
			vPointsToUnhide = vPointsHiding;
			vPointsLeftToAdd = vT - vPointsHiding;
		}

		if( vPointsToUnhide > 0 )
		{
			_unhidePoints( vPointsToUnhide );
		}

		// If there are still points that need to be added, add them.
		for( unsigned int i = 0; i < vPointsLeftToAdd; i++ )
		{
			sfSpiderPointsPoint* vPoint = new sfSpiderPointsPoint();
			_setupPoint( vPoint );
			_points.push_back( vPoint );
		}

		// Reset the point stagger-er to start moving points from where we added new points.
		if( _pointStaggerDuration == 0 )
		{
			_pointStagger.setCurrentLoop( 0 );
		}
		else	if( _pointStagger.getCurrentLoop() > _numberOfActivePoints )
		{
			_pointStagger.setCurrentLoop( _numberOfActivePoints );
		}

		_numberOfActivePoints += vT;
	}
}

void sfSpiderPoints::_unhidePoints( unsigned int vTotal )
{
	unsigned int vEnd = _numberOfActivePoints + vTotal;

	if( vEnd > _points.size() )
	{
		throw sfOutOfBounds( "Attempted to unhide more points than are currently hidden." );
	}

	for( unsigned int i = _numberOfActivePoints; i < vEnd; i++ )
	{
		sfSpiderPointsPoint* vPoint = _points.at(i);
		vPoint->unhide();
		vPoint->setTarget( _newPointLocation( _x ), _newPointLocation( _y ), _newPointLocation( _z ) );
	}
}

void sfSpiderPoints::_setupPoint( sfSpiderPointsPoint* vPoint )
{
	int vX = _newPointLocation( _x );
	int vY = _newPointLocation( _y );
	int vZ = 0;

	if( _is3D )
		vZ = _newPointLocation( _z );

	// Make new points grow out of the last point.
	if( _points.size() > 0 )
	{
		sfSpiderPointsPoint* vLastPoint = _points.at( _points.size() - 1 );
		vPoint->set( vLastPoint->x, vLastPoint->y, vLastPoint->z );
	}
	else
	{
		vPoint->set( _x, _y, _z );
	}
	vPoint->setAnimation( _pointAnimationType, _pointAnimationEasing, _pointAnimationDuration );
	vPoint->setTarget( vX, vY, vZ );

//	if( _pointStaggerDuration == 0 )
//	{
//		vPoint->start();
//	}
}

void sfSpiderPoints::removePoints( unsigned int vT )
{
	if( vT > _numberOfActivePoints )
	{
		throw sfOutOfBounds( "Cannot remove more points than exist." );
	}

	// Make sure we always have at least 3 active points.
	if( _numberOfActivePoints - vT < 3 )
	{
		vT = _numberOfActivePoints - 3;
	}

	if( !_initialized )
	{
		_numberOfActivePoints = _points.size() - vT;
	}
	else
	{
		unsigned int vEnd = _numberOfActivePoints - 1 - vT;
		sfSpiderPointsPoint* vLastPoint = _points.at( vEnd );
		for( unsigned int i = _numberOfActivePoints - 1; i > vEnd; i-- )
		{
//			int vPointStaggerLoop = _pointStagger.getCurrentLoop();
//			int vNumberOfActivePoints = _numberOfActivePoints;
//			int vNumberOfPoints = _numberOfPoints;
//			int vActualNumberOfPoints = _points.size();

			sfSpiderPointsPoint* vPoint = _points.at( i );
			vPoint->hide( vLastPoint->x, vLastPoint->y, vLastPoint->z );
		}

		_numberOfActivePoints -= vT;
	}
}

void sfSpiderPoints::_removeOldPoints()
{
	for( int i = _points.size() - 1; i >= 0; i-- )
	{
		sfSpiderPointsPoint* vPoint = _points.at( i );

		if( vPoint->isHidden() )
		{
			delete vPoint;
			_points.erase( _points.begin() + i );
		}
	}
/*
	if( _points.size() < _numberOfActivePoints )
	{
		std::stringstream vNOAP;
		vNOAP << _numberOfActivePoints;
		std::stringstream vP;
		vP << _points.size();
		std::cout << "Number of points is less than the number of active points-> AP:" << vNOAP.str() << " | P: " << vP.str() << ". " << std::endl;
	}
	*/
}

void sfSpiderPoints::setAutoRotateDuration( int vD )
{
	if( _rotationDuration != vD )
	{
		_rotationDuration = vD;
		_rotation.setAnimationDuration( _rotationDuration );
	}
}

void sfSpiderPoints::setInnerRadius( int vR )
{
	_innerRadius = vR;
}

void sfSpiderPoints::setOuterRadius( int vR )
{
	_outerRadius = vR;
}

void sfSpiderPoints::setWindowSize( int vW, int vH )
{
	_outerRadius = ( vH < vW ) ? vH / 2: vW / 2;
	_innerRadius = ( _outerRadius < _innerRadius ) ? _outerRadius / 2 : _innerRadius;
}

void sfSpiderPoints::setLocation( float vX, float vY, float vZ )
{
	_x = vX;
	_y = vY;
	_z = vZ;
}

void sfSpiderPoints::setPointSpeed( int vD )
{
	if( _pointAnimationDuration != vD )
	{
		_pointAnimationDuration = vD;
		if( (int)_points.size() > 0 )
		{
			for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin(); vIT != _points.end(); vIT++ )
			{
				sfSpiderPointsPoint* vPoint = *vIT;
				vPoint->setAnimationDuration( _pointAnimationDuration );
			}
		}
	}
}

void sfSpiderPoints::setNumberOfPoints( unsigned int vT )
{
	if( _numberOfActivePoints != vT && vT >= 3 )
	{
		if( !_initialized )
		{
			_numberOfActivePoints = vT;
		}
		else
		{
			int vDiff = vT - _numberOfActivePoints;
			if( vDiff > 0 )
			{
				addPoints( vDiff );
			}
			else
			{
				removePoints( -vDiff );
			}
		}
	}
}

void sfSpiderPoints::setPointAnimationEaseDirection( int vEasing )
{
	if( _pointAnimationEasing != vEasing )
	{
		_pointAnimationEasing = vEasing;
		if(  (int)_points.size() > 0 )
		{
			for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin(); vIT != _points.end(); vIT++ )
			{
				sfSpiderPointsPoint* vPoint = *vIT;
				vPoint->setAnimationDirection( _pointAnimationEasing );
			}
		}
	}
}

void sfSpiderPoints::setPointStaggerDuration( int vF )
{
	if( _pointStaggerDuration != vF )
	{
		_pointStaggerDuration = vF;
		_pointStagger = sfLoopTracker( _pointStaggerDuration, 0 );
	}
}

void sfSpiderPoints::setRotationEaseDirection( int vEasing )
{
	if( _rotationEasing != vEasing )
	{
		_rotationEasing = vEasing;
		_rotation.setAnimationDirection( _rotationEasing );
	}
}

int sfSpiderPoints::_newPointLocation( int vRoot )
{
	sfMathUtils vUtil;
	return  vRoot + ( ofRandom( _innerRadius, _outerRadius ) * vUtil.positiveOrNegative() );
}

void sfSpiderPoints::movePoints()
{
	for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin(); vIT != _points.end(); vIT++ )
	{
		sfSpiderPointsPoint* vPoint = *vIT;

		if( !vPoint->isHiding() )
		{
			int vZ = 0;
			if( _is3D )
				vZ = _newPointLocation( _z );

			vPoint->setTarget( _newPointLocation( _x ), _newPointLocation( _y ), vZ );

//			if( _pointStaggerDuration == 0 )
//			{
//				vPoint->start();
//			}
		}
	}

	// Reset point stagger so points will start moving to their new locations
	// on the next update call.
	_pointStagger = sfLoopTracker( _pointStaggerDuration, 0 );
}

void sfSpiderPoints::rotate()
{
	_rotation.setTarget( ofRandom( 0, 360 ), ofRandom( 0, 360 ), ofRandom( 0, 360 ) );
	_rotation.start();
}

void sfSpiderPoints::rotate( float vX, float vY, float vZ )
{
	if( _rotation.targetX != vX && _rotation.targetY != vY && _rotation.targetZ != vZ )
	{
		_rotation.set( vX, vY, vZ );
		_rotation.start();
	}
}

void sfSpiderPoints::useColors( bool vUseColors )
{
	_useColors = vUseColors;
}

void sfSpiderPoints::update()
{
	_removeOldPoints();

	// Stagger the movement of points.
	if( _pointStaggerDuration == 0 )
	{
		if( _pointStagger.getCurrentLoop() == 0 )
		{
			// Start all points.
			for( unsigned int i = 0; i < _numberOfActivePoints; i++ )
			{
				sfSpiderPointsPoint* vPoint = _points.at( i );
				vPoint->start();
			}
		}
	}
	else if( _pointStagger.isLoopStart() && _pointStagger.getCurrentLoop() < _numberOfActivePoints )
	{
//		int vPointStaggerLoop = _pointStagger.getCurrentLoop();
//		int vNumberOfActivePoints = _numberOfActivePoints;
//		int vNumberOfPoints = _numberOfPoints;
//		int vActualNumberOfPoints = _points.size();

		sfSpiderPointsPoint* vPoint = _points.at( _pointStagger.getCurrentLoop() );
		vPoint->start();
	}
	_pointStagger.update();

	// Rotate the object.
	_rotation.update();

	for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin(); vIT != _points.end(); vIT++ )
	{
		sfSpiderPointsPoint* vPoint = *vIT;
		vPoint->update();
	}
}

void sfSpiderPoints::draw()
{
	if( _is3D )
	{
		ofRotateY( _rotation.y );
		ofRotateX( _rotation.x );
	}
	ofRotateZ( _rotation.z );

	sfDrawingUtil vUtil = sfDrawingUtil();
	vector<int> vColors = vUtil.colorWheel( 50 );

	int i = 0;
	for( vector<sfSpiderPointsPoint*>::iterator vIT = _points.begin() + 2; vIT != _points.end(); vIT++, i++ )
	{
		sfSpiderPointsPoint* vPoint1 = *vIT;
		sfSpiderPointsPoint* vPoint2 = *( vIT - 1);
		sfSpiderPointsPoint* vPoint3 = *( vIT - 2);

		float vR = 1.0;
		float vG = 1.0;
		float vB = 1.0;
		if( _useColors )
		{
			int vColor = vColors.at( i );
			vR = (float)vUtil.getHexRedValue( vColor ) / 255.0;
			vG = (float)vUtil.getHexGreenValue( vColor ) / 255.0;
			vB = (float)vUtil.getHexBlueValue( vColor ) / 255.0;
		}

		// Draw the triangle polygon.
		glBegin( GL_POLYGON );
		glColor3f( vR, vG, vB );
		glVertex3f( vPoint1->x, vPoint1->y, vPoint1->z );
		glVertex3f( vPoint2->x, vPoint2->y, vPoint2->z );
		glVertex3f( vPoint3->x, vPoint3->y, vPoint3->z );
		glEnd();

		// Outline the shape in order to get anti-aliased edges.
//		glBegin( GL_LINE_LOOP );
//		glColor3f( vR, vG, vB );
//		glVertex3f( vPoint1->x, vPoint1->y, vPoint1->z );
//		glVertex3f( vPoint2->x, vPoint2->y, vPoint2->z );
//		glVertex3f( vPoint3->x, vPoint3->y, vPoint3->z );
//		glEnd();
	}
}
