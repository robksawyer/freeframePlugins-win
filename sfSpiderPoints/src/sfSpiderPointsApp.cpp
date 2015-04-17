#include "sfSpiderPointsApp.h"
#include "ofMain.h"
#include "ofxFFGLPlugin.h"
#include "sfMathUtils.h"

sfSpiderPointsApp::sfSpiderPointsApp()
{
	_zoom = 500.0f;
	// Move the camera towards/away from the SpiderPoints object.
	addFloatParameter( "Zoom", &_zoom, 1.0f, 2000.0f );

	_pointAnimationDuration = 40.0f;
	// The number of frames it takes to move the points in the SpiderPoints
	// object to their new locations.
	addFloatParameter( "Point Speed", &_pointAnimationDuration, 0.0f, 100.0f );

	_pointStaggerDuration = 1.0f;
	// The number of frames between points moving. If set to 0, all points will
	// move immediately when move events occur. If set to 10, one point will
	// start moving every 10 frames until all points have been told to move to
	// their new locations.
	addFloatParameter( "Point Stagger", &_pointStaggerDuration, 0.0f, 15.0f );

	_numberOfPoints = 4.0f;
	// The total number of points in the SpiderPoints object.
	addFloatParameter( "Total Points", &_numberOfPoints, 3.0f, 40.0f );

	// Cause the points in the SpiderPoints object to move to new locations.
	_pointMoveEventTracker = sfResolumeBeatEventTracker();
	addBeatEventParameter( "Event: Move", &_pointMoveEventTracker );

	_useColors = false;
	// True = Color the shape.
	// False = Make the shape white.
	addBoolParameter( "Use Colors", &_useColors );

	_easePointMovesInAndOut = true;
	// True = Points in the SpiderPoints object should ease in and ease out
	// when moving to new locations.
	// False = Points in the SpiderPoints object will only ease out when moving
	// to new locations.
	addBoolParameter( "Ease In/Out", &_easePointMovesInAndOut );

	// Cause the SpiderPoints object to rotate (if rotation events are being honored).
	_rotationEventTracker = sfResolumeBeatEventTracker();
	addBeatEventParameter( "Event: Rotate", &_rotationEventTracker );

	_rotationDuration = 60.0f;
	// The number of frames it takes to rotate the SpiderPoints object
	// if rotation events are being honored.
	addFloatParameter( "Rotate Speed", &_rotationDuration, 0.0f, 100.0f );

	_honorRotationEvents = true;
	// True = Use rotation events to pick a new random rotation for the SpiderPoints object.
	// False = Use the Rotation X/Y/Z sliders to set the rotation of the SpiderPoints object.
	addBoolParameter( "Use R Events", &_honorRotationEvents );

	_rotationX = 0.0f;
	// Set the X rotation of the SpiderPoints object.
	addFloatParameter( "Rotation X", &_rotationX, 0.0f, 360.0f );

	_rotationY = 0.0f;
	// Set the Y rotation of the SpiderPoints object.
	addFloatParameter( "Rotation Y", &_rotationY, 0.0f, 360.0f );

	_rotationZ = 0.0f;
	// Set the Z rotation of the SpiderPoints object.
	addFloatParameter( "Rotation Z", &_rotationZ, 0.0f, 360.0f );
}

void sfSpiderPointsApp::setup()
{
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 30 );
	ofSetVerticalSync( true );
	ofSetWindowPosition( 2000, 600);

	_spiderPoints = sfSpiderPoints();
	_spiderPoints.setWindowSize( ofGetWidth(), ofGetHeight() );
	_spiderPoints.setLocation( 0, 0, 0 );

	_resetSpiderPoint();

	_spiderPoints.setup();
}

void sfSpiderPointsApp::preIterate()
{
	_pointMoveEventTracker.setStandalone( true );
	_pointMoveEventTracker.setFramesPerBeat( 37 );
	_rotationEventTracker.setStandalone( false );
	_rotationEventTracker.setFramesPerBeat( 150 );

	_honorRotationEvents = false;
	_rotationY += 1.0;

	if( ofGetFrameNum() % 17 == 0 && ofGetFrameNum() > 1 )
	{
		_numberOfPoints = ofRandom( 3, 40 );
//		_zoom = ofRandom( 0, 2000 );
//		_rotationX = ofRandom( 0, 360 );
//		_rotationY = ofRandom( 0, 360 );
//		_rotationZ = ofRandom( 0, 360 );
	}
}

void sfSpiderPointsApp::iterate()
{
	ofxVec3f vLoc = _camera.getLocation();
	vLoc.z = _zoom;
	_camera.location( vLoc );

	_resetSpiderPoint();
	_spiderPoints.update();
}

void sfSpiderPointsApp::_resetSpiderPoint()
{
	_spiderPoints.setNumberOfPoints( (int)_numberOfPoints );
	_spiderPoints.useColors( _useColors );

	// Listen for point move events.
	if( _pointMoveEventTracker.isBeatEvent() )
	{
		_spiderPoints.movePoints();
	}
	_pointMoveEventTracker.update();

	// Listen for rotation events.
	if( _rotationEventTracker.isBeatEvent() )
	{
		if( _honorRotationEvents )
		{
			_spiderPoints.setRotationEaseDirection( sfAnimatedPoint::EASE_IN_OUT );
			_spiderPoints.rotate();
		}
	}
	_rotationEventTracker.update();

	// Set rotation and point speed values.
	if( _easePointMovesInAndOut )
	{
		_spiderPoints.setPointAnimationEaseDirection( sfAnimatedPoint::EASE_IN_OUT );
	}
	else
	{
		_spiderPoints.setPointAnimationEaseDirection( sfAnimatedPoint::EASE_OUT );
	}

	if( !_honorRotationEvents )
	{
		_spiderPoints.setRotationEaseDirection( sfAnimatedPoint::EASE_OUT );
		_spiderPoints.rotate( _rotationX, _rotationY, _rotationZ );
	}

	_spiderPoints.setAutoRotateDuration( _rotationDuration );
	_spiderPoints.setPointSpeed( _pointAnimationDuration );
	_spiderPoints.setPointStaggerDuration( (int)_pointStaggerDuration );
}

void 	sfSpiderPointsApp::postIterate()
{

}

void sfSpiderPointsApp::draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable( GL_DEPTH_TEST );

	_camera.place();

	_spiderPoints.draw();
}

void sfSpiderPointsApp::exit()
{
}

void sfSpiderPointsApp::keyPressed( int key )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::keyReleased( int key )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::mouseMoved( int x, int y )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::mouseDragged( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::mousePressed( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::mouseReleased( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfSpiderPointsApp::windowResized( int w, int h )
{

}

