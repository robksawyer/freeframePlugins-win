#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxFFGLApp.h"
#include "sfSpiderPoints.h"
//#include "ofxLight.h"
#include "sfCamera.h"
#include "sfApp.h"
//#include "ofx3DGraphics.h"
#include "sfResolumeBeatEventTracker.h"

class sfSpiderPointsApp : public sfApp{

	public:
		sfSpiderPointsApp();
		void setup();
		void draw();
		void exit();

		void preIterate();
		void iterate();
		void postIterate();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

	private:
		/**
		 * The main focus of our animation.
		 */
		sfSpiderPoints _spiderPoints;
		/**
		 * The object used to track beat events from resolume.
		 */
		sfResolumeBeatEventTracker _pointMoveEventTracker;
		/**
		 * The object used to track when rotation events occur.
		 */
		sfResolumeBeatEventTracker _rotationEventTracker;
		/**
		 * The camera viewing our scene.
		 * TODO Replace this with sfCamera.
		 */
		sfCamera _camera;
		/**
		 * The amount of time that the spinning motion of the SpiderPoints object should last.
		 */
		float _rotationDuration;
		/**
		 * The amount of time it takes the points to re-order themselves.
		 */
		float _pointAnimationDuration;
		/**
		 * The number of frames points are staggered when moving them to new locations.
		 */
		float _pointStaggerDuration;
		/**
		 * True = Animation direction for point objects will be ease in and out.
		 * False = Animation direction will just be ease out.
		 */
		bool _easePointMovesInAndOut;
		/**
		 * True = Allow rotation events to set a random rotation.
		 * False = Allow rotation to be set by rotation sliders.
		 */
		bool _honorRotationEvents;
		/**
		 * The amount of rotation around the X axis (if rotation events are being ignored).
		 */
		float _rotationX;
		/**
		 * The amount of rotation around the Y axis (if rotation events are being ignored).
		 */
		float _rotationY;
		/**
		 * The amount of rotation around the Z axis (if rotation events are being ignored).
		 */
		float _rotationZ;
		/**
		 * The number of points in the spider points object.
		 */
		float _numberOfPoints;
		/**
		 * The location of the camera on the z axis.
		 */
		float _zoom;
		/**
		 * True = color the shape. False = make the shape white.
		 */
		bool _useColors;
		/**
		 * Reset the state of the SpiderPoints object taking into account parameters modified
		 * by the host.
		 */
		void _resetSpiderPoint();
};

#endif
