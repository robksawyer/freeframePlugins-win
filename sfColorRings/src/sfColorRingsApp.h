#ifndef _TEST_APP
#define _TEST_APP


#include "ofxFFGLApp.h"
#include "SpinningRing.h"
#include "ColorRing.h"
#include "sfApp.h"

class sfColorRingsApp : public sfApp{
	
public:
	sfColorRingsApp();
		
	void setup();
	void draw();

	void preIterate();
	void iterate();
	void postIterate();
		
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	
	/**
	 * The amount of vibration (in pixels) added to all rings. 
	 * 0 means that the rings do not vibrate. 10 means that
	 * each ring will be moved by up to 10 pixels with each
	 * update event.
	 */
	float _vibrationAmount;
	/**
	 * The inner diameter of our rings.
	 */
	float _innerDiameter;
	/**
	 * The outer diameter of our rings.
	 */
	float _outerDiameter;
	/**
	 * The factor by which each ring's offset is multiplied.
	 * Increasing this number will have the effect of spacing
	 * each of the rings out from each other.
	 */
	float _offsetFactor;
	
	
private:
	ColorRing _colorRing;
};

#endif
	
