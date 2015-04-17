#include "sfBranchesApp.h"
#include "ofMain.h"
#include "ofxFFGLPlugin.h"
#include "sfResolumeBeatEventTracker.h"

sfBranchesApp::sfBranchesApp()
{
	// Add FFGL parameters
	_branchRotation = 0;
	addFloatParameter( "Rotation", &_branchRotation, 0.0f, 360.0f );

	_branchSpeed = 15.0;
	addFloatParameter( "Speed", &_branchSpeed, 1.0f, 50.0f );

	_branchLength = 250.0f;
	addFloatParameter( "Length", &_branchLength, 10.0f, 500.0f );

	addBeatEventParameter( "Branch Event", &_beatTracker );

	_randomBranching = 5;
	addFloatParameter( "Randomness", &_randomBranching, 0.0f, 25.0f );

	_cameraZoom = 1500;
	addFloatParameter( "Zoom", &_cameraZoom, 0.0f, 2000.0f );

	_cameraPan = 0;
	addFloatParameter( "Pan", &_cameraPan, -1000.0f, 1000.0f );

	_cameraMinShakiness = _cameraMaxShakiness = 50;
	addFloatParameter( "Constant Shake", &_cameraMinShakiness, 0.0f, 100.0f );
	addFloatParameter( "Branch Shake", &_cameraMaxShakiness, 0.0f, 400.0f );

	_cameraShakeSpeed = 20;
	addFloatParameter( "Shake Speed", &_cameraShakeSpeed, 10.0f, 100.0f );

	_cameraShakeDuration = 15;
	addFloatParameter( "Shake Decay", &_cameraShakeDuration, 1.0f, 200.0f );

	_fogDepth = 500;
	addFloatParameter( "Fog Depth", &_fogDepth, 0.0f, 2000.0f );

	_is3D = true;
	addBoolParameter( "3D", &_is3D );

	// TODO Make a few extra branches when beat events occur a few segments later.
	// TODO Turning shakiness decay to low settings with branch shake and speed on,
	// branch still shakes even if no sub-branches are created.
}

void sfBranchesApp::setup()
{
	ofBackground( 0, 0, 0 );
	ofSetFrameRate( 30 );
	ofSetVerticalSync( true );
//	ofSetWindowPosition( 2500, 600);

	_camera = sfCameraPlus();
	_camera.focalPoint( 0, 0, 0 );
	_camera.location( 0, 0, 1000 );
	_camera.addPlugin( &_cameraBump );

	_branchRotation = 0;
	_branchRotationSpeed = 1;
	_branchTipScreenLoc = 400;

	_branch.setBranchProbability(0);
	_branch.setNumberOfSegments( 150 );
}

void sfBranchesApp::preIterate()
{

}

void sfBranchesApp::iterate()
{
	// Beat events occur if the beatParameter changes more than the threshold.
	if( _beatTracker.isBeatEvent() )
	{
		float vStrength = _beatTracker.getBeatStrength();
		int vTotal = 1;

		if( vStrength > 0.95 )
		{
			vTotal = 3;
		}
		else if( vStrength > 0.85 )
		{
			vTotal = 2;
		}

		vStrength *= 1.5;
		if( vStrength > 1 ) vStrength = 1;

		_beatEvent( vStrength, vTotal );
	}
	else if( _randomBranching > 0 )
	{
		float vRand = ofRandom( 0, 100 );
		if( vRand < _randomBranching )
		{
			_beatEvent( 0.5, 1 );
		}
	}
	_beatTracker.update();

	// Update the camera and plugins.
	_cameraBump.setMaxWaveWidth( _cameraMaxShakiness );
	_cameraBump.setMinWaveWidth( _cameraMinShakiness );
	_cameraBump.setShakeDuration( _cameraShakeDuration );
	_cameraBump.setWaveSpeed( _cameraShakeSpeed );

	ofxVec3f vNewPos = _camera.getLocation();
	vNewPos.z = _cameraZoom;
	vNewPos.x = _cameraPan;
	_camera.location( vNewPos );
	_camera.update();

	// Grow all of the branches.
	_branch.setSegmentLength( _branchSpeed );
	_branch.setNumberOfSegments( _branchLength );
	_branch.setIs3D( _is3D );
	_branch.update();
}

void sfBranchesApp::postIterate()
{

}

void sfBranchesApp::_beatEvent( float vStrength, int vTotal )
{
	_branch.branch( vStrength, vTotal );
	_cameraBump.shake();
}

void sfBranchesApp::draw()
{
	// TODO Don't think we need these anymore.
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA,GL_ONE );

	if( _fogDepth > 0 )
	{
		glEnable( GL_DEPTH_TEST );

		glEnable( GL_FOG );
		glFogf( GL_FOG_MODE, GL_LINEAR );
		glFogf( GL_FOG_DENSITY, 0.03f );

		GLfloat fogColor[4]= {0.0f, 0.0f, 0.0f, 1.0f};
		glFogfv(GL_FOG_COLOR, fogColor );

//		glFogf( GL_FOG_START, _cameraZoom - _fogDepth );
//		glFogf( GL_FOG_START, _cameraZoom );
		glFogf( GL_FOG_START, _cameraZoom - (_fogDepth / 4) );
		glFogf( GL_FOG_END, _cameraZoom + _fogDepth );
	}
	else
	{
		glDisable( GL_DEPTH_TEST );
		glDisable( GL_FOG );
	}

	ofxVec3f vBranchTip = _branch.getEnd();

	_camera.place();

	glPushMatrix();
	glRotatef( _branchRotation, 1, 0, 0 );
	glTranslatef( _branchTipScreenLoc - vBranchTip.x, 0, 0 );

	_branch.draw();

	glPopMatrix();
}

void sfBranchesApp::keyPressed( int key )
{

}

//--------------------------------------------------------------
void sfBranchesApp::keyReleased( int key )
{

}

//--------------------------------------------------------------
void sfBranchesApp::mouseMoved( int x, int y )
{

}

//--------------------------------------------------------------
void sfBranchesApp::mouseDragged( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfBranchesApp::mousePressed( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfBranchesApp::mouseReleased( int x, int y, int button )
{

}

//--------------------------------------------------------------
void sfBranchesApp::windowResized( int w, int h )
{

}

