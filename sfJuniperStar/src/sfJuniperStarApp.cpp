#include "sfJuniperStarApp.h"
#include "ofMain.h"
#include "ofxFFGLPlugin.h"
//#include "ofxLight.h"
#include "sfCamera.h"
#include <algorithm>

sfJuniperStarApp::sfJuniperStarApp()
{
	// Add FFGL parameters
	_rotation = 0;
	addFloatParameter( "Rotation", &_rotation, -90, 90 );

	_zoom = 1000;
	addFloatParameter( "Zoom", &_zoom, 0, 2000 );

	_numberOfStars = 4;
	addFloatParameter( "Stars", &_numberOfStars, 1.0f, 25.0f );

	_starMoveDuration = 15;
	addFloatParameter( "Star Move Speed", &_starMoveDuration, 1.0f, 50.0f );

	_starMoveDistance = 500;
	addFloatParameter( "Star Move Dist", &_starMoveDistance, 0, 1000 );

	_numberOfPoints = 8;
	addFloatParameter( "Points", &_numberOfPoints, 3.0f, 25.0f );

	_pointXOffset = 0;
//	addFloatParameter( "Point X Offset", &_pointXOffset, -100, 100 );

	_pointYOffset = 100;
	addFloatParameter( "Point Y Offset", &_pointYOffset, 0, 200 );

	_pointHeight = 25;
	addFloatParameter( "Point Height", &_pointHeight, 10, 300 );

	_pointWidth = 25;
	addFloatParameter( "Point Width", &_pointWidth, 10, 300 );

	_pointRotation = 30;
	addFloatParameter( "Point Rotation", &_pointRotation, 0, 360 );

	_starDepthFactor = 50;
	addFloatParameter( "Point Depth", &_starDepthFactor, 0.0f, 500.0f );

	_sortPoints = true;
	addBoolParameter( "Bring To Front", &_sortPoints );

	_beat.setLoopSize( _numberOfPoints );
	addBeatEventParameter( "Event: Next", &_beatEventTracker );

	_moveEventTracker.setFramesPerBeat( 150 );
	addBeatEventParameter( "Event: Move", &_moveEventTracker );

	// TODO There seems to be a bug where if the number of points is reduced to just a few points around
	// the same time the active point changes from the first to the last point, the star is removed and a new one
	// is created (or the star suddenly changes in some way that looks like a new point being created).
	// TODO Make it possible to align stars in regular patterns (concentric circles, spriral, squares, tiles).
	// TODO When rotating the camera, drawing transparent areas back to front doesn't work when the camera rotation
	// means that objects in the back are actually in the front. Need to find a way to resolve this. Could determine
	// the distance of each drawable object to the camera. Could just flip the sorting algorithm when the camera rotation
	// is between 90 and 180 degrees. Might need to implement a drawable interface that allows object to return a list
	// of objects to draw. These could then be sorted by distance from the camera and drawn.

	// FOR sfJuniperSpiral
	// TODO Add the ability to specify point rotation range so that points can be laid out on a half circle and so forth.
	// TODO Add the ability to disable active point tracking.
}

void sfJuniperStarApp::setup()
{
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 30 );
	ofSetVerticalSync( true );
	// TODO Only do this if we are in a test application.
	ofSetWindowPosition( 2000, 600);
//	ofSetWindowPosition( 0, 1000);

	camera = sfCamera();
	camera.focalPoint( 0, 0, 0 );
	camera.location( 0, 0, 1000 );

	// Configure the stars.
	for ( int i=0; i< _numberOfStars; i++ )
	{
		_createStar();
	}
	moveStars();
}


void sfJuniperStarApp::preIterate()
{
	_beatEventTracker.setStandalone( true );
	_moveEventTracker.setStandalone( true );

	if( ofGetFrameNum() % 160 == 0 && ofGetFrameNum() > 1 )
	{
		_numberOfPoints = 4;
	}

	if( ofGetFrameNum() % 180 == 0 && ofGetFrameNum() > 1 )
	{
		_pointWidth = 150;
	}

	if( ofGetFrameNum() % 200 == 0 && ofGetFrameNum() > 1 )
	{
		_pointHeight = 250;
	}

	if( ofGetFrameNum() % 220 == 0 && ofGetFrameNum() > 1 )
	{
		_numberOfPoints = 8;
	}
//		_numberOfStars = ofRandom( 1, 4 );
//		_pointYOffset = ofRandom( 0, 200 );
//		_pointWidth = ofRandom( 10, 300 );
//		_pointHeight = ofRandom( 10, 300 );
//		_pointRotation = ofRandom( 0, 360 );
//		_starDepthFactor = ofRandom( 0, 100 );
//	}
//	_rotation += 1;
//	if( _rotation >= 90 )
//	{
//		_rotation = -90;
//	}
}

