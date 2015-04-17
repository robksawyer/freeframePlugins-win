/*
 * JuniperStar.h
 *
 *  Created on: Aug 12, 2010
 *      Author: marcwren
 */

#include "ofMain.h"
#include "sfJuniperPoint.h"

#ifndef JUNIPERPOINT_H_
#define JUNIPERPOINT_H_

class sfJuniperStar
{
	public:
		sfJuniperStar();
		~sfJuniperStar();
		/**
		 * Advance the selected point to the next point in the star.
		 */
		void nextPoint();
		/**
		 * Update the state of the star.
		 */
		void update();
		/**
		 * Draw the star to the screen.
		 */
		void draw();
		/**
		 * Hide the star.
		 */
		void hide();
		/**
		 * Determine if the star is currently hidden.
		 * True = The star is not visible.
		 */
		bool isHidden();
		/**
		 * Show the star.
		 */
		void show();
		/**
		 * Move the star to the specified location.
		 * @param x The new x location of the star.
		 * @param y The new y location of the star.
		 * @param z The new z location of the star.
		 */
		void move( float x, float y, float z );
		/**
		 * Set the offset of each point along the x axis
		 * relative to the star's center point.
		 * @param offset The new x offset amount.
		 */
		void setPointXOffset( float offset );
		/**
		 * Set the offset of each point along the y axis
		 * relative to the star's center point.
		 * @param offset The new y offset amount.
		 */
		void setPointYOffset( float offset );
		/**
		 * Set the height of the points in the star.
		 * @param height The new height. The point class
		 * will clamp this so it is at least the same as the point width.
		 */
		void setPointHeight( float height );
		/**
		 * Set the width of the points in the star.
		 */
		void setPointWidth( float width );
		/**
		 * Set the rotation of each point around it's own center.
		 * @param rotation The amount of rotation in degrees to apply (this is not additive).
		 */
		void setPointRotation( float rotation );
		/**
		 * Set the spacing along the z axis between points of the star.
		 */
		void setPointSpacing( float depth );
		/**
		 * Set the number of points in this star.
		 */
		void setNumberOfPoints( int points );
		/**
		 * Specify how long it takes the star to move to its new location
		 * when it changes location.
		 */
		void setMoveSpeed( int speed );
		/**
		 * Get the width of the star.
		 * @return The width of the star.
		 */
		float getDiameter();
		/**
		 * Get the current location of this star.
		 * @return ofxVec3f The location of the star.
		 */
		ofxVec3f getLocation();
		/**
		 * Add points from the star.
		 * @param points The number of points to remove.
		 */
		void addPoints( int points );
		/**
		 * Remove points from the star.
		 * @param points The number of points to remove.
		 */
		void removePoints( unsigned int points );
		/**
		 * Set the currently active point.
		 * @param index The point to set as the current point.
		 */
		void setActivePoint( unsigned int index );
		unsigned int getActivePoint();
		/**
		 * @param sort True = sort points so the active point is in the front.
		 */
		void setSortPoints( bool sort );
	private:
		/**
		 * True = The star is hidden from sight.
		 */
		bool _isHiding;
		/**
		 * The space along the z axis between points in the star.
		 */
		float _pointSpacing;
		/**
		 * True = sort the points so the active points is in front.
		 */
		bool _sortPoints;
		/**
		 * The number of updates it takes to move the star
		 * from its current location to its new location.
		 */
		int _locationChangeDuration;
		/**
		 * The object animating the location of this star.
		 */
		sfAnimatedPoint _location;
		/**
		 * The number of points in this star.
		 */
		int _numberOfPoints;
		/**
		 * The currently highlighted point on the star.
		 */
		unsigned int _activePoint;
		/**
		 * The transparency of the star.
		 */
		float _alpha;
		/**
		 * The width of each point in the star.
		 */
		float _pointWidth;
		/**
		 * The height of each point in the star.
		 */
		float _pointHeight;
		/**
		 * The offset of each point (relative to the point) in the x direction
		 * from the center of the star.
		 */
		float _pointXOffset;
		/**
		 * The offset of each point (relative to the point) in the y direction
		 * from the center of the star.
		 */
		float _pointYOffset;
		/**
		 * The rotation of each point around it's own center.
		 */
		float _pointRotation;
		/**
		 * The list of points on this star.
		 */
		vector<sfJuniperPoint*> _points;
		/**
		 * Create a new star and add it to the list of stars.
		 * @param index The index at which to add the point.
		 * @param rotation The initial rotation from which this point will show itself.
		 */
		void _createPoint( int index, int rotation );
		/**
		 * Distribute the points of the star evenly.
		 */
		void _distributePoints();
		/**
		 * True = The point sorting/spacing is invalid and needs to be adjusted on
		 * the next update call.
		 */
		bool _pointsRequireSorting;
};

#endif /* JUNIPERPOINT_H_ */
