#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "sfApp.h"
#include "ofxFFGLApp.h"
#include "sfPerlinNoiseBranch.h"
#include "sfCameraPlus.h"
#include "sfCameraSineWave.h"
#include "sfResolumeBeatEventTracker.h"

class sfBranchesApp : public sfApp
{

	public:
		sfBranchesApp();
		void setup();
		void draw();

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
		 * The camera object viewing our scene.
		 */
		sfCameraPlus _camera;
		/**
		 * The object used to make the camera movement bumpy.
		 */
		sfCameraSineWave _cameraBump;
		/**
		 * The branch being drawn by this application.
		 */
		sfPerlinNoiseBranch _branch;
		/**
		 * True = Draw the scene in 3 dimensions.
		 */
		bool _is3D;
		/**
		 * Set the depth of the fog.
		 */
		float _fogDepth;
		/**
		 * The rotation of the branch.
		 */
		float _branchRotation;
		/**
		 * The number of degrees the branch will rotate each frame.
		 */
		float _branchRotationSpeed;
		/**
		 * The speed at which the branch grows (ie. how long each segment will be).
		 */
		float _branchSpeed;
		/**
		 * The number of branch segments.
		 */
		float _branchLength;
		/**
		 * The location that the tip of the branch will live on screen.
		 */
		float _branchTipScreenLoc;
		/**
		 * The object used to track when beat events occur.
		 */
		sfResolumeBeatEventTracker _beatTracker;
		/**
		 * The previous beat value.
		 */
		float _lastBeatValue;
		/**
		 * The current beat value.
		 */
		float _beatParameter;
		/**
		 * The threshold for change in _beatParameter before a beat event will be registered.
		 */
		float _beatThreshhold;
		/**
		 * The maximum amount that the beat change parameter can change.
		 */
		float _maxBeatChange;
		/**
		 * How shaky the camera is when it is bumped.
		 */
		float _cameraMaxShakiness;
		/**
		 * How shaky the camera is normally.
		 */
		float _cameraMinShakiness;
		/**
		 * The speed of the sine wave used to shake the camera.
		 */
		float _cameraShakeSpeed;
		/**
		 * The amount of time the camera shakes last.
		 */
		float _cameraShakeDuration;
		/**
		 * The camera's location on the positive z axis.
		 */
		float _cameraZoom;
		/**
		 * The camera's location on the x axis.
		 */
		float _cameraPan;
		/**
		 * Determine's how frequently random branches will be created
		 * (as a percentage probability).
		 */
		float _randomBranching;
		/**
		 * Make the camera shake and tree branch.
		 * @param strength The strength of the beat event.
		 */
		void _beatEvent( float strength, int total );
};

#endif
