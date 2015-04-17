/*
 * sfJuniperPoint.h
 *
 *  Created on: Aug 25, 2010
 *      Author: marc.wren
 */

#ifndef SFJUNIPERPOINT_H_
#define SFJUNIPERPOINT_H_

#include "sfAnimatedPoint.h"
#include "sfCirclePoint.h"

class sfJuniperPoint
{
	public:
		/**
		 * Debug name of this point.
		 */
		int index;
		/**
		 * Create the point using the default shape.
		 */
		sfJuniperPoint();
		/**
		 * Create the point at a specific starting rotation.
		 */
		sfJuniperPoint( float rotation );
		/**
		 * Set the rotation amount of this point around the star's center.
		 */
		void setRotation( float rotation );
		/**
		 * Set the rotation of this point around the point's center.
		 */
		void setSubRotation( float rotation );
		/**
		 * Set the x and y offset from the point's origin.
		 */
		void setOffset( float x, float y );
		/**
		 * Set the offset along the x axis.
		 */
		void setXOffset( float x );
		/**
		 * Set the offset along the x axis.
		 */
		void setYOffset( float y );
		/**
		 * Set the point's location on the z-axis.
		 */
		void setZLocation( float z );
		/**
		 * Set the height of the point. This will be clamped
		 * such that the point is at least a circle.
		 */
		void setHeight( float height );
		/**
		 * Set the width of the point.
		 */
		void setWidth( float width );
		/**
		 * Set the transparency value of this point.
		 */
		void setAlpha( float alpha );
		/**
		 * Set the highlight color of this point.
		 */
		void setHighlightColor( int color );
		/**
		 * Set this point as active (ie. animate it into its highlighted
		 * position).
		 */
		void activate();
		/**
		 * Set this point as inactive (ie. animate it into its
		 * unhighlighted position).
		 */
		void deactivate();
		/**
		 * Animates the point into its closed position.
		 */
		void hide();
		/**
		 * Determine if this point is completely hidden.
		 * @return True = The point has completed its hide animation.
		 */
		bool isHidden();
		/**
		 * Animates the point into its open position.
		 */
		void show();
		/**
		 * Update the current color of the point.
		 */
		void update();
		/**
		 * Draw the point to the screen.
		 */
		void draw();
	private:
		/**
		 * Initialize this instance.
		 */
		void _init();
		/**
		 * True = This point is currently active.
		 */
		bool _isActive;
		/**
		 * The offset of the point from its original x position.
		 */
		float _xOffset;
		/**
		 * The offset of the point from its original y position.
		 */
		float _yOffset;
		/**
		 * The height of the point.
		 */
		float _height;
		/**
		 * The width of the point.
		 */
		float _width;
		/**
		 * The alpha value of this point.
		 */
		float _alpha;
		/**
		 * The alpha value of this point when it is active.
		 */
		float _activeAlphaMultiplier;
		/**
		 * The object animating the point's alpha value.
		 */
		sfAnimatedPoint _alphaAnimator;
		/**
		 * The color that the point will be when it is highlighted.
		 */
		int _activatedColor;
		/**
		 * The duration that the activate animation will last.
		 */
		int _activateAnimationDuration;
		/**
		 * The duration that the deactivate animation will last.
		 */
		int _deactivateAnimationDuration;
		/**
		 * The duration that it takes to show the point (ie. rotate it into position).
		 */
		int _showAnimationDuration;
		/**
		 * The amount of time it takes to hide the point( ie. rotate it to the 0 rotation).
		 */
		int _hideAnimationDuration;
		/**
		 * The color that the point will be most of the time.
		 */
		int _deactivatedColor;
		/**
		 * The color of the point.
		 */
		sfAnimatedPoint _colorAnimator;
		/**
		 * The point used to define the rotation of this point around the star's center.
		 */
		float _rotation;
		/**
		 * The starting rotation of the point used when fist showing the point.
		 */
		float _initialRotation;
		/**
		 * Determines how this point will be rotated around the point's center.
		 */
		float _subRotation;
		/**
		 * The object animating the point's rotation.
		 */
		sfAnimatedPoint _rotationAnimator;
		/**
		 * The object animating the point's location.
		 */
		sfAnimatedPoint _locationAnimator;
		/**
		 * The amount of time it takes the points to move to their new locations.
		 */
		int _locationAnimationDuration;
		/**
		 * The object used to draw the shape of the point.
		 */
		sfCirclePoint _renderer;
		/**
		 * True = The point is in the process of hiding itself.
		 */
		bool _hidden;
};

#endif /* SFJUNIPERPOINT_H_ */
