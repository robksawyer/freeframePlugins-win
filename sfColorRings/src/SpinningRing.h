/*
 *  SpinningRing.h
 *  Creates a ring that rotates around it's z axis. You can specify 
 *  an offset so that the rotation causes it to "wobble" as the rotation
 *  point will not be the center of the circle.
 *
 *  Created by Marc Wren  on 5/20/10.
 *  Copyright 2010 Soul-Fresh. All rights reserved.
 *
 */
#ifndef _SF_SPINNING_RING
#define _SF_SPINNING_RING

class SpinningRing 
{
public:
	/**
	 * Create a default spinning ring with all properties other than 
	 * inner and outer diameters set to 0.
	 */
	SpinningRing();
	/**
	 * Create a default spinning ring.
	 * @param x The x location of the center of the ring.
	 * @param y The y location of the center of the ring.
	 * @param z The z location of the center of the ring.
	 * @param outerDiameter The outer diameter of the ring.
	 * @param innerDiameter The inner diameter of the ring.
	 * @param color The color of the ring.
	 */
	SpinningRing( int x, int y, int z, int outerDiameter, int innerDiameter, int color );
	/**
	 * Create a spinning ring, also specifying an x and y offset from the center point 
	 * so that the ring does not spin in a perfect circle.
	 * @param x The x location of the center of the ring.
	 * @param y The y location of the center of the ring.
	 * @param z The z location of the center of the ring.
	 * @param outerDiameter The outer diameter of the ring.
	 * @param innerDiameter The inner diameter of the ring.
	 * @param color The color of the ring.
	 * @param offsetX The x offset of the ring from it's center.
	 * @param offsetY The y offset of the ring from it's center.
	 */
	SpinningRing( int x, int y, int z, int outerDiameter, int innerDiameter, int color, int offsetX, int offsetY );
	/**
	 * Draw the ring to the screen.
	 */
	void draw();
	/**
	 * Update the state of the ring each frame.
	 */
	void update();
	/**
	 * Update the x location of the ring.
	 */
	void setX( int x );
	/**
	 * Get the current x location of the ring.
	 */
	int getX();
	/**
	 * Update the y location of the ring.
	 */
	void setY( int y );
	/**
	 * Get the current y location of the ring.
	 */
	int getY();
	/**
	 * Update the z location of the ring.
	 */
	void setZ( int z );
	/**
	 * Get the current z location of the ring.
	 */
	int getZ();
	/**
	 * Update the x offset of the ring from it's center.
	 */
	void setXOffset( int offset );
	/**
	 * Update the y offset of the ring from it's center.
	 */
	void setYOffset( int offset );
	/**
	 * Update the offset factor for this ring.
	 */
	void setOffsetFactor( int factor );
	/**
	 * Update the inner diameter of the ring.
	 */
	void setInnerDiameter( int innerDiameter );
	/**
	 * Update the outer diameter of the ring.
	 */
	void setOuterDiameter( int outerDiameter );
	/**
	 * Update the color of the ring.
	 */
	void setColor( int color );
	/**
	 * Update the color of the ring using rgba values.
	 * @param r 
	 * @param g
	 * @param b
	 * @param a The alpha value.
	 */
	void setColor( int r, int g, int b, int a );
	/**
	 * Update the current rotation of the ring around it's 
	 * X-axis.
	 * @param rotation The new rotation of the ring.
	 */
	void setXRotation( int rotation );
	/**
	 * Update the current rotation of the ring around it's 
	 * Y-axis.
	 * @param rotation The new rotation of the ring.
	 */
	void setYRotation( int rotation );
	/**
	 * Update the current rotation of the ring around it's 
	 * Z-axis.
	 * @param rotation The new rotation of the ring.
	 */
	void setZRotation( int rotation );
	/**
	 * Set the speed in degrees at which the ring will spin
	 * around its center.
	 */
	void setZRotationSpeed( int speed );

private:
	/**
	 * Reset all values of the ring.
	 * @param x The x location of the center of the ring.
	 * @param y The y location of the center of the ring.
	 * @param z The z location of the center of the ring.
	 * @param outerDiameter The outer diameter of the ring.
	 * @param innerDiameter The inner diameter of the ring.
	 * @param color The color of the ring.
	 * @param offsetX The x offset of the ring from it's center.
	 * @param offsetY The y offset of the ring from it's center.
	 * @param rotation The rotation of the ring around it's z axis.
	 */
	void _init( int x, int y, int z, int outerDiameter, int innerDiameter, int color, int offsetX, int offsetY, int xRotation, int yRotation, int zRotation );
	/**
	 * Make sure rotation values are between 0-360. If they
	 * are not, increase or decrease them by 360 until they
	 * are withing the correct range.
	 * @param rotation The rotation to constrain.
	 */
	int _constrainRotation( int rotation );
	int _color;
	int _r;
	int _g;
	int _b;
	int _alpha;
	int _x;
	int _y;
	int _z;
	int _innerDiameter;
	int _outerDiameter;
	int _offsetX;
	int _offsetY;
	/**
	 * The factor by which the x and y offset will be multiplied.
	 * Modifying the offset factor, allows rings to become more/less
	 * offset from each other and the center.
	 */
	int _offsetFactor;
	int _xRotation;
	int _yRotation;
	int _zRotation;
	/**
	 * The speed in degrees at which the ring will rotate around
	 * it's center.
	 */
	int _zRotationSpeed;
};

#endif
