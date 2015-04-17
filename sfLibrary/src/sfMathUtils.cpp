/*
 * MathUtils.cpp
 *
 *  Created on: Jul 19, 2010
 *      Author: marcwren
 */

#include <math.h>
#include "ofMain.h"
#include "sfMathUtils.h"

int sfMathUtils::LAST_POSITIVE_OR_NEGATIVE_HALF_ROUND = 1;

sfMathUtils::sfMathUtils()
{

}

int sfMathUtils::positiveOrNegative()
{
	// TODO Does this return one value more often than the other?
	// Could write a test to verify.
//	return random() % 2 ? -1: 1;

	// Generate a number between 0 and 1.
	float vNum = ofRandomuf();

	// If we rounded to the exact center, alternate
	// whether or not we go netagive or positive.
	if( vNum == 0.5 )
	{
		if( sfMathUtils::LAST_POSITIVE_OR_NEGATIVE_HALF_ROUND == 1 )
		{
			vNum = -1;
			sfMathUtils::LAST_POSITIVE_OR_NEGATIVE_HALF_ROUND = vNum;
		}
		else
		{
			vNum = 1;
			sfMathUtils::LAST_POSITIVE_OR_NEGATIVE_HALF_ROUND = vNum;
		}
	}
	else
	{
		vNum = round( vNum );
	}

	// Now that we have 1 or 0, convert 0s to -1s.
	if( vNum == 0 )
	{
		vNum = -1;
	}

	return vNum;
}

float sfMathUtils::round( float vValue )
{
  return floor(vValue + 0.5);
}

ofxVec3f sfMathUtils::randomPointWithinSphere( float vOuterR, float vInnerR )
{
	// TODO Factor in inner radius value. Not sure how to do that yet.
	long int r = vOuterR;
	long int aux;

	float z = (int)(positiveOrNegative() * ofRandomuf()) % r;
	aux = r*r - z*z;
	float x = (int)(positiveOrNegative() * ofRandomuf()) % ((int) sqrt( (float)aux));
	aux -= x*x;
	float y = (int)(positiveOrNegative() * ofRandomuf()) % ((int) sqrt( (float)aux));
	
//	float z = positiveOrNegative() * random() % r;
//	aux = r*r - z*z;
//	float x = positiveOrNegative() * random() % ((int) sqrt(aux));
//	aux -= x*x;
//	float y = positiveOrNegative() * random() % ((int) sqrt(aux));

	ofxVec3f vOut( x, y, z );
	return vOut;

	// The following is supposed to be faster but I haven't been able to get it to work.
//	int x, y, z;
//	int r = (int)vOuterR;
//	do
//	{
//		x = ofRandom( -vOuterR, vOuterR );
//		y = ofRandom( -vOuterR, vOuterR );
//		z = ofRandom( -vOuterR, vOuterR );
//		ofxVec3f vOut = ofxVec3f( x, y, z );
//	} while( x^2 + y^2 + z^2 > r^2 );
//
//	return ofxVec3f( x, y, z );
}

ofxVec3f sfMathUtils::randomPointWithinSphere( float vR )
{
	return randomPointWithinSphere( vR, 0 );
}
