/*
 * sfBranchPoint.h
 *
 *  Created on: Sep 30, 2010
 *      Author: marc.wren
 */

#ifndef SFBRANCHPOINT_H_
#define SFBRANCHPOINT_H_

#include "ofxVec3f.h"
#include "sfBranch.h"

class sfBranch;

class sfBranchPoint
{
	public:
		sfBranchPoint();
		~sfBranchPoint();
		/**
		 * Set the location of this point.
		 */
		void setLoc( float x, float y, float z );
		/**
		 * Get the current location of this point.
		 */
		ofxVec3f getLoc();
		/**
		 * Adds a branch to this branch point.
		 */
		void addBranch( sfBranch* branch );
		/**
		 * True = additiona branches grow out of this branch point.
		 */
		bool hasBranches();
		/**
		 * Update all branches (if any) at this point.
		 */
		void update();
		/**
		 * Draws all of the branches (if any) at this point.
		 */
		void draw();
	private:
		/**
		 * True = additiona branches grow out of this branch point.
		 */
		bool _hasBranches;
		/**
		 * The location at which this point exists.
		 */
		ofxVec3f _loc;
		/**
		 * The branches (if any) that grow out of this point.
		 */
		vector<sfBranch*> _branches;
};

#endif /* SFBRANCHPOINT_H_ */
