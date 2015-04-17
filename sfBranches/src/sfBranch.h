/*
 * sfBranch.h
 *
 *  Created on: Sep 30, 2010
 *      Author: marc.wren
 */

#ifndef SFBRANCH_H_
#define SFBRANCH_H_

#include "ofxVec3f.h"
#include "sfBranchPoint.h"
#include "ofxPerlin.h"

class sfBranchPoint;

class sfBranch
{
	public:
		sfBranch();
		~sfBranch();
		/**
		 * Update the size of this branch and any sub-branches.
		 */
		void update();
		/**
		 * Draws the current state of the branch.
		 */
		virtual void draw();
		/**
		 * Set the thickness of this branch.
		 */
		void setThickness( float thickness );
		/**
		 * Set the number of segments that will make up this branch.
		 */
		void setNumberOfSegments( unsigned int number );
		/**
		 * Set the length of each segment in this branch.
		 */
		void setSegmentLength( float length );
		/**
		 * Set the probability (as a percentage) that this branch will
		 * create sub-branches.
		 */
		void setBranchProbability( float probability );
		/**
		 * Get the angle of rotation along the Y axis at which this branch grows.
		 */
		float getRotationY();
		/**
		 * Get the angle of rotation along on the Z axis at which this branch grows.
		 */
		float getRotationZ();
		/**
		 * Set the angle of rotation in degrees along the Y axis at which this branch grows.
		 */
		void setRotationY( float rotationY );
		/**
		 * Set the angle of rotation in degrees along the Z axis at which this branch grows.
		 */
		void setRotationZ( float rotationZ );
		/**
		 * Get the begining of the branch (ie. the oldest point).
		 */
		ofxVec3f getStart();
		/**
		 * Get the end of the branch (ie. the newest point).
		 */
		ofxVec3f getEnd();
		/**
		 * True = this branch is growing.
		 */
		Boolean isActive();
		/**
		 * Create new branches at the tip of the branch.
		 */
		void branch();
		/**
		 * Create new branches at the tip of the branch but specify how strong/fast
		 * those branches are.
		 * @param strength Will be used to affect how long branches are and how
		 * probable it will be that they create their own sub-branches.
		 */
		void branch( float strength );
		/**
		 * Create new branches at the tip of the branch and specify both the strength
		 * of sub-branches and the total number.
		 * @param strength Will be used to affect how long branches are and how
		 * probable it will be that they create their own sub-branches.
		 * @param total The total number of branches to create at this point.
		 */
		void branch( float strength, int total );
		/**
		 * Set whether or not this branch branches in 3 dimensions.
		 */
		void setIs3D( Boolean vIs3D );
	protected:
		/**
		 * True = Branches are drawn in 3 dimensions.
		 */
		Boolean _is3D;
		/**
		 * True = this branch is a growing branch.
		 */
		Boolean _active;
		/**
		 * True = this branch will continue to grow after it has
		 * created _numberOfSegments and old points will be
		 * removed from the branch in order to keep the number
		 * of segments equal to _numberOfSegments.
		 */
		Boolean _continuousGrowth;
		/**
		 * The thickness of this branch.
		 */
		float _thickness;
		/**
		 * The factor by which the thickness of branches is reduced
		 * in sub-branches.
		 */
		float _subBranchThicknessFactor;
		/**
		 * The angle in degrees along the Y axis that this branch shoots off the
		 * parent branch. This property rotates the branch as a whole.
		 */
		float _rotationY;
		/**
		 * The angle in degrees along the Z axis that this branch grows from
		 * the parent branch. This property rotates the branch as a whole.
		 */
		float _rotationZ;
		/**
		 * The maximum rotation at which branches can grow out of their parent branch.
		 * For example, if set to 90, then sub branches will grow from their parent branch
		 * at an angle between 90 and -90 degrees.
		 */
		float _maxInitialRotation;
		/**
		 * The direction (in degrees) along the y axis in which
		 * new branch points are added.
		 * This property affects where the next branch point will
		 * be placed.
		 */
		float _directionY;
		/**
		 * The direction (in degrees) along the z axis which new
		 * branch points are added.
		 */
		float _directionZ;
		/**
		 * The maximum amount by which the direction of the branch
		 * will change each time a new branch point is added.
		 */
		float _directionMultiplier;
		/**
		 * The number of branch points created by this branch.
		 */
		unsigned int _numberOfPointsCreated;
		/**
		 * The distance between points on the branch.
		 */
		float _segmentLength;
		/**
		 * The number of segments in the branch (ie. number
		 * of points - 1).
		 */
		unsigned int _numberOfSegments;
		/**
		 * The list of points on the branch.
		 */
		vector<sfBranchPoint*> _points;
		/**
		 * The list of points on this branch that contain sub-branches.
		 */
		vector<sfBranchPoint*> _subBranches;
		/**
		 * The probability (0-100) that a new branch will be created at
		 * a new branch point.
		 */
		float _newBranchProbability;
		/**
		 * The _newBranchProbability used by any subBranches of this branch.
		 * Setting this to 0 means that any subBranches of this branch will not
		 * create branches.
		 */
		float _subBranchProbability;
		/**
		 * The amount by which the _subBranchProbability is reduced with each
		 * generation of subBranches. Setting this to 0 means that each generation
		 * of branches has the same probability of branching as it's parent.
		 */
		float _subBranchProbabilitySubtractor;
		/**
		 * The maximum number of subBranches that can be generated at any point.
		 */
		int _maxSubBranchesPerPoint;
		/**
		 * The object used to draw circles.
		 */
		GLUquadric* _quadric;
		/**
		 * Activate this branch so that it starts growing.
		 */
		void _activate();
		/**
		 * Draws this branch.
		 */
		void _drawBranch();
		/**
		 * Draws any branches that grow out of this branch.
		 */
		void _drawSubBranches();
		/**
		 * Start this branch growing.
		 */
		void _addBranchPoint();
		/**
		 * Create the sub-branches at a branch point.
		 * @param branchPoint The point to which sub-branches will be added.
		 */
		virtual void _createSubBranches( sfBranchPoint* branchPoint );
		/**
		 * Create the sub-branches at a branch point.
		 * @param branchPoint The point to which sub-branches will be added.
		 * @param strength The strength of the new branches (ie. how fast do they grow
		 * and are they more likely to create sub-branches of their own?).
		 * @param total The total number of branches to create at this point.
		 */
		virtual void _createSubBranches( sfBranchPoint* branchPoint, float strength, int total );
		/**
		 * Remove the oldest branch points if we have exceeded
		 * _numberOfSegments.
		 */
		void _removeOldBranchPoints();
		/**
		 * Update all sub-branches of this branch.
		 */
		void _updateSubBranches();
		/**
		 * Determine the location of the next point on the branch.
		 */
		virtual ofxVec3f _createNewPointLoc();
};

#endif /* SFBRANCH_H_ */
