/*
 * sfBranch.cpp
 *
 *  Created on: Sep 30, 2010
 *      Author: marc.wren
 */

#include "sfBranch.h"
#include "sfDrawingUtil.h"

sfBranch::sfBranch()
{
	_numberOfSegments = 50;
	_continuousGrowth = false;
	_segmentLength = 15;
	_newBranchProbability = _subBranchProbability = 6;
//	_subBranchProbabilitySubtractor = 1;
	_thickness = 4;
	_subBranchThicknessFactor = 0.5;
	_rotationY = 0;
	_rotationZ = 0;
	_maxInitialRotation = 90;
	_directionY = 0;
	_directionZ = 0;
	_directionMultiplier = 20;
	_active = false;
	_numberOfPointsCreated = 0;
	_maxSubBranchesPerPoint = 1;
	_is3D = true;

	// TODO A version with symetrical sub branches
	// always at a 45 degree angle.
}

sfBranch::~sfBranch()
{
	if( !_points.empty() )
	{
		for( vector<sfBranchPoint*>::iterator i = _points.begin(); i < _points.end(); ++i )
		{
			delete *i;
		}

		_points.clear();
		_subBranches.clear();
	}
}

void sfBranch::setThickness( float vT )
{
	_thickness = vT;
}

float sfBranch::getRotationY()
{
	return _rotationY;
}

float sfBranch::getRotationZ()
{
	return _rotationZ;
}

void sfBranch::setRotationY( float vRY )
{
	_rotationY = vRY;
}

void sfBranch::setRotationZ( float vRZ )
{
	_rotationZ = vRZ;
}

void sfBranch::setNumberOfSegments( unsigned int vTotal )
{
	_numberOfSegments = vTotal;
}

void sfBranch::setSegmentLength( float vLength )
{
	_segmentLength = vLength;
}

void sfBranch::setBranchProbability( float vProbability )
{
	_newBranchProbability = vProbability;
}

void sfBranch::setIs3D( Boolean vIs3D )
{
	_is3D = vIs3D;
}

void sfBranch::_activate()
{
	_active = true;
	_quadric = gluNewQuadric();

	// Add the first point on the branch (0, 0, 0).
	sfBranchPoint* vFirst = new sfBranchPoint();
	_points.push_back( vFirst );
	_numberOfPointsCreated = 1;
}

void sfBranch::update()
{
	if( !isActive() )
	{
		_activate();
	}

	_removeOldBranchPoints();
	_addBranchPoint();
	_updateSubBranches();
}

void sfBranch::_removeOldBranchPoints()
{
	// Limit our branch to _numberOfSegments long.
	if( _continuousGrowth && _points.size() > _numberOfSegments )
	{
		int vDiff = _points.size() - _numberOfSegments;

		// Remove enough points to get us back to _numberOfSegments.
		for( int i = 0; i < vDiff; i++ )
		{
			sfBranchPoint* vPoint = _points.at(i);

			// If this point has subBranches, remove those from the subBranch list.
			if( vPoint->hasBranches() )
			{
				for( vector<sfBranchPoint*>::iterator j = _subBranches.begin(); j < _subBranches.end(); j++ )
				{
					if( *j == vPoint )
					{
						_subBranches.erase(j);
						break;
					}
				}
			}

			delete vPoint;
		}

		_points.erase( _points.begin(), _points.begin() + vDiff );
	}
}

void sfBranch::branch()
{
	branch( 0.5, 1 );
}

void sfBranch::branch( float vS )
{
	branch( vS, 1 );
}

void sfBranch::branch( float vS, int vT )
{
	if( isActive() )
	{
		_createSubBranches( _points.back(), vS, vT );
	}
}

void sfBranch::_addBranchPoint()
{
	if( _continuousGrowth || _points.size() <= _numberOfSegments )
	{
		// Create a new point on the branch.
		sfBranchPoint* vNextPoint = new sfBranchPoint();

		ofxVec3f vNextPointLoc = _createNewPointLoc();
		vNextPoint->setLoc( vNextPointLoc.x, vNextPointLoc.y, vNextPointLoc.z );

		// Does this branch point create another branch?
		if( ofRandom( 0, 100 ) < _newBranchProbability && _points.size() > 1 )
		{
			_createSubBranches( vNextPoint );
		}

		_points.push_back( vNextPoint );
		++_numberOfPointsCreated;
	}
}

