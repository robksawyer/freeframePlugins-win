/*
 * sfApp.cpp
 *
 *  Created on: Nov 24, 2010
 *      Author: marc.wren
 */

#include "sfApp.h"
#include "sfResolumeBeatEventTracker.h"

sfApp::sfApp()
{
	_isRunningAsApplication = false;
}

void sfApp::addBeatEventParameter( const char * vName, sfResolumeBeatEventTracker * vTracker )
{
	float* vParamAddress = vTracker->getParameterAddress();
	float vMaxChange = vTracker->getMaxChangeValue();
	addFloatParameter( vName, vParamAddress, 0.0f, vMaxChange );
}

void sfApp::update()
{
	if( _isRunningAsApplication )
	{
		preIterate();
	}
	iterate();
	if( _isRunningAsApplication )
	{
		postIterate();
	}
}

void sfApp::preIterate()
{

}

void sfApp::iterate()
{

}

void sfApp::postIterate()
{

}

void sfApp::runAsApplication( bool vRunAsApp )
{
	_isRunningAsApplication = vRunAsApp;
}

bool sfApp::isApplication()
{
	return _isRunningAsApplication;
}

void sfApp::setup()
{
}

void sfApp::draw()
{
}

void sfApp::keyPressed( int key )
{

}

//--------------------------------------------------------------
void sfApp::keyReleased( int key )
{

}

//--------------------------------------------------------------
void sfApp::mouseMoved( int x, int y )
{

}

//--------------------------------------------------------------
void sfApp::mouseDragged( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfApp::mousePressed( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfApp::mouseReleased( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfApp::windowResized( int w, int h )
{

}
