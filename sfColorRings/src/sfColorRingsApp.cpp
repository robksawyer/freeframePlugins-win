#include "sfColorRingsApp.h"
#include "ofxFFGLPlugin.h"
#include "SpinningRing.h"
#include "sfDrawingUtil.h"
#include <list>


sfColorRingsApp::sfColorRingsApp()
{
	// Here we add the parameters for the plugin 
	_vibrationAmount = 0.0f;
	_innerDiameter = 150.0f;
	_outerDiameter = 1000.0f;
	_offsetFactor = 100.0f;
	
	addFloatParameter("Vibration", &_vibrationAmount, 0.0f, 100.0f );
	addFloatParameter("Inner Diameter", &_innerDiameter, 0.0f, 1000.0f );
	addFloatParameter("Outer Diameter", &_outerDiameter, 0.0f, 1000.0f );
	addFloatParameter("Ring Spacing", &_offsetFactor, 0.0f, 100.0f );
}

void sfColorRingsApp::setup(){
	int vWindowW = 640;
	int vWindowH = 480;
	ofSetWindowShape( vWindowW, vWindowH );
	ofBackground(0,0,0);
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	
	_colorRing.setup( vWindowW, vWindowH );
}

void sfColorRingsApp::preIterate()
{

}

void sfColorRingsApp::iterate()
{
	_colorRing.setVibrationAmount( _vibrationAmount );
	_colorRing.setInnerDiameter( _innerDiameter );
	_colorRing.setOuterDiameter( _outerDiameter );
	_colorRing.setOffsetFactor( _offsetFactor );
	_colorRing.update();
}

void sfColorRingsApp::postIterate()
{

}

void sfColorRingsApp::draw()
{
	_colorRing.draw();
}

//--------------------------------------------------------------
void sfColorRingsApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void sfColorRingsApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void sfColorRingsApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void sfColorRingsApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void sfColorRingsApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void sfColorRingsApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void sfColorRingsApp::windowResized(int w, int h){

}
