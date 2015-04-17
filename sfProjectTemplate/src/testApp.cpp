#include "testApp.h"
#include "ofMain.h"
#include "ofxFFGLPlugin.h"

testApp::testApp()
{
	// Add FFGL parameters
//	addFloatParameter( "AutoRotate Time", &_rotationDuration, 0.0f, 100.0f );
}

void testApp::setup()
{
	int vWindowW = 640;
	int vWindowH = 480;
	ofSetWindowShape( vWindowW, vWindowH );
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 30 );
	ofSetVerticalSync( true );
}

void testApp::update()
{
}

void testApp::draw()
{
	ofCircle( 50, 50, 400 );
}

void testApp::keyPressed( int key )
{

}

//--------------------------------------------------------------
void testApp::keyReleased( int key )
{

}

//--------------------------------------------------------------
void testApp::mouseMoved( int x, int y )
{

}

//--------------------------------------------------------------
void testApp::mouseDragged( int x, int y, int button )
{

}

//--------------------------------------------------------------
void testApp::mousePressed( int x, int y, int button )
{

}

//--------------------------------------------------------------
void testApp::mouseReleased( int x, int y, int button )
{

}

//--------------------------------------------------------------
void testApp::windowResized( int w, int h )
{

}

