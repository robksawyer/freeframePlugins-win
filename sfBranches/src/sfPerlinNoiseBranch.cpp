/*
 * sfPerlinNoiseBranch.cpp
 *
 *  Created on: Oct 5, 2010
 *      Author: marc.wren
 */

#include "sfPerlinNoiseBranch.h"

sfPerlinNoiseBranch::sfPerlinNoiseBranch()
{
	_noiseMultiplier = 50;
	_numberOfSegments = 100;
	_continuousGrowth = true;
//	_maxSubBranchesPerPoint = 3;
	_subBranchMaxNumberOfSegments = 75;
}

ofxVec3f sfPerlinNoiseBranch::_createNewPointLoc()
{
	sfBranchPoint* vLastPoint = _points.back();
	ofxVec3f vLastPointLoc = vLastPoint->getLoc();

	float vNoiseX = ( _numberOfPointsCreated + 1 ) * 0.1;
	float vY = _noise.noise( vNoiseX ) * _noiseMultiplier;
	float vZ;

	if( _is3D )
	{
		vZ = _noise.noise( vNoiseX, vNoiseX ) * _noiseMultiplier;
	}
	else
	{
		vZ = vLastPointLoc.z;
	}

	ofxVec3f vNextPointLoc( vLastPointLoc.x + _segmentLength, vY, vZ );

	return vNextPointLoc;
}

void sfPerlinNoiseBranch::_createSubBranches( sfBranchPoint* vPoint, float vS, int vT )
{
	for( int i = 0; i < vT; i++ )
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
		vBranch->setNumberOfSegments( _subBranchMaxNumberOfSegments * vS );

		vPoint->addBranch( vBranch );
	}

	_subBranches.push_back( vPoint );
}

void sfPerlinNoiseBranch::draw()
{
	_drawBranch();
	_drawSubBranches();
}

//void sfPerlinNoiseBranch::_drawBranch()
//{
//	if( isActive() )
//	{
//		// Draw the lines of this branch.
//		glLineWidth( _thickness );
//		glBegin( GL_LINE_STRIP );
//
//		float vTotal = _points.size();
//		for( unsigned int i = 0; i < vTotal; i++ )
//		{
//			sfBranchPoint* vPoint = _points.at( i );
//			ofxVec3f vPointLoc = vPoint->getLoc();
//
//			// Set the color used when drawing this branch segment.
//			glColor4f( 1, 1, 1, _determineAlpha( i ) );
//
//			// Draw this branch segment.
//			glVertex3f( vPointLoc.x, vPointLoc.y, vPointLoc.z );
//		}
//
//		// Reset colors back to what they were previously.
//		glColor4f( 1, 1, 1, 1 );
//
//		glEnd();
//	}
//}
//
//void sfPerlinNoiseBranch::_drawSubBranches()
//{
//	if( isActive() && _subBranches.size() > 0 )
//	{
//		// Draw any branches that branch off from this one.
//		float vTotal = _points.size();
//		for( unsigned int i = 0; i < vTotal; i++ )
//		{
//			sfBranchPoint* vPoint = _points.at( i );
//
//			if( vPoint->hasBranches() )
//			{
//				// Set the color used when drawing this branch segment.
//				glColor4f( 1, 1, 1, _determineAlpha( i ) );
//
//				ofxVec3f vPointLoc = vPoint->getLoc();
//
//				glPushMatrix();
//				glTranslatef( vPointLoc.x, vPointLoc.y, vPointLoc.z );
//
//				// Draw a dot a branch points.
//				gluSphere( _quadric, _thickness * 6, 10, 10 );
//
//				// Draw any branches at this branch point.
//				vPoint->draw();
//
//				glPopMatrix();
//			}
//		}
//
//		// Reset colors back to what they were previously.
//		glColor4f( 1, 1, 1, 1 );
//	}
//}
//
//float sfPerlinNoiseBranch::_determineAlpha( float vI )
//{
//	return vI / _points.size();
//}
