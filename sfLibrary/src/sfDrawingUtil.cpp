/*
 * sfDrawingUtil.cpp
 *
 *  Created on: Aug 23, 2010
 *      Author: marc.wren
 */


#include "sfDrawingUtil.h"
#include "ofMain.h"
#include <math.h>


void sfDrawingUtil::circleVerticies( int vX, int vY, float vR )
{
	// Determin the multiplier for our bezier control points.
	float vKappa = 4 * ( (sqrtf(2) - 1)/3 );
	float vK = vKappa * vR;

	ofVertex( vX - vR, vY );
	ofBezierVertex( vX - vR, vY - vK, vX - vK, vY - vR, vX, vY - vR );
	ofBezierVertex( vX + vK, vY - vR, vX + vR, vY - vK, vX + vR, vY );
	ofBezierVertex( vX + vR, vY + vK, vX + vK, vY + vR, vX, vY + vR );
	ofBezierVertex( vX - vK, vY + vR, vX - vR, vY + vK, vX - vR, vY );
}

void sfDrawingUtil::drawRing( int vX, int vY, float vOR, float vIR )
{
	// TODO This could be implemented using gluDisk.
	// Reset the drawing location to the center of the circle we want to draw.
	ofPushMatrix();
	ofTranslate( vX, vY, 0 );
	vX = vY = 0;

	// Begin our shape.
	ofBeginShape();

	circleVerticies( vX, vY, vOR );
	circleVerticies( vX, vY, vIR );

	// End our shape.
	ofEndShape();

	// Reset the drawing head to it's initial state.
	ofPopMatrix();
}

int sfDrawingUtil::rgbToHex( int vR, int vG, int vB )
{
	return vR << 16 | vG << 8 | vB;
}

int sfDrawingUtil::getHexRedValue( int vH )
{
	return vH >> 16 & 0xFF;
}

int sfDrawingUtil::getHexGreenValue( int vH )
{
	return vH >> 8 & 0xFF;
}

int sfDrawingUtil::getHexBlueValue( int vH )
{
	return vH & 0xFF;
}

int sfDrawingUtil::blendHex(  int vC1, int vC2, float vAmount )
{
	// TODO Make sure vAmount is between 0 and 1.
	float vR = vAmount * (float)getHexRedValue( vC2 ) + (1 - vAmount) * (float)getHexRedValue( vC1 );
	float vG = vAmount * (float)getHexGreenValue( vC2 ) + (1 - vAmount) * (float)getHexGreenValue( vC1 );
	float vB = vAmount * (float)getHexBlueValue( vC2 ) + (1 - vAmount) * (float)getHexBlueValue( vC1 );

	// Convert rgb back to a hex value.
	return rgbToHex( vR, vG, vB );
}

vector<int> sfDrawingUtil::colorWheel( int vPoints )
{
//	int* vReturn = new int[ vPoints ];
	vector<int> vReturn;

	for( int i = 0; i < vPoints; i++ )
	{
		float vColorPercent = (float)i / (float)vPoints;

		float vRadians = ( -360 * vColorPercent ) * ( PI / 180 );

		int vR = (int)(cos( vRadians ) * 127 + 128) << 16;
		int vG = (int)(cos( vRadians + 2 * PI / 3 ) * 127 + 128) << 8;
		int vB = (int)(cos( vRadians + 4 * PI / 3 ) * 127 + 128);

		int vColor = vR | vG | vB;

//		vReturn[i] = vColor;
		vReturn.push_back( vColor );
	}

	return vReturn;
}

void sfDrawingUtil::renderCylinder( ofxVec3f vStart, ofxVec3f vEnd, float vR, int vStacks, GLUquadricObj * vQ )
{
	renderCylinder( vStart.x, vStart.y, vStart.z, vEnd.x, vEnd.y, vEnd.z, vR, vStacks, vQ );
}

void sfDrawingUtil::renderCylinder( float x1, float y1, float z1, float x2, float y2, float z2, float radius, int subdivisions, GLUquadricObj *quadric )
{
	float vx = x2 - x1;
	float vy = y2 - y1;
	float vz = z2 - z1;

	//handle the degenerate case of z1 == z2 with an approximation
	if( vz == 0 )
		vz = .0001;

	float v = sqrt( vx * vx + vy * vy + vz * vz );
	float ax = 57.2957795 * acos( vz / v );
	if( vz < 0.0 )
		ax = -ax;
	float rx = -vy * vz;
	float ry = vx * vz;
	glPushMatrix();

	//draw the cylinder body
	glTranslatef( x1, y1, z1 );
	glRotatef( ax, rx, ry, 0.0 );
	gluQuadricOrientation( quadric, GLU_OUTSIDE );
	gluCylinder( quadric, radius, radius, v, subdivisions, 1 );

	//draw the first cap
	gluQuadricOrientation( quadric, GLU_INSIDE );
	gluDisk( quadric, 0.0, radius, subdivisions, 1 );
	glTranslatef( 0, 0, v );

	//draw the second cap
	gluQuadricOrientation( quadric, GLU_OUTSIDE );
	gluDisk( quadric, 0.0, radius, subdivisions, 1 );
	glPopMatrix();
}
/*
void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
  //the same quadric can be re-used for drawing many cylinders
  GLUquadricObj *quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
  gluDeleteQuadric(quadric);
}
*/
