/*
 * sfBranchPoint.cpp
 *
 *  Created on: Sep 30, 2010
 *      Author: marc.wren
 */

#include "sfBranchPoint.h"

sfBranchPoint::sfBranchPoint()
{
	_hasBranches = false;
}

sfBranchPoint::~sfBranchPoint()
{
	if( !_branches.empty() )
	{
		for( vector<sfBranch*>::iterator i = _branches.begin(); i < _branches.end(); ++i )
		{
			delete *i;
		}

		_branches.clear();
	}
}

void sfBranchPoint::setLoc( float vX, float vY, float vZ )
{
	_loc = ofxVec3f( vX, vY, vZ );
}

ofxVec3f sfBranchPoint::getLoc()
{
	return _loc;
}

void sfBranchPoint::addBranch( sfBranch* vBranch )
{
	_branches.push_back( vBranch );
	_hasBranches = true;
}

bool sfBranchPoint::hasBranches()
{
	return _hasBranches;
}

void sfBranchPoint::update()
{
	for( unsigned int i = 0; i < _branches.size(); i++ )
	{
		_branches.at(i)->update();
	}
}

void sfBranchPoint::draw()
{
	for( unsigned int i = 0; i < _branches.size(); i++ )
	{
		sfBranch* vBranch = _branches.at(i);
		if( vBranch->isActive() )
		{
			vBranch->draw();
		}
	}
}
