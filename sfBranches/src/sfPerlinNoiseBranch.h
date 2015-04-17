/*
 * sfPerlinNoiseBranch.h
 *
 *  Created on: Oct 5, 2010
 *      Author: marc.wren
 */

#ifndef SFMAINBRANCH_H_
#define SFMAINBRANCH_H_

#include "ofxVec3f.h"
#include "sfBranchPoint.h"
#include "sfBranch.h"
#include "ofxPerlin.h"

class sfPerlinNoiseBranch: public sfBranch
{
	public:
		sfPerlinNoiseBranch();
		/**
		 * Draws the current state of the branch.
		 */
		virtual void draw();
	protected:
		/**
		 * The object used to determine perlin noise.
		 * TODO How can we reuse this noise object between branch instances?
		 * We're probably going to have to pass a pointer. Maybe create an sfBranchMain
		 * class which is responsible for creating the perlin noise object and any other
		 * resources that need to be shared between the branch objects.
		 */
		ofxPerlin _noise;
		/**
		 * The amount by which the perlin noise will be mutliplied.
		 * This has the effect of making the branch more or less wavy.
		 */
		float _noiseMultiplier;
		/**
		 * The number of segments that sub branches start at.
		 */
		int _subBranchMaxNumberOfSegments;
		/**
		 * Determine the location of the next point on the branch.
		 */
		virtual ofxVec3f _createNewPointLoc();
//		/**
//		 * Override the default branch drawing.
//		 */
//		void _drawBranch();
//		/**
//		 * Override the default sub-branch drawing behaviour.
//		 */
//		void _drawSubBranches();
//		/**
//		 * Determine the alpha value to use at a particular branch index.
//		 */
//		float _determineAlpha( float index );
		/**
		 * Create the sub-branches at a branch point. Overrides sfBranch version in order
		 * to control sub-branching.
		 */
		virtual void _createSubBranches( sfBranchPoint* branchPoint, float strength, int total );
};

#endif /* SFMAINBRANCH_H_ */