void sfBranch::_createSubBranches( sfBranchPoint* vPoint )
{
	int vNum = ofRandom( 1, _maxSubBranchesPerPoint );
	_createSubBranches( vPoint, 0.5, vNum );
}

void sfBranch::_createSubBranches( sfBranchPoint* vPoint, float vS, int vNum )
{
	for( int i = 0; i < vNum; i++ )
	{
		sfBranch* vBranch = new sfBranch();
		vBranch->setRotationY( ofRandom( -_maxInitialRotation, _maxInitialRotation ) );
		if( _is3D )
		{
			vBranch->setRotationZ( ofRandom( -_maxInitialRotation, _maxInitialRotation ) );
		}
		vBranch->setThickness( _thickness * _subBranchThicknessFactor );
		vBranch->setSegmentLength( _segmentLength / 1.5 );
		vBranch->setIs3D( _is3D );
//		vBranch->setBranchProbability( _subBranchProbability - _subBranchProbabilitySubtractor );
		vBranch->setBranchProbability( _subBranchProbability * vS );
		vBranch->setNumberOfSegments( _numberOfSegments * vS );

		vPoint->addBranch( vBranch );
	}

	_subBranches.push_back( vPoint );
}

void sfBranch::_updateSubBranches()
{
	// Update all sub-branches of this branch.
	for( unsigned int i = 0; i < _subBranches.size(); i++ )
	{
		sfBranchPoint* vPoint = _subBranches.at(i);
		vPoint->update();
	}
}

ofxVec3f sfBranch::_createNewPointLoc()
{
	sfBranchPoint* vLastPoint = _points.back();
	ofxVec3f vLastPointLoc = vLastPoint->getLoc();
	_directionY += ofRandom( -_directionMultiplier, _directionMultiplier );
	_directionZ += ofRandom( -_directionMultiplier, _directionMultiplier );

	float vRad1 = DEG_TO_RAD * _directionY;
	float vX = vLastPointLoc.x + (cos( vRad1 ) * _segmentLength);
	float vY = vLastPointLoc.y + (sin( vRad1 ) * _segmentLength);
	float vZ;

	if( _is3D )
	{
		float vRad2 = DEG_TO_RAD * _directionZ;
		vZ = vLastPointLoc.z + (sin( vRad2 ) * _segmentLength );
	}
	else
	{
		vZ = vLastPointLoc.z;
	}

	ofxVec3f vNextPointLoc( vX, vY, vZ );
	return vNextPointLoc;
}

ofxVec3f sfBranch::getStart()
{
	return _points.front()->getLoc();
}

ofxVec3f sfBranch::getEnd()
{
	return _points.back()->getLoc();
}

Boolean sfBranch::isActive()
{
	return _active;
}

void sfBranch::draw()
{
	glPushMatrix();
	glRotatef( _rotationY, _rotationZ, 0, 1 );

	_drawBranch();
	_drawSubBranches();

	glPopMatrix();
}

void sfBranch::_drawBranch()
{
	if( isActive() )
	{
		// Draw the lines of this branch.
		glLineWidth( _thickness );
		glBegin( GL_LINE_STRIP );

		for( unsigned int i = 0; i < _points.size(); i++ )
		{
			sfBranchPoint* vPoint = _points.at( i );
			ofxVec3f vPointLoc = vPoint->getLoc();

			// Draw this branch.
			glVertex3f( vPointLoc.x, vPointLoc.y, vPointLoc.z );
		}
		glEnd();
	}
}

void sfBranch::_drawSubBranches()
{
	if( isActive() && _subBranches.size() > 0 )
	{
		// Draw any branches that branch off from this one.
		for( unsigned int i = 0; i < _subBranches.size(); i++ )
		{
			sfBranchPoint* vPoint = _subBranches.at( i );
			ofxVec3f vPointLoc = vPoint->getLoc();

			glPushMatrix();
			glTranslatef( vPointLoc.x, vPointLoc.y, vPointLoc.z );

			// Draw a dot a branch points.
			gluSphere( _quadric, _thickness * 6, 10, 10 );

			// Draw any branches at this branch point.
			vPoint->draw();

			glPopMatrix();
		}
	}
}