void sfJuniperStarApp::iterate()
{
	_removeOldStars();

	_beat.setLoopSize( _numberOfPoints );

	_setNumberOfStars( (int)_numberOfStars );

	// Each time the beat parameter cycles, we consider this a beat.
	if( _beatEventTracker.isBeatEvent() )
	{
		beatEvent();
	}
	_beatEventTracker.update();

	if( _moveEventTracker.isBeatEvent() )
	{
		moveStars();
	}
	_moveEventTracker.update();

	// Update the information about each star.
	for( unsigned int j = 0; j < _stars.size(); j++ )
	{
		_updateStar( _stars.at(j) );
		_stars.at(j)->update();
	}

	// Sort all of the stars.
	sort( _stars.begin(), _stars.end(), _compareStarLocations );

	// Update camera location.
	ofxVec3f vCameraLoc = camera.getLocation();
	vCameraLoc.z = _zoom;
	vCameraLoc.x = 0;
	vCameraLoc.y = 0;
	camera.location( vCameraLoc );
	ofxVec3f vAxis = ofxVec3f( 0, 1, 0 );
	camera.orbitAround( camera.getFocalPoint(), vAxis, _rotation );
}

void sfJuniperStarApp::postIterate()
{

}

void sfJuniperStarApp::_createStar()
{
	sfJuniperStar* vStar = new sfJuniperStar();
	_updateStar( vStar );
	vStar->show();

	_moveStar( vStar );

	_stars.push_back( vStar );
}

void sfJuniperStarApp::_updateStar( sfJuniperStar* vStar )
{
	vStar->setNumberOfPoints( (int)_numberOfPoints );
	vStar->setPointSpacing( _starDepthFactor );
	vStar->setPointYOffset( _pointYOffset );
	vStar->setPointRotation( _pointRotation );
	vStar->setPointHeight( _pointHeight );
	vStar->setPointWidth( _pointWidth );
	vStar->setMoveSpeed( (int)_starMoveDuration );
	vStar->setSortPoints( _sortPoints );
	vStar->setActivePoint( _beat.getCurrentIndex() );
}

void sfJuniperStarApp::moveStars()
{
	for( unsigned int k = 0; k < _stars.size(); k++ )
	{
//		_stars.at(k)->move( k * 300, 0, -400 );
		_moveStar( _stars.at(k) );
	}
}

void sfJuniperStarApp::_moveStar( sfJuniperStar* vStar )
{
	vStar->move( ofRandom( -_starMoveDistance, _starMoveDistance ), ofRandom( -_starMoveDistance, _starMoveDistance ), ofRandom( 0, _starMoveDistance ) );
}

void sfJuniperStarApp::_setNumberOfStars( unsigned int vNum )
{
	int vDiff = vNum - _stars.size();
	if( vDiff > 0 )
	{
		_addStars( vDiff );
	}
	else if( vDiff < 0 )
	{
		_hideStars( -vDiff );
	}
}

void sfJuniperStarApp::_addStars( unsigned int vNum )
{
	for( unsigned int i = 0; i < vNum; i++ )
	{
		_createStar();
	}

	// TODO Temporary
//	moveStars();
}

void sfJuniperStarApp::_hideStars( unsigned int vNum )
{
	for( unsigned int i = 0; i < vNum; i++ )
	{
		_stars.at(i)->hide();
	}
}

void sfJuniperStarApp::_removeOldStars()
{
	for( vector<sfJuniperStar*>::iterator it = _stars.begin(); it < _stars.end(); it++ )
	{
		sfJuniperStar* vStar = *it;
		if( vStar->isHidden() )
		{
			delete vStar;
			_stars.erase( it );
		}
	}
}

void sfJuniperStarApp::beatEvent()
{
	_beat.update();

	for( unsigned int i = 0; i < _stars.size(); i++ )
	{
		_stars.at(i)->nextPoint();
	}
}

void sfJuniperStarApp::draw()
{
	glEnable( GL_BLEND );
//	glDepthMask( GL_TRUE );
//	glEnable( GL_DEPTH_TEST );
//	glEnable( GL_ALPHA_TEST ); // TODO Not sure if we need this.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	camera.place();

//	ofCircle( 0, 0, 50 );
//	ofxVec3f vLL = camera.getViewportLowerLeft();
//	ofDrawBitmapString( "Lower Left Corner: " + ofToString( vLL.x ) + ", " + ofToString( vLL.y ), 0, -25 );
//
//	ofSetColor( 255, 0, 0 );
//	ofCircle( vLL.x, vLL.y, 50 );
//
//	ofCircle( camera.getViewportRight(), camera.getViewportBottom(), 0 );
//	ofCircle( camera.getViewportRight(), camera.getViewportTop(), 0 );
//	ofCircle( camera.getViewportLeft(), camera.getViewportTop(), 0 );

	glPushMatrix();
//	glRotatef( 0, _rotation, 0, 1 );

	for( unsigned int i = 0; i < _stars.size(); i++ )
	{
		_stars.at(i)->draw();
	}

	glPopMatrix();
}
